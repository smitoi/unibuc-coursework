/*
	Mitoi Stefan - Daniel
	Grupa 231
	Drumuri minime - problema 2
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <queue>

#define NMAX 100010
#define INF 0x3f3f3f3f

using namespace std;

ifstream f("grafpond.in");
ofstream g("grafpond.out");

/*
	s - nodul de start
	k - nr. punctelor de control
	t - auxiliar pentru citirea punctelor de control
	m - nr. de muchii
	n - nr. de noduri
*/
int						s, t, m, n, k;
vector<pair<int, int>> 	listaArce[NMAX]; // Listele de adiacenta
int						distMin = INF, punctMin = -1; // Distanta minima si punctul de control cu distanta minima
vector<int>				drumMin; // Vector pentru drumul minim 

/*
	Dijkstra gaseste cel mai scurt de la nodul de start s la toate celalalte. 
    Complexitatea algoritmului ramane cea a algoritmului Dijkstra, O(m * log(n)), deoarece folosim lista de adiacenta + heap

	Facem Dijkstra de la nodul sursa si ni se returneaza doi vectori:
	- dist[], unde dist[i] este cea mai mica distanta de la nodul sursa la i
	- prev[], unde prev[i] este nodul prin care se ajunge la distanta minima dist[i]

	Citim punctele de control si aflam distanta minima intre sursa si orice punct de control.
	Apoi folosim vectorul prev ca sa aflam nodurile care alcatuiesc drumul.
*/

pair<vector<int>, vector<int>> dijkstra(int s)
{
	// Heap folosit pentru parcurgere
	priority_queue<pair<int, int>, vector <pair<int, int>> , greater<pair<int, int>> > q; 
	vector<int>		dist(m + 1, INF); // Vectorul distanelor
	vector<int>		prev(m + 1, -1); // Vectorul nodurilor sursa
	
    dist[s] = 0;
	q.push({0, s});
	
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
	
	// Returnam distantele si nodurile anterioare
	return {dist, prev};
}

int		main()
{
	// Citim nr. de noduri si de muchii
	f >> n >> m;
	for (int i = 0; i < m; i++)
	{
		// Citim muchiile si costul acestora
		int a, b, w;
		f >> a >> b >> w;
		listaArce[a].push_back({b, w});
		listaArce[b].push_back({a, w});
	}
	
	// Citim nodul sursa
	cout << "s = ";
	cin >> s;
	// Aplicăm Dijkstra pentru a afla distantele pornind de la nodul s
	pair<vector<int>, vector<int>> aux = dijkstra(s);
	vector<int> dist = aux.first;
	vector<int> prev = aux.second;
	
	// Citim nr. celor k puncte de control
	cout << "k = ";
	cin >> k;
	for (int i = 0; i < k; i++)
	{
		// Citim punctul de control si afisam distanta
		cout << "Punct de control " << i + 1 << " = ";
		cin >> t;
		if (dist[t] == INF)
		{
			cout << "Nu se poate ajunge din nodul " << s << " in nodul " << t << '\n';
		}
		else if (punctMin == -1 || dist[t] < distMin)
		{
			// Daca distanta catre punctul original este mai mica decat distanta minima, retinem punctul
			if (dist[t] < distMin)
			{
				distMin = dist[t];
				punctMin = t;
			}
		}
	}
	
	int p_orig = punctMin;
	vector<int> drum;

	drum.push_back(p_orig);
	// Aflam drumul de la s la t
	while (p_orig != s)
	{
		drum.push_back(prev[p_orig]);
		p_orig = prev[p_orig];
	}
	drumMin = drum;

	// Afisam cel mai apropriat punct de control
	if (punctMin != 0)
	{
		cout << "Cel mai apropriat punct este " << punctMin << " cu drumul de lungime " << distMin << ": ";
		for (int i = drumMin.size() - 1; i >= 0; i--)
			cout << drumMin[i] << ' ';
		cout << '\n';
	}
	else
		cout << "Nu se poate ajunge la nici un punct de control" << '\n';

	return 0;
}