#include <bits/stdc++.h>

/// https://www.infoarena.ro/problema/proc2

using namespace std;
	
ifstream f("proc2.in");
ofstream g("proc2.out");
	
priority_queue<int, vector<int>, greater<int> > proces;
priority_queue<pair<int,int>, vector<pair<int,int> >, greater<pair<int,int> > > tasks;
int st, dr, pr, n, m;

int main()
{
    f >> n >> m;
    for(int i = 1; i <= n; i++)
        proces.push(i);

    for(int i = 0; i < m; i++)
    {
        f >> st >> fi;
        while(!tasks.empty() && st >= tasks.top().first)
		{
            proces.push(tasks.top().second);
            tasks.pop();
        }
        g << proces.top() << '\n';
        tasks.push({st + dr, proces.top()});
		proces.pop();
    }

    return 0;
	
}