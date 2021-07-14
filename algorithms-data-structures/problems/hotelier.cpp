#include <bits/stdc++.h>

/// https://codeforces.com/problemset/problem/1200/A)

using	namespace std;

int	r, l, R[10];
int	n;
char op[100001];

int	findL()
{
	for (int i = 0; i < 10; i++)
		if (R[i] == 0)
			return i;
	return -1;
}

int	findR()
{
	for (int i = 9; i > -1; i--)
		if (R[i] == 0)
			return i;
	return -1;
}

int	main()
{
	cin >> n;
	cin >> op;
	
	for (int i = 0; i < n; i++)
	{
		if (op[i] == 'L')
			R[findL()] = 1;
		else if (op[i] == 'R')
			R[findR()] = 1;
		else if (op[i] >= '0' && op[i] <= '9')
			R[op[i] - '0'] = 0;
	}
	
	for (int i = 0; i < 10; i++)
		cout << R[i];
	
	return 0;
}
