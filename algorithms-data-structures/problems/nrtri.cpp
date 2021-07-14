#include <bits/stdc++.h>	

/// https://www.infoarena.ro/problema/nrtri

using	namespace std;
	
ifstream	f("nrtri.in");
ofstream	g("nrtri.out");
	

long int		n, v[801], nr;
int	main()
{

	nr = 0;
	f >> n;
	for (int i = 0; i < n; i++)
	
		f >> v[i];

	sort(v, v + n);

	for (int i = 0; i < n; i++)
		for (int j = i + 1; j < n; j++)
			for (int k = j + 1; k < n && v[i] + v[j] >= v[k]; k++)
				nr++;

	g << nr;
	return	0;
	
}