/*
	Mitoi Stefan - Daniel
	Grupa 231
    Arbori parțiali de cost minim - problema 6
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

bool    operator==(edge e, edge f)
{
    return e.w == f.w && e.u == f.u && e.v == f.v;
}

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

int    kruskal()
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
        cost += mst[i].w;

    return cost;
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
    int             aux;
    aux = kruskal();

    cout << "Primul - cost = " << aux << '\n';
    for (int i = 0; i < mst.size(); i++)
        cout << mst[i].u << " - " << mst[i].v << '\t' << mst[i].w << '\n';

    sort(mst.begin(), mst.end(), myComp);
    edge e = mst[mst.size() - 1];
    mst.clear();
    listaArce.erase(remove(listaArce.begin(), listaArce.end(), e), listaArce.end());
    aux = kruskal();

    cout << "Al doilea - cost = " << aux << '\n';
    for (int i = 0; i < mst.size(); i++)
        cout << mst[i].u << " - " << mst[i].v << '\t' << mst[i].w << '\n';

	return 0;
}