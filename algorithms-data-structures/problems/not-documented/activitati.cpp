/*
	Mitoi Stefan - Daniel
	Grupa 231
	Drumuri minime - problema 1
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <queue>

#define NMAX 100010
#define INF 0x3f3f3f3f

using namespace std;

ifstream f("activitati.in");
ofstream g("activitati.out");

typedef struct {
	int timp_s; // Timp start
	int timp_f; // Timp finalizare
} activitate;

vector<int>     listaArce[NMAX]; // Listele de adiacenta pentru sortarea topologica
vector<int>		listaDependente[NMAX]; // Lista dependentelor (listaDependente[i] contine nodurile j de care depinde i in contextul problemei)
vector<int>		listaCritic; // Lista activitatilor critice
int             deg[NMAX]; // Gradele nodurilor pentru sortare topologica
int				timpi[NMAX]; // Timpii necesari pentru desfasurarea activitatilor
activitate		out[NMAX]; // Intervalele de timp in care se desfasoara activitatile
vector<int>     l; // Lista nodurilor sortate topologic
int     n, m; // n - nr. de activitati (noduri), m - nr. de dependente (muchii)

// Sortare topologica in O(n + m)
void    topologicalSort() 
{
	// Iau nodurile cu grad 0
    for (ssize_t i = 1; i <= n; i++)
        if (deg[i] == 0)
            l.push_back(i);
    
	// Parcurge toate nodurile - O(n)
    for (ssize_t i = 0; i < l.size(); i++)
    {
		// Parcurge vecinii fiecarui nod - O(m) pentru ca ajungem sa parcurgem toate muchiile
        for (ssize_t j = 0; j < listaArce[l[i]].size(); j++) 
        {
			// Ii izolez si daca au gradul 0 ii iau in lista sortata
            deg[listaArce[l[i]][j]]--;
            if (deg[listaArce[l[i]][j]] == 0)
                l.push_back(listaArce[l[i]][j]);
        }
    }
}


/*
	Algoritmul reprezinta activitatile ca noduri, iar dependenta unei activitati I de o activitate J ca o muchie (I, J).
	Facem sortare toplogica, iar apoi pe ordinea data de aceasta aplicam urmatorul algoritm pentru fiecare nod:

	Timpii sunt aflati in functie de lista de dependente. Pentru o activitate A:
	- daca listaDependente[A] are lungimea 0, activitatea incepe de la timpul de start 0 pana la timpul de final timpi[A]
	- daca listaDependente[A] are lungimea > 0, parcurgem fiecare activitate de care depinde si aflam timpul de final maxim M dintre acestea. Timpul de start pentru activitatea A va fi M pana la timpul de final M + timpi[A]

	Pentru a afla timpul minim de desfasurarea, la determinarea acestor intervale cautam timpul de final maxim. 

	Pentru a afla drumul critic pornim de la o activitate A cu timpul de final maxim si parcurgem in revers cautand o dependenta B cu timpul de start al lui A egal cu timpul de final al lui B.
	Ne mutam pe activitatea B si continuam sa facem asta pana gasim o activitate de start (care nu are dependente), moment in care am parcurs tot drumul critic si il putem afisa.
*/


int		main()
{
	// Citim cate activitati avem si timpii de desfasurare (activitati = noduri)
	f >> n;
	for (unsigned int i = 0; i < n; i++)
		f >> timpi[i + 1];
	
	// Citim cate dependente avem si care sunt acestea (dependente = muchii)
	f >> m;
	for (unsigned int i = 0; i < m; i++)
	{
		int nodS, nodD;
		f >> nodS >> nodD;
        listaArce[nodS].push_back(nodD);
		listaDependente[nodD].push_back(nodS);
        deg[nodD]++;
	}

	// Aplicam sortarea topologica
    topologicalSort();
	
	//
	int activ_minim = -1;
	int	timp_minim = -1;
	
	// Parcurge toate nodurile in ordinea data de sortarea topologica - O(n)
	for (unsigned int i = 0; i < n; i++)
	{
		activitate aux = { 0, timpi[l[i]] };
		
		// Daca avem dependente pentru nodul curent
		if (listaDependente[l[i]].size())
		{
			unsigned int maxim = 0;
			
			// Parcurge toate dependentele - O(m) pentru ca nr. dependentelor = nr. muchiilor
			for (unsigned int j = 0; j < listaDependente[l[i]].size(); j++)
			{
				if (out[listaDependente[l[i]][j]].timp_f > maxim)
					maxim = out[listaDependente[l[i]][j]].timp_f;
			}
			aux.timp_s += maxim;
			aux.timp_f += maxim;
		}
		
		out[l[i]] = aux;
		
		// Aici aflam timpul minim de desfasurare al proiectului si ultima activitate
		if (out[l[i]].timp_f > timp_minim)
		{
			timp_minim = out[l[i]].timp_f;
			activ_minim = l[i];
		}
	}
	
	// Afisam timpul minim
	cout << "Timp minim " << timp_minim << '\n';

	listaCritic.push_back(activ_minim);
	// Inca un O(m) sa aflam drumul critic
	while (listaDependente[activ_minim].size())
	{
		for (unsigned int i = 0; i < listaDependente[activ_minim].size(); i++)
		{
			if (out[listaDependente[activ_minim][i]].timp_f == out[activ_minim].timp_s)
			{
				activ_minim = listaDependente[activ_minim][i];
				listaCritic.push_back(activ_minim);
				break;
			}
		}
	}
	
	// Afisam activitatile critice
	cout << "Activitati critice: ";
	for (int i = listaCritic.size() - 1; i >= 0; i--)
	{
		cout << listaCritic[i] << ' ';
	}
	
	cout << '\n';
	// Afisam intervalele de desfasurare
	for (unsigned int i = 1; i <= n; i++)
	{
		cout << i << ": " << out[i].timp_s << " " << out[i].timp_f << '\n';
	}
	
	return 0;
}