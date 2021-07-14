/*
	Mitoi Stefan - Daniel
	Grupa 231
    Arbori parțiali de cost minim - problema 1, versiunea O(m * log(n))
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <algorithm>

#define NMAX 100010
#define INF 0x3f3f3f3f

using namespace std;

ifstream f("grafpond.in");
ofstream g("grafpond.out");

typedef struct {
    int w;
    int u;
    int v;
} edge;


int						m, n;
vector<edge>            listaArce, mst;
int                     parent[NMAX];

bool myComp(edge first, edge second)
{
    return first.w < second.w;
}

int findOrigin(int i)
{
    if (i != parent[i]) 
        parent[i] = findOrigin(parent[i]); 
    
    return parent[i]; 
}

void    kruskal()
{
    sort(listaArce.begin(), listaArce.end(), myComp);
    
    for (int i = 1; i <= n; i++)
        parent[i] = i;

    for (int i = 0; i < listaArce.size(); i++)
    {
        int u = listaArce[i].u;
        int v = listaArce[i].v;

        int up = findOrigin(u);
        int vp = findOrigin(v);
        if (up != vp)
        {
            mst.push_back(listaArce[i]);
            parent[vp] = up;
        }
    }

    int cost = 0;
    for (int i = 0; i < mst.size(); i++)
    {
        cout << mst[i].u << " - " << mst[i].v << '\t' << mst[i].w << '\n';
        cost += mst[i].w;
    }
    cout << "Cost total = " << cost << '\n';

}

int		main()
{
	f >> n >> m;

	for (int i = 0; i < m; i++)
	{
		edge e;
		f >> e.u >> e.v >> e.w;
		listaArce.push_back(e);
	}

    kruskal();

	return 0;
}