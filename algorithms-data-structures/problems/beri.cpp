#include <bits/stdc++.h>
#include <algorithm>

using	namespace std;

/// https://www.infoarena.ro/problema/beri
/// Reference: http://www.cplusplus.com/reference/algorithm/nth_element/

long long int		n;
long long int		k;
long long int		q;
long long int		x, y, z;
long long int		v[1000001];
ifstream	f("beri.in");
ofstream	g("beri.out");
	
int	main()	
{
	f >> n >> k >> q >> x >> y >> z;
	long long int	suma = 0;
	v[0] = q;
	
	for (register long long int index = 1; index < n; index++)
		v[index] = (v[index - 1] * x + y) % z + k;
	
	nth_element (v, v + n - k - 1, v + n);

	for (register long long int index = n - 1; index > n - k - 1; index--)
		suma += v[index];

	suma -= (k * (k - 1)) / 2;
	
	g << suma;
	
	return	0;
	
}