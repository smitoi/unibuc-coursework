/*
	Mitoi Stefan - Daniel
	Grupa 231
    Arbori parțiali de cost minim - problema 2, versiunea O(n^2)
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <algorithm>

#define NMAX 101
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
vector<edge>            mst;
int                     weight[NMAX], parent[NMAX];
int                     mat[NMAX][NMAX];
bool                    inmst[NMAX];

void    prim()
{
    for (int i = 1; i <= n; i++)
    {
        weight[i] = INF;
        inmst[i] = false;
        parent[i] = -1;
    }

    for (int i = 1; i <= n; i++)
    {
        inmst[i] = true;

        for (int j = 1; j <= n; j++)
        {
            if (mat[i][j] != -1 && !inmst[j] && mat[i][j] < weight[j])
            {
                parent[j] = i;
                weight[j] = mat[i][j];
            }
        }
    }

    int cost = 0;
    for (int i = 1; i <= n; i++)
        if (parent[i] != -1)
        {
            cout << parent[i] << " - " << i << '\t' << mat[parent[i]][i] << '\n';
            cost += mat[parent[i]][i];
        }
    cout << "Cost total = " << cost << '\n';
}

int		main()
{
	f >> n >> m;

    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            mat[i][j] = -1;

	for (int i = 0; i < m; i++)
	{
		edge e;
		f >> e.u >> e.v >> e.w;
		mat[e.u][e.v] = e.w;
        mat[e.v][e.u] = e.w;
	}

    prim();

	return 0;
}