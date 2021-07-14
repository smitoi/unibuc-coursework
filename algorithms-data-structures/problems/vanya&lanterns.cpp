#include <bits/stdc++.h> 

/// https://codeforces.com/problemset/problem/492/B

using namespace std;

int		v[1001];
int		n;
long	l;
double	maxim;

int main()
{
	cin >> n;
	cin >> l;
	
	for (int i = 0; i < n; i++)
		cin >> v[i];
	
	sort(v, v + n);
	
	for (int i = 0; i < n - 1; i++)
		maxim = max(maxim, (v[i + 1] - v[i]) / 2.0);
	
	maxim = max(maxim, (l - v[n - 1]) / 1.0);
	maxim = max(maxim, (v[0]) / 1.0);
	cout << fixed << maxim;
	return 0;
}