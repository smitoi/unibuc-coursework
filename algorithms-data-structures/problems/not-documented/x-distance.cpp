#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

#define NMAX 100010

int                     n, m, x, nr_noduri;
vector<pair<int,int>>   listaArce[NMAX];
bool                    vizitate[NMAX];

void dfs(int nod, int max) {
    nr_noduri++;
    vizitate[nod] = 1;

    for (int i = 0; i < listaArce[nod].size(); i++) 
    {
        if (!vizitate[listaArce[nod][i].first] && listaArce[nod][i].second <= max) 
            dfs(listaArce[nod][i].first, max);
    }
}

long long int sol(int max) {

    for (int i = 1; i <= n; i++)
        vizitate[i] = false;

    long long int rez = 0;
    for (int i = 1; i <= n; i++) {
        if (vizitate[i] == false) 
        {
            nr_noduri = 0;
            dfs(i, max);
            rez += 1LL * nr_noduri * (nr_noduri - 1) / 2;
        }
    }

    return rez;
}

int main() 
{
    cin >> n >> m >> x;

    for(int i = 0; i < m; i++) {
        int a, b, w;
        cin >> a >> b >> w;
        if (w <= x)
        {
            listaArce[a].push_back(pair<int, int> (b, w));
            listaArce[b].push_back(pair<int, int> (a, w));
        }
        
    }

    long long int big = sol (x);
    long long int small = sol (x-1);

    cout << big - small;

    return 0;
}