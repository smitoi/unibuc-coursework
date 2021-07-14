/*
	Mitoi Stefan - Daniel
	Grupa 231
    Arbori parțiali de cost minim - problema 5
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

// muchie de la u la v
typedef struct {
    int w;
    int u;
    int v;
} edge;

edge                    deAdaugat;
int						m, n, cost;
vector<edge>            listaArce, mst, mstAux;
vector<pair<int, int>>  vecini[NMAX];
int                     culori[NMAX];
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
            vecini[listaArce[i].u].push_back({listaArce[i].v, listaArce[i].w});
            vecini[listaArce[i].v].push_back({listaArce[i].u, listaArce[i].w});
            parent[vp] = up;
        }
    }

    cout << "Muchiile apcm in G: " << '\n';
    for (int i = 0; i < mst.size(); i++)
    {
        cout << mst[i].u << ' ' << mst[i].v << '\t' << mst[i].w << '\n';
        cost += mst[i].w;
    }
    cout << "Cost " << cost << '\n';
}

bool    vizitate[NMAX];
vector<pair<int, int>>     dfs(vector<pair<int, int>> drum, int curent, int cautat)
{
    vizitate[curent] = true;

    for (int i = 0; i < vecini[curent].size(); i++)
    {
        int next = vecini[curent][i].first;

        if (vizitate[next] != true)
        {
            drum.push_back(vecini[curent][i]);
            if (vecini[curent][i].first == cautat)
                return drum;
            else
            {
                vector<pair<int, int>> aux = dfs(drum, next, cautat);
                if (aux.size() != 0)
                    return aux;
            }
            drum.pop_back();
        }
    }

    return vector<pair<int, int>>();
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
    
    cin >> deAdaugat.u >> deAdaugat.v >> deAdaugat.w;
    mst.push_back(deAdaugat);
    mstAux = mst;

    edge waux;
    waux.w = -1;
    vector<pair<int, int>> aux = dfs(vector<pair<int, int>>(), deAdaugat.u, deAdaugat.v);
    for (int i = 0; i < aux.size(); i++)
        if (aux[i].second > waux.w)
        {
            waux.w = aux[i].second;
            waux.v = aux[i].first;
            if (i == 0)
                waux.u = deAdaugat.u;
            else
                waux.u = aux[i - 1].first;
        }
    if (deAdaugat.w > waux.w)
    {
        cout << "Muchia de cost maxim din ciclul inchis de " << deAdaugat.u << ' ' << deAdaugat.v << " in apcm este " << deAdaugat.u << ' ' << deAdaugat.v << " de cost " << deAdaugat.w << '\n';
        cout << "Dupa adaugarea muchiei costul este " << cost << '\n';
    }
    else
    {
        cout << "Muchia de cost maxim din ciclul inchis de " << deAdaugat.u << ' ' << deAdaugat.v << " in apcm este " << waux.u << ' ' << waux.v << " de cost " << waux.w << '\n';
        cout << "Dupa adaugarea muchiei costul este " << cost - waux.w + deAdaugat.w << '\n';
    }

	return 0;
}