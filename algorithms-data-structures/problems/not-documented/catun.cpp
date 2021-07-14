/*
	Mitoi Stefan - Daniel
	Grupa 231
	Drumuri minime - problema 4
	https://www.infoarena.ro/job_detail/2679971
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <algorithm>
#include <set>

#define NMAX 100010
#define INF 0x3f3f3f3f

using namespace std;

ifstream f("catun.in");
ofstream g("catun.out");

/*
	s - nodul de start
	k - nr. fortaretelor
	m - nr. de muchii
	n - nr. de noduri
*/
int						s, m, n, k;
vector<pair<int, int>> 	listaArce[NMAX]; // Listele de adiacenta
vector<int>				fortarete; // Lista fortaretelor

/*
	Dijkstra gaseste cel mai scurt de la nodul de start s la toate celalalte. Algoritmul incepe prin a insera in set elemente de tip {0, fortarete[i]} pentru a incepe parcurgerea de la fiecare fortareata.
    Complexitatea algoritmului ramane cea a algoritmului Dijkstra, O(m * log(n)), deoarece folosim lista de adiacenta + set
	
	Cand suntem la nodul u, si vizitam un vecin de-al sau v, daca gasim o distanta mai buna trecand prin muchia (u, v), vom insera in set {dist[v], v} pentru a revizita vecinii lui v.
	De asemenea, vom seta ca nodul v este apropriat de fortareata de care este si u apropriat prin ans[v] = ans[u], si vom schimba distanta catre v.
*/

vector<int>  dijkstra()
{
	set<pair<int, int>> s; // Set folosit pentru parcurgere
	vector<int>		dist(m + 1, INF); // Vectorul distantelor
	vector<int>		ans(n + 1, 0); // Vector cu raspunsul la problema
	
	// Inseram fortaretele pentru a porni cu mai multe noduri de start
	// Astfel garantam ca algoritmul va vizita nodurile cele mai apropriate de fiecare fortareata
	for (int i = 0; i < k; i++)
	{
		s.insert({0, fortarete[i]});
		// O fortareata este cea mai apropriata de ea insasi
		ans[fortarete[i]] = fortarete[i];
		dist[fortarete[i]] = 0;
	}
	
	while (!s.empty())
	{
		// Luam indexul unui nod si il scoatem din set
		int u = s.begin() -> second;
		s.erase(s.begin());
		
		// Viziteaza vecinii nodului u
		for (int i = 0; i < listaArce[u].size(); i++)
		{
			// v - nodul destinatie, w - distanta pana la el
			int v = listaArce[u][i].first;
			int w = listaArce[u][i].second;
			
			// Daca distanta actuala pana la nodul v este mai mare decat distanta daca am merge pe muchia (u, v)
			// Schimbam distanta, si spunem ca nodul v se va duce la aceeasi fortareata ca nodul u
			if (dist[v] > dist[u] + w)
			{
				s.erase({dist[v], v});
				dist[v] = dist[u] + w;
				ans[v] = ans[u];
				s.insert({dist[v], v});
			}
			else if (dist[v] == dist[u] + w && ans[u] < ans[v])
				ans[v] = ans[u];
		}
	}
	
	return ans;
}

int		main()
{
	// Citim numarul de noduri, de muchii, si numarul de fortarete
	f >> n >> m >> k;
	
	// Citim ce noduri sunt fortarete
	for (int i = 0; i < k; i++)
	{
		int a;
		f >> a;
		fortarete.push_back(a);
	}
	
	// Citim muchiile
	for (int i = 0; i < m; i++)
	{
		int a, b, w;
		f >> a >> b >> w;
		listaArce[a].push_back({b, w});
		listaArce[b].push_back({a, w});
	}
	
	// Aplicăm Dijkstra, care va intoarce un vector ans, unde ans[i] = index-ul fortaretei cea mai apropriata de nodul i
	vector<int> ans = dijkstra();

	for (int i = 1; i <= n; i++)
		// Daca e o fortareata sau nu s-a gasit nici un drum catre acest nod pornind de la orice fortareata
		if (ans[i] == i || ans[i] == INF)
			g << 0 << ' ';
		else
			g << ans[i] << ' ';
	
	return 0;
}