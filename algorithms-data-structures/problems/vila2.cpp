#include <bits/stdc++.h>
#include <deque>

/// https://www.infoarena.ro/problema/vila2

using	namespace std;

deque<int> m, M;
int		n, k;
int		dif;
int		v[1000001];
ifstream f("vila2.in");
ofstream g("vila2.out");

int	main()
{
	f >> n >> k;
	
	for (int i = 0; i < n; i++)
	{
		f >> v[i];
		
		while (!m.empty() && v[i] <= v[m.front()])
			m.pop_back();
		while (!M.empty() && v[i] >= v[M.front()])
			M.pop_back();
		
		m.push_back(i);
		M.push_back(i);
		
		if (i - m.front() == k + 1)
			m.pop_front();
		if (i - M.front()  == k + 1)
			M.pop_front();
	
		if (abs(v[M.front()] - v[m.front()]) > dif)
			dif = abs(v[M.front()] - v[m.front()]);
	}
	
	g << dif;
	return	0;
}
