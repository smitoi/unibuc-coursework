#include <iostream>
#include <fstream>
#include <vector>
#include <stack>
#include <cstring>

#define NMAX 100010
using namespace std;

ifstream f("ctc.in");
ofstream g("ctc.out");

typedef struct {
    int index;
    int lowlink;
    bool onStack;
} nod;

vector<nod>     listaNoduri;
vector<int>     listaArce[NMAX];
vector<vector<int>>     listaComponente;
stack<int>      S;
int             n, m;
int             ix = 0;
int             k = 0;

void     strongconnect(int   v)
{
	// Ii actualizam index-ul, link-ul si il punem pe stack
    listaNoduri[v].index = ix;
    listaNoduri[v].lowlink = ix;
    ix++;
    S.push(v);
    listaNoduri[v].onStack = true;

    for (int i = 0; i < listaArce[v].size(); i++)
    {
		// Ne uitam la toti vecinii lui v
        int w = listaArce[v][i];
		// Daca n-a fost vizitat, ii facem si lui strongconnect si link-ul lui v va fi minimul dintre link-ul lui si link-ul lui w
        if (listaNoduri[w].index == -1)
        {
            strongconnect(w);
            listaNoduri[v].lowlink = min(listaNoduri[v].lowlink, listaNoduri[w].lowlink);
        }
        else if (listaNoduri[w].onStack)
		// Daca este deja pe stack vecinul, link-ul lui v este minimul dintre link-ul lui si index-ul lui w
            listaNoduri[v].lowlink = min(listaNoduri[v].lowlink, listaNoduri[w].index);
    }

	// Daca am ajuns la final si avem o componenta tare conexa luam tot ce e pe stack
    if (listaNoduri[v].lowlink == listaNoduri[v].index)
    {
        k++;
        vector<int> L;
        int w;
        do {
            w = S.top();
            S.pop();
            listaNoduri[w].onStack = false;
            L.push_back(w);
        } while (v != w);
        listaComponente.push_back(L);
    }
}

// https://www.infoarena.ro/problema/ctc
// https://www.infoarena.ro/job_detail/2660708
int		main()
{
	f >> n >> m;
	for (unsigned int i = 0; i < m; i++)
	{
		int nodS, nodD;
		f >> nodS >> nodD;
		listaArce[nodS].push_back(nodD);
	}

    for (unsigned int i = 1; i <= n + 1; i++)
        listaNoduri.push_back({-1, -1, false});
    
    for (unsigned int i = 1; i <= n; i++)
    {
        if (listaNoduri[i].index == -1)
            strongconnect(i);
    }
	
    g << k << '\n';
    for (int i = 0; i < listaComponente.size(); i++)
    {
        for (int j = 0; j < listaComponente[i].size(); j++)
            g << listaComponente[i][j] << ' ' ;
        g << '\n';
    }

	return 0;
}