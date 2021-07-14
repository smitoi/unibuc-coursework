#include <iostream>
#include <fstream>
#include <vector>
#include <queue>

#define NMAX 100010

using namespace std;

ifstream f("sortaret.in");
ofstream g("sortaret.out");

vector<int>     listaArce[NMAX];
int             deg[NMAX];
vector<int>     l;
int     n, m;

void    topologicalSort()
{
	// Iau nodurile cu grad 0
    for (ssize_t i = 1; i <= n; i++)
        if (deg[i] == 0)
            l.push_back(i);
    
	// Parcurge toate nodurile
    for (ssize_t i = 0; i < l.size(); i++)
    {
		// Parcurge vecinii fiecarui nod
        for (ssize_t j = 0; j < listaArce[l[i]].size(); j++)
        {
			// Ii izolez si daca au gradul 0 ii iau
            deg[listaArce[l[i]][j]]--;
            if (deg[listaArce[l[i]][j]] == 0)
                l.push_back(listaArce[l[i]][j]);
        }
    }

    for (ssize_t i = 0; i < l.size(); i++)
        g << l[i] << ' ';
}

// https://www.infoarena.ro/problema/sortaret
// https://www.infoarena.ro/job_detail/2660659
int		main()
{
	f >> n >> m;
	
	for (unsigned int i = 0; i < m; i++)
	{
		int nodS, nodD;
		f >> nodS >> nodD;
        listaArce[nodS].push_back(nodD);
        deg[nodD]++;
	}

    topologicalSort();
	return 0;
}