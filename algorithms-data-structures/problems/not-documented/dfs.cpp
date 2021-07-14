#include <iostream>
#include <fstream>
#include <vector>
#include <queue>

#define NMAX 100010

using namespace std;

ifstream f("dfs.in");
ofstream g("dfs.out");

int             n, m;
int             compConex = 0;
vector<int>     listaArce[NMAX];
bool             vizitate[NMAX];

void    visit(int  n)
{
    vizitate[n] = true;
    for (int i = 0; i < listaArce[n].size(); i++)
        if (vizitate[listaArce[n][i]] == false)
            visit(listaArce[n][i]);
}

void    dfs()
{
    for (int i = 1; i <= n; i++)
    {
        if (vizitate[i] == false)
        {
            visit(i);
            compConex++;
        }
    }
    
    g << compConex;
}

// https://www.infoarena.ro/problema/dfs
// https://www.infoarena.ro/job_detail/2660664
int		main()
{
	f >> n >> m;
	
	for (unsigned int i = 0; i < m; i++)
	{
		int nodS, nodD;
		f >> nodS >> nodD;
        listaArce[nodS].push_back(nodD);
        listaArce[nodD].push_back(nodS);
	}

    dfs();
	return 0;
}