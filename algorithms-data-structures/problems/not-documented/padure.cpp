#include <iostream>
#include <fstream>
#include <vector>
#include <deque>
#include <cstring>

#define NMAX 1010
#define INF 2147483647
using namespace std;

ifstream f("padure.in");
ofstream g("padure.out");

int     N, M, pl, pc, cl, cc;
int     padure[NMAX][NMAX];
int     cost[NMAX][NMAX];
deque<pair<int, int>> deq;

void    parcurge ()
{
    pair<int, int> poz, aux;
    cost[pl][pc] = 0;
    deq.push_back(pair<int, int>(pl, pc));

    while (!deq.empty())
    {
        poz = deq.front();
        deq.pop_front();
        
        for (int ox = -1; ox <= 1; ox++)
            for (int oy = -1; oy <= 1; oy++)
            {
                aux = pair<int, int> (poz.first + ox, poz.second + oy);
                if (ox != oy && (ox * oy) == 0 && 
                (aux.first <= N && aux.first >= 1) &&
                (aux.second <= M && aux.second >= 1))
                {
                    if (cost[poz.first][poz.second] + 1 < cost[aux.first][aux.second] && 
                    padure[poz.first][poz.second] != padure[aux.first][aux.second])
                    {
                        cost[aux.first][aux.second] = cost[poz.first][poz.second] + 1;
                        deq.push_back(aux);
                    }
                    else if (cost[poz.first][poz.second] < cost[aux.first][aux.second] &&
                    padure[poz.first][poz.second] == padure[aux.first][aux.second])
                    {
                        cost[aux.first][aux.second] = cost[poz.first][poz.second];
                        deq.push_front(aux);
                    }
                }
            }
    }
}

// https://www.infoarena.ro/problema/padure
// https://www.infoarena.ro/job_detail/2663755
int		main()
{
	f >> N >> M >> pl >> pc >> cl >> cc;

    for (int i = 1; i <= N; i++)
        for (int j = 1; j <= M; j++)
        {
            f >> padure[i][j];
            cost[i][j] = INF;
        }

    parcurge ();

    /*
    for (int i = 1; i <= N; i++)
    {
        for (int j = 1; j <= M; j++)
            g << cost[i][j] << ' ';
        g << '\n';  
    }
    */

    g << cost[cl][cc];

	return 0;
}