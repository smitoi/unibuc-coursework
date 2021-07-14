#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <cstring>

#define NMAX 1024
#define INF 2147483647
using namespace std;

int     n, m, k, x, y;
vector<pair<int, int>>  special;
char    row[NMAX];
int     matrice[NMAX][NMAX];


void    parcurge (int x, int y)
{
    queue<pair<int, int>> que;
    pair<int, int> poz, aux;
    matrice[x][y] = 0;
    que.push(pair<int, int>(x, y));

    while (!que.empty())
    {
        poz = que.front();
        que.pop();

        for (int ox = -1; ox <= 1; ox++)
            for (int oy = -1; oy <= 1; oy++)
            {
                aux = pair<int, int> (poz.first + ox, poz.second + oy);
                if (ox != oy && (ox * oy) == 0 &&
                (aux.first < n && aux.first >= 0) &&
                (aux.second < m && aux.second >= 0) && 
                matrice[aux.first][aux.second] != -1)
                {
                    if (matrice[poz.first][poz.second] + 1 < matrice[aux.first][aux.second])
                    {
                        matrice[aux.first][aux.second] = matrice[poz.first][poz.second] + 1;
                        que.push(aux);
                    }
                }
            }
    }
}

// https://csacademy.com/contest/archive/task/matrix_exploration
int		main()
{
	cin >> n >> m >> k;
    cin.get();

    for (int i = 0; i < n; i++)
    {
        cin.getline(row, 1024);
        for (int j = 0; j < m; j++)
        {
            if (row[j] == '#')
            {
                matrice[i][j] = -1;
            }
            else
            {
                matrice[i][j] = INF;
            }
        }
    }

    for (int i = 0; i < k; i++)
    {
        int auxX, auxY;
        cin >> auxX >> auxY;
        special.push_back(pair<int, int>(auxX - 1, auxY - 1));
    }

    for (int i = 0; i < special.size(); i++)
        parcurge (special[i].first, special[i].second);

    int s = 0;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            matrice[i][j] != -1 ? s += matrice[i][j] : s;

   cout << s;

	return 0;
}