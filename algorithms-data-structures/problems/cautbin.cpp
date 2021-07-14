#include <bits/stdc++.h>

/// https://www.infoarena.ro/problema/cautbin

using	namespace std;

long long int	v[100002];
ifstream	f("cautbin.in");
ofstream	g("cautbin.out");
int			op;
long long int	n, m;
long long int nr, x;

long long int	cautbin()
{
	long long int dr = n - 1, st = 0;
	long long int mij;
	
	if (op == 0)
	{
		while (st <= dr)
		{
			mij = st + (dr - st) / 2;

			if (v[mij] == x && mij == (n - 1) || v[mij] == x && v[mij + 1] != x)
				return mij + 1;
			
			if (v[mij] <= x)
				st = mij + 1;
			else
				dr = mij - 1;
			
			mij = st / 2 + dr / 2;
		}
		
		return -1;
	}
	else if (op == 1)
	{
		while (st <= dr)
		{
			mij = st + (dr - st) / 2;
			
			if (v[mij] <= x && mij == (n - 1) || v[mij] <= x && v[mij + 1] > x)
				return mij + 1;
			
			if (v[mij] <= x)
				st = mij + 1;
			else
				dr = mij - 1;
			
			mij = st / 2 + dr / 2;
		}
		
		return -1;
	}
	else if (op == 2)
	{
		while (st <= dr)
		{
			mij = st + (dr - st) / 2;
			
			if (v[mij] >= x && mij == 0 || v[mij] >= x && v[mij - 1] < x)
				return mij + 1;
			
			if (v[mij] >= x)
				dr = mij - 1;
			else
				st = mij + 1;
			
			mij = st / 2 + dr / 2;
		}
		
		return -1;
	}
}

int	main()
{
	f >> n;

	
	for (register long long int index = 0; index < n; index++)
	{
		f >> v[index];
	}
	
	f >> m;
	for (register long long int index = 0; index < m; index++)
	{
		f >> op >> x;
		g << cautbin() << '\n';
	}

	return	0;
}
