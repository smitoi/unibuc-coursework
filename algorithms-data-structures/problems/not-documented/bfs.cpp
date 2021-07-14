#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <cstring>

#define NMAX 100010
using namespace std;

ifstream f("bfs.in");
ofstream g("bfs.out");

vector<int>		listaArce[NMAX];
int				n, m, s;
queue<int>			coadaNoduri;
int				costuri[NMAX];

void	bfs(int	nodStart)
{
	coadaNoduri.push(nodStart);
	costuri[coadaNoduri.front()] = 0;
	
	while (!coadaNoduri.empty())
	{
		for (int i = 0; i < listaArce[coadaNoduri.front()].size(); i++)
		{
			if (costuri[listaArce[coadaNoduri.front()][i]] == -1)
			{
				costuri[listaArce[coadaNoduri.front()][i]] = costuri[coadaNoduri.front()] + 1;
				coadaNoduri.push(listaArce[coadaNoduri.front()][i]);
			}
		}
		coadaNoduri.pop();
	}
	
	for (int i = 1; i <= n; i++)
		g << costuri[i] << ' ';
}

// https://www.infoarena.ro/problema/bfs
// https://www.infoarena.ro/job_detail/2660637
int		main()
{
	f >> n >> m >> s;
	
	for (unsigned int i = 0; i < m; i++)
	{
		int nodS, nodD;
		f >> nodS >> nodD;
		listaArce[nodS].push_back(nodD);
	}
	memset(costuri, -1, sizeof(costuri));  
	
	bfs(s);
	return 0;
}