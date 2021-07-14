#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

#define NMAX 100010

using namespace std;

int n, m;
vector<int>     listaArce[NMAX];
vector<int>     permutari;
vector<int>     ordineDFS;
int             ordine[NMAX];
bool            vizitat[NMAX];

bool    cmp(int a, int b)
{
    return ordine[a] < ordine[b];
}

void    dfs(int i)
{
    vizitat[i] = true;
    ordineDFS.push_back(i);
    for (int j = 0; j < listaArce[i].size(); j++)
    {
        if (!vizitat[listaArce[i][j]])
        {
            dfs(listaArce[i][j]);
        }
    }
}

int     main()
{
    cin >> n >> m;
    
    for (int i = 0; i < n; i++)
    {
        int p;
        cin >> p;
        permutari.push_back(p);
        ordine[p] = i;
    }
    
    for (int i = 0; i < m; i++)
    {
        int a, b;
        cin >> a >> b;
        listaArce[a].push_back(b);
        listaArce[b].push_back(a);
    }
    
    for (int i = 0; i < m; i++)
    {
        sort(listaArce[i].begin(), listaArce[i].end(), cmp);
    }
    
    dfs(1);

    for (int i = 0; i < n; i++)
    {
        if (permutari[i] != ordineDFS[i])
        {
            cout << 0;
            return 0;
        }
    }
    cout << 1;
    return 0;
}