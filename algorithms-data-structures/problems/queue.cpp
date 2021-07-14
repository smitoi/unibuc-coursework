#include <bits/stdc++.h>
#include <stack>

using	namespace std;

/// https://www.infoarena.ro/problema/queue

stack<int> s1, s2;
char		c[100];
int			n;
int			nr, wr;
ifstream f("queue.in");
ofstream g("queue.out");

void	showStack(stack<int> s1, stack<int> s2)
{
	g << "s1: ";
	while (!s1.empty())
	{
		g << s1.top() << ' ';
		s1.pop();
	}
	g << '\n';
	g << "s2: ";
	while (!s2.empty())
	{
		g << s2.top() << ' ';
		s2.pop();
	}
	g << '\n';
}

void	push(int s, int n)
{
	g << "push(" << s << "," << n << ") ";
}

void	pop(int s)
{
	g << "pop(" << s << ") ";
}

void	read(int n)
{
	g << "read(" << n << ") ";
}

void	write(int n)
{
	g << "write(" << n << ") ";
}

void	push_back(int n)
{
	s1.push(n);
	read(nr);
	push(1, n);
	g << '\n';
	// showStack(s1, s2);
}

void	pop_front()
{
	if (s2.empty())
	{
		while (s1.size() != 1)
		{
			wr = s1.top();
			pop(1);
			push(2, wr);
			s2.push(wr);
			s1.pop();
		}
		wr = s1.top();
		pop(1);
		write(wr);
		s1.pop();
		g << '\n';
	}
	else
	{
		wr = s2.top();
		pop(2);
		write(wr);
		s2.pop();
		g << '\n';
	}
	// showStack(s1, s2);
}

int	main()	
{
	f >> n;
	
	for (int i = 0; i < n; i++)
	{
		f >> c;
		g << i + 1 << ": ";
		if (c[1] == 'u')
		{
			nr = atoi(c + 10);
			push_back(nr);
		}
		else
			pop_front();
	}
	
	return	0;
	
}