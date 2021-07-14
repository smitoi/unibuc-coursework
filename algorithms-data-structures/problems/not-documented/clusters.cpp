/*
	Mitoi Stefan - Daniel
	Grupa 231
    Arbori parțiali de cost minim - problema 3
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <cstring>

#define NMAX 100010
#define SMAX 50
#define INF 0x3f3f3f3f

using namespace std;

ifstream f("cuvinte.in");
ofstream g("cuvinte.out");

// muchie de la u la v
typedef struct {
    int u;
    int v;
    int w;
} edge;

int						m, n, nclusters;
vector<edge>            listaArce, mst;
vector<int>             clusters[NMAX];
char                    cuv[NMAX][SMAX];
int                     parent[NMAX], deg[NMAX];
bool                    visited[NMAX];

int minimum(int a, int b)
{
    if (a < b)
        return a;
    else
        return b;
}

int distanta(char s[], char t[])
{
    int ss = strlen(s);
    int ts = strlen(t);
    
    if (ts == 0)
        return ss;
    else if (ss == 0)
        return ts;
    else if (s[0] == t[0])
        return distanta(s + 1, t + 1);
    else
        return 1 + minimum(distanta(s + 1, t), minimum(distanta(s, t + 1), distanta(s + 1, t + 1)));
}

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

    for (int i = 0; i < mst.size(); i++)
        cout << mst[i].u << " - " << mst[i].v << '\t' << mst[i].w << '\n';
}

void    dfs(int c)
{
    clusters[nclusters].push_back(c);
    visited[c] = true;

    for (int i = 0; i < mst.size(); i++)
    {
        if (mst[i].u == c && !visited[mst[i].v])
            dfs(mst[i].v);
        if (mst[i].v == c && !visited[mst[i].u])
            dfs(mst[i].u);
    }
}

int		main()
{
    int i = 1;
    int j = 0;
    int k;
    char c[50];

    while (f >> c)
    {
        strcpy(cuv[i], c);
        i++;
    }
    i--;

    n = i;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
        {
            edge e;
            e.u = i;
            e.v = j;
            e.w = distanta(cuv[i], cuv[j]);
            g << e.u << ' ' << e.v << ' ' << e.w << '\n';
            listaArce.push_back(e);
        }
    
    kruskal();

    cout << "k = ";
    cin >> k;

    sort(mst.begin(), mst.end(), myComp);

    int separare = -1;
    for (int i = 0; i < k - 1; i++)
    {
        separare = mst[mst.size() - 1].w;
        mst.pop_back();
    }

    for (int i = 1; i <= n; i++)
        visited[i] = false;

    nclusters = 0;
    for (int i = 1; i <= n; i++)
    {
        if (!visited[i])
        {
            dfs(i);
            nclusters++;
        }
    }

    for (int i = 0; i < nclusters; i++)
    {
        for (int j = 0; j < clusters[i].size(); j++)
            cout << cuv[clusters[i][j]] << ' ' << clusters[i][j] << '\t';
        cout << '\n';
    }
    cout << separare << '\n';

	return 0;
}