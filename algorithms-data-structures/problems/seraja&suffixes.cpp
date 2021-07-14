#include <bits/stdc++.h>
#include <set>

/// https://codeforces.com/contest/368/problem/B

using	namespace std;

int m, n, v[100001];

int	main()
{
	set<int> w;
	cin >> n >> m;
	
	for (int i = 0; i < n; i++)
		cin >> v[i];
	
	for (int i = n - 1; i > -1; i--)
	{
		w.insert(v[i]);
		v[i] = w.size();
	}
	
	for (int i = 0; i < m; i++)
	{
		cin >> n;
		cout << v[n - 1] << '\n';
	}
	
	return 0;
}
