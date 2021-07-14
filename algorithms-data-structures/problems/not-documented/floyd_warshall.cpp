/*
	Mitoi Stefan - Daniel
	Grupa 231
	Drumuri minime - problema 5
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <queue>

#define NMAX 100010
#define INF 0x3f3f3f3f

using namespace std;

ifstream f("grafpond.in");
ofstream g("grafpond.out");

/*
    Complexitatea algoritmului este O(n^3), aceea a algoritmului Floyd-Warshall. 
    Problema este rezolvată corect întrucât după aplicarea algoritmului Floyd-Warshall, care ne află toate drumurile de la fiecare nod către oricare alt nod, tot ce ne rămâne de făcut este să aplicăm formulele pentru centru, rază, diametru și afisarea lanțului diametral.
*/

int     n, m; // n - nr. de noduri, m - nr. de muchii
vector<vector<int>>     graf, dist; // graf - matrice de adiacenta, dist - distantele aflate de catre Floyd-Warshall
vector<vector<vector<int>>> drumuri; // un vector de vectori de vectori, unde drumuri[i][j] este vectorul lantului minim de la i la j

void floydWarshall ()  
{  
    int i, j, k;  
    dist.resize(n + 1);

    for (int i = 1; i <= n; i++)
        dist[i].resize(n + 1);

    // Distanta de la i la j este cea din graf (infinit sau cea a muchiei (i, j) in cazul in care aceasta exista)
    // De asemenea, drumul i - j este compus doar din muchia (i, j) initial
    for (i = 1; i <= n; i++)  
        for (j = 1; j <= n; j++)
        {  
            dist[i][j] = graf[i][j]; 
            drumuri[i][j].push_back(i);
            drumuri[i][j].push_back(j);
        } 
    
    for (int k = 1; k <= n; k++)  
    {  
        for (int i = 1; i <= n; i++)  
        {  
            for (int j = 1; j <= n; j++)  
            {  
                // Daca distanta trecand prin muchiile (i, k) si (k, j) este mai buna decat prin muchia (i, j)
                // Schimbam distanta si modificam drumul sa includa nodurile de pe drumul (i, k) si (k, j)
                if (dist[i][k] + dist[k][j] < dist[i][j]) 
                {
                    vector<int> drum_aux;
                    dist[i][j] = dist[i][k] + dist[k][j];
                    for (int v = 0; v < drumuri[i][k].size(); v++)
                        drum_aux.push_back(drumuri[i][k][v]);
                    for (int v = 1; v < drumuri[k][j].size(); v++)
                        drum_aux.push_back(drumuri[k][j][v]);
                    drumuri[i][j] = drum_aux;
                }  
            }  
        }  
    }  
    
    // Afisam distantele
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
            if (dist[i][j] == INF)
                cout << -1 << '\t';
            else
                cout << dist[i][j] << '\t';
        cout << '\n';
    }
}  

// Determina minimul dintr-un vector
int minimum(vector<int> v)
{
    int min = INF;
    for (int i = 1; i < v.size(); i++)
        if (v[i] < min)
            min = v[i];
    return min;
}

// Determina maximul dintr-un vector
int maximum(vector<int> v)
{
    int max = 0;
    for (int i = 1; i < v.size(); i++)
        if (v[i] > max)
            max = v[i];
    return max;
}

int main()  
{  
    // Citim numarul de noduri si de muchii si initializam vectorii
    f >> n >> m;
    graf.resize(n + 1);
    dist.resize(n + 1);
    drumuri.resize(n + 1);

    for (int i = 1; i <= n; i++)
    {
        graf[i] = vector<int>(n + 1, INF);
        drumuri[i] = vector<vector<int>>(n + 1);
    }
    
    for (int i = 1; i <= n; i++)
        graf[i][i] = 0;

    // Citim muchiile si le punem in matricea de adiacenta
    for (int i = 0; i < m; i++)
    {
        int a, b, w;
        f >> a >> b >> w;
        graf[a][b] = w;
        graf[b][a] = w;
    }

    // Aplicam algoritmul Roy-Floyd-Warhsall
    floydWarshall(); 

    vector<int> centru;
    vector<int> excen;

    // Aflam excentritatea nodurilor
    for (int i = 1; i <= n; i++)
        excen.push_back(maximum(dist[i]));

    // Aflam raza (minimul dintre toate excentritatile) si diametrul (maximul dintre toate excentritatile)
    int raza = minimum(excen);
    int diam = maximum(excen);

    // Aflam nodurile care fac parte din centru
    for (int i = 0; i < n; i++)
        if (excen[i] == raza)
            centru.push_back(i + 1);
    
    cout << "Raza = " << raza << '\n';
    cout << "Diametru = " << diam << '\n';

    cout << "Excentricitate: ";
    for (int i = 0; i < excen.size(); i++)
    {
        cout << excen[i];
        if (i != excen.size() - 1)
            cout << ", ";
    }
    cout << '\n';

    cout << "Centrul grafului: ";
    for (int i = 0; i < centru.size(); i++)
    {
        cout << centru[i];
        if (i != centru.size() - 1)
            cout << ", ";
    }
    cout << '\n';

    // Aflam lanturile diametrale (lanturi unde distanta e egala cu diametrul)
    cout << "Lanturi diametrale: \n";
    int lun = -1;
    vector<int> drum;
    for (int i = 1; i <= n; i++)
    {
        for (int j = i + 1; j <= n; j++)
        {
            if (dist[i][j] == diam)
            {
                cout << "Drumul de la " << i << " la " << j << ": ";
                for (int k = 0; k < drumuri[i][j].size(); k++)
                {
                    cout << drumuri[i][j][k];
                    if (k != drumuri[i][j].size() - 1)
                        cout << ", ";
                }
                cout << '\n';
            }
        }
    }
    return 0;  
} 
