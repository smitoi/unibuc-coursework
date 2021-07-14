/*
	Mitoi Stefan - Daniel
	Grupa 231
    Arbori parțiali de cost minim - problema 4
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <cmath>

#define NMAX 100010
#define INF 0x3f3f3f3f

using namespace std;

ifstream f("retea2.in");
ofstream g("retea2.out");

int						m, n, e;
vector<pair<int, double>> 	listaArce[NMAX];
vector<pair<int, int>>       coord;
int                     weights[NMAX], origins[NMAX];
bool                    inmst[NMAX];

double  distanta(int a, int b)
{
    int x = coord[a].first - coord[b].first;
    int y = coord[a].second - coord[b].second;

    return (sqrt(x * x + y * y));
}

void    prim()
{
    priority_queue <pair <int, int>, vector <pair <int, int>>, greater <pair <int, int>>> q;

    for (int i = n + 1; i <= n + m; i++)
        weights[i] = INF;
    
    for (int i = 1; i <= n; i++)
    {
        weights[i] = 0;
        origins[i] = -1;
        q.push({0, i});
    }

    while (q.size())
    {
        int u = q.top().second;
        q.pop();
        inmst[u] = true;

        for (int i = 0; i < listaArce[u].size(); i++)
        {
            int v = listaArce[u][i].first;
            int w = listaArce[u][i].second;

            if (!inmst[v] && w < weights[v])
            {
                weights[v] = w;
                q.push({w, v});
                origins[v] = u;
            }
        }
    }

    int cost = 0;
    for (int i = 1; i <= n + m; i++)
        if (origins[i] != -1)
            cost += distanta (origins[i], i);
    cout << cost << '\n';

    for (int i = 1; i <= n + m; i++)
        if (origins[i] != -1)
            cout << origins[i] << " - " << i << '\n';
}

int		main()
{
	f >> n >> m >> e;

    coord.push_back({0, 0});
    for (int i = 1; i <= n + m; i++)
    {
        int x, y;
        f >> x >> y;
        coord.push_back({x, y});
    }

	for (int i = 0; i < e; i++)
	{
		int a, b;
		f >> a >> b;
		listaArce[a].push_back({b, distanta(a, b)});
		listaArce[b].push_back({a, distanta(a, b)});
	}

    prim();

	return 0;
}