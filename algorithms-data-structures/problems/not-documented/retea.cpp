/*
	Mitoi Stefan - Daniel
	Grupa 231
	Drumuri minime - problema 3
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <queue>

#define NMAX 100010
#define INF 0x3f3f3f3f

using namespace std;

ifstream f("retea.in");
ofstream g("retea.out");

/*
	s - nodul de start
	t - nodul destinatie
	m - nr. de muchii
	n - nr. de noduri
*/

int						s, t, m, n;
vector<pair<int, int>> 	listaArce[NMAX]; // Listele de adiacenta

/*
	Dijkstra gaseste cel mai scurt de la nodul de start s la toate celalalte. 
    Complexitatea algoritmului ramane cea a algoritmului Dijkstra, O(m * log(n)), deoarece folosim lista de adiacenta + heap

	Facem Dijkstra de la nodul sursa si ni se returneaza doi vectori:
	- dist[], unde dist[i] este cea mai mica distanta de la nodul sursa la i
	- prev[], unde prev[i] este nodul prin care se ajunge la distanta minima dist[i]

	Problema vrea sa aflam un drum de siguranta maxima, siguranta fiind data de produsul ponderilor grafului, care au forma 1/(2^p)
	Având un produs 1/(2^p_1) * 1/(2^p_2) * ... * 1/(2^p_n) = = 2 ^ ((-1) * (p_1 + p_2 + ... + p_n))
	Noi cautam suma p_1 + p_2 + ... + p_n minimă => Căutăm un drum minim de valori p_i între s și t
	Deci aplicăm Dijkstra pentru a afla drumul minim, unde drumurile au valoarea p_i, care corespund siguranței 1/(2^p_i)
*/

void dijkstra()
{
	// Heap folosit pentru parcurgere
	priority_queue<pair<int, int>, vector <pair<int, int>> , greater<pair<int, int>> > q; 
	vector<int>		dist(m + 1, INF); // Vectorul distanelor
	vector<int>		prev(m + 1, -1); // Vectorul nodurilor sursa
	
    dist[s] = 0;
	q.push({0, s});
  
    dist[s] = 0;
	
	while (!q.empty())
	{
		// Luam indexul unui nod si il scoatem din heap
		int u = q.top().second;
		q.pop();
		
		// Viziteaza vecinii nodului u
		for (int i = 0; i < listaArce[u].size(); i++)
		{
			// v - nodul destinatie, w - distanta pana la el
			int v = listaArce[u][i].first;
			int w = listaArce[u][i].second;
			
			// Daca distanta actuala pana la nodul v este mai mare decat distanta daca am merge pe muchia (u, v).
			if (dist[v] > dist[u] + w)
			{
				dist[v] = dist[u] + w;
				prev[v] = u;
				q.push({dist[v], v});
			}
		}
	}
	
	// Afisam distantele catre toate nodurile (poate ajuta la debug)
	for (int i = 1; i <= n; i++)
		cout << i << " - " << dist[i] << '\n';
	
	// Aflam drumul de la s la t, sau spunem ca acesta nu exista
	if (dist[t] == INT_MAX)
	{
		cout << "Nu se poate ajunge din nodul " << s << " in nodul " << t << '\n';
	}
	else
	{
		vector<int> drum;
		drum.push_back(t);
		while (t != s)
		{
			drum.push_back(prev[t]);
			t = prev[t];
		}
		
		for (int i = drum.size() - 1; i >= 0; i--)
			cout << drum[i] << ' ';
		cout << '\n';
	}
}

int		main()
{

	// Citim s si t din problema
	cin >> s >> t;
	
	// Citim numarul de noduri si numarul de muchii
	f >> n >> m;
	for (int i = 0; i < m; i++)
	{
		// Citim muchiile si costul acestora
		int a, b, w;
		f >> a >> b >> w;
		listaArce[a].push_back({b, w});
	}
	
	// Aplicăm Dijkstra unde afisam si drumul minim
	dijkstra();
	
	return 0;
}