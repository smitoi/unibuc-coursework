#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <cstring>

#define NMAX 1010
#define INF 2147483647
using namespace std;

ifstream f("rj.in");
ofstream g("rj.out");

int             n, m;
char            row[256];
int romeo[100][100];
int julieta[100][100];

// https://www.infoarena.ro/problema/rj
// https://www.infoarena.ro/job_detail/2663912
int		main()
{
	f >> n >> m;
    f.get();
    
    int rSx, rSy, jSx, jSy;

    for (int i = 0; i < n; i++)
    {
        f.getline(row, 256);
        for (int j = 0; j < m; j++)
        {
            if (row[j] == 'X')
            {
                romeo[i][j] = -1;
                julieta[i][j] = -1;
            }
            else if (row[j] == 'R')
            {
                rSx = i;
                rSy = j;
                julieta[i][j] = INF;
            }
            else if (row[j] == 'J')
            {
                jSx = i;
                jSy = j;
                romeo[i][j] = INF;
            }
            else
            {
                romeo[i][j] = INF;
                julieta[i][j] = INF;
            }
        }
    }

    queue <pair<int, int>> que;
    pair<int, int> poz, aux;
    julieta[jSx][jSy] = 0;
    que.push(pair<int, int>(jSx, jSy));

    while (!que.empty())
    {
        poz = que.front();
        que.pop();
        
        for (int ox = -1; ox <= 1; ox++)
            for (int oy = -1; oy <= 1; oy++)
            {
                aux = pair<int, int> (poz.first + ox, poz.second + oy);
                if (((ox != 0 && oy != 0) || (ox != oy)) && 
                (aux.first < n && aux.first >= 0) &&
                (aux.second < m && aux.second >= 0) &&
                julieta[aux.first][aux.second] != -1)
                {
                    if (julieta[poz.first][poz.second] + 1 < julieta[aux.first][aux.second])
                    {
                        julieta[aux.first][aux.second] = julieta[poz.first][poz.second] + 1;
                        que.push(aux);
                    }
                }
            }
    }

    romeo[rSx][rSy] = 0;
    que.push(pair<int, int>(rSx, rSy));

    while (!que.empty())
    {
        poz = que.front();
        que.pop();
        
        for (int ox = -1; ox <= 1; ox++)
            for (int oy = -1; oy <= 1; oy++)
            {
                aux = pair<int, int> (poz.first + ox, poz.second + oy);
                if (((ox != 0 && oy != 0) || (ox != oy)) && 
                (aux.first < n && aux.first >= 0) &&
                (aux.second < m && aux.second >= 0) &&
                romeo[aux.first][aux.second] != -1)
                {
                    if (romeo[poz.first][poz.second] + 1 < romeo[aux.first][aux.second])
                    {
                        romeo[aux.first][aux.second] = romeo[poz.first][poz.second] + 1;
                        que.push(aux);
                    }
                }
            }
    }

    int minim = INF;
    int minX = -1, minY = -1;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
        {
            if (romeo[i][j] == julieta[i][j] && romeo[i][j] < minim && romeo[i][j] != -1)
            {
                minX = i;
                minY = j;
                minim = romeo[i][j];
            }
        }
    g << minim + 1 << ' ' << minX + 1 << ' ' << minY + 1;
	return 0;
}