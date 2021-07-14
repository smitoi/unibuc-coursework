#include <bits/stdc++.h>

using	namespace std;

/// https://www.infoarena.ro/problema/mit

ifstream f("mit.in");
ofstream g("mit.out");

int rmq[20][100002];
int n, m;
int x, y, aux, op, z;

int	main()	
{
	f >> n >> m;
	
	for (int i = 0; i < n; i++)
		f >> rmq[0][i];
	
	for (int i = 1; (1 << i) <= n; i++)
		for (int j = 0; j < n - (1 << i) + 1; j++)
			rmq[i][j] = max(rmq[i - 1][j], rmq[i - 1][j + (1 << (i - 1))]);
	
   	for (int i = 0; i < m; i++)
	{		
		f >> op;
		if (op == 1)
		{
			f >> x >> y;
			if (x - y == 0)
				 g << rmq[0][x - 1] << '\n';
			else
			{
				aux = (int)log2(abs(x - y));
				g << max(rmq[aux][x - 1], rmq[aux][y - (1 << aux)]) << '\n';
			}
		}
		else if (op == 2)
		{
			f >> x >> y >> z;
			x--;
			for (int i = x; i < y; i++)
				rmq[0][i] += z;
	
			for (int i = 1; (1 << i) <= n; i++)
				for (int j = (x - (1 << i) + 1) > 0 ? (x - (1 << i) + 1) : 0; j < n - (1 << i) + 1; j++)
					rmq[i][j] = max(rmq[i - 1][j], rmq[i - 1][j + (1 << (i - 1))]);
		}
	}
	
    return 0;
	
}

