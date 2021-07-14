#include <bits/stdc++.h>

/// https://www.infoarena.ro/problema/paranteze

using namespace std;

ifstream f("paranteze.in");
ofstream g("paranteze.out");
stack<char> v;
int  fs[1000001];
char s[1000001];
int  n, k = 0;
int maxim;
	
int main()
{
	f >> n;
	f >> s;
	maxim = 0;
	fs[k] = 0;
	k++;
	for (int i = 0; i < n; i++)
	{
		if (s[i] == ')' && !v.empty() && v.top() == '(')
		{
			v.pop();
			fs[k] = -1;
			k--;
		}
		else if (s[i] == ']' && !v.empty() && v.top() == '[')
		{
			v.pop();
			fs[k] = -1;
			k--;
		}
		else if (s[i] == '}' && !v.empty() && v.top() == '{')
		{
			v.pop();
			fs[k] = -1;
			k--;
		}
		else 
		{
			v.push(s[i]);
			fs[k] = i + 1;
			k++;
		}
	}
	
	fs[k] = strlen(s) + 1;
	k++;
	for (int i = k - 1; i > 0; i--)
		maxim = max(maxim, abs(fs[i] - fs[i - 1] - 1));
	
	
	g << maxim;
	return 0;
}