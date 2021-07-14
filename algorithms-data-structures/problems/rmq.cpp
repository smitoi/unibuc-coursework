#include <bits/stdc++.h>

using	namespace std;

/// https://www.infoarena.ro/problema/rmq
/// TIL (1 << n) = 2^n

ifstream f("rmq.in");
ofstream g("rmq.out");

int rmq[20][100002];
int n, m;
int x, y, aux;

int	main()	
{
	f >> n >> m;
	
	for (int i = 0; i < n; i++)
		f >> rmq[0][i];
	
	for (int i = 1; (1 << i) <= n; i++)
		for (int j = 0; j < n - (1 << i) + 1; j++)
			rmq[i][j] = min(rmq[i - 1][j], rmq[i - 1][j + (1 << (i - 1))]);
	
   	for (int i = 0; i < m; i++)
	{
		f >> x >> y;
		if (x - y == 0)
			 g << rmq[0][x - 1] << '\n';
		else
		{
			aux = (int)log2(abs(x - y));
			g << min(rmq[aux][x - 1], rmq[aux][y - (1 << aux)])<<"\n";
		}
	}
	
    return 0;
	
}

