#include <iostream>
#include <fstream>
#include <vector>
#include <queue>

#define NMAX 100010
#define INF 0x3f3f3f3f

using namespace std;

ifstream f("dijkstra.in");
ofstream g("dijkstra.out");

int						s, t, m, n;
vector<pair<int, int>> 	listaArce[NMAX];

void dijkstra(int s) // dj astra
{
	priority_queue<pair<int, int>, vector <pair<int, int>> , greater<pair<int, int>> > q; 
	vector<int>		dist(m + 1, INF);
	vector<int>		prev(m + 1, -1);
	
    dist[s] = 0;
	q.push({0, s});
  
    dist[s] = 0;
	
	while (!q.empty())
	{
		int u = q.top().second;
		q.pop();
		
		for (int i = 0; i < listaArce[u].size(); i++)
		{
			int v = listaArce[u][i].first;
			int w = listaArce[u][i].second;
			
			if (dist[v] > dist[u] + w)
			{
				dist[v] = dist[u] + w;
				prev[v] = u;
				q.push({dist[v], v});
			}
		}
	}
	
	for (int i = 2; i <= n; i++)
	{
		if (dist[i] == INF)
			dist[i] = 0;
			
		g << dist[i] << ' ';
	}
}

int		main()
{
	f >> n >> m;
	for (int i = 0; i < m; i++) // m complexitatea pentru citire
	{
		int a, b, w;
		f >> a >> b >> w;
		listaArce[a].push_back({b, w});
	}
	
	dijkstra(1); // facem djkstra unde vom afisa si drumul minim
	
	return 0;
}