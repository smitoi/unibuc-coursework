/*
	Mitoi Stefan - Daniel
	Grupa 231
	Cuplaj maxim în graf bipărțit - problema 2, versiunea Edmonds Karp
*/

#include<bits/stdc++.h> 
#include <windows.h>

#define NMAX 100010
#define INF 0x3f3f3f3f

using namespace std;

ifstream f("graf.in");
ofstream g("graf.out");

typedef struct {
    int capacity;
    int flow;
    int source;
    int sink;
} edge;

int n, m, s, t;
vector<edge> 	listaArce[NMAX], listaCuplaje;
edge* pred[NMAX];

int     edmonds_karp() {
    int flow = 0;

    do {
        for (int i = 0; i <= 2 * n + 5; i++)
            pred[i] = NULL;

        queue<int> q = queue<int>();
        q.push(s);
        while (q.empty() != true) {
            int u = q.front();
            q.pop();
            for (int i = 0; i < listaArce[u].size(); i++) {
                edge e = listaArce[u][i];
                if (pred[e.sink] == NULL && e.sink != s && e.capacity > e.flow) {
                    pred[e.sink] = &listaArce[u][i];
                    // cout << e.sink << " = " << pred[e.sink] -> source << " -> " << pred[e.sink] -> sink << '\n';
                    q.push(e.sink);
                }
            }
        }

        // cout << "Trecut de BFS" << '\n';
        
        if (pred[t] != NULL) {
            int diff_flow = INF;

            for (edge* e = pred[t]; e != NULL; e = pred[e -> source]) {
                diff_flow = min(diff_flow, e -> capacity - e -> flow);
                // cout << "Mers pe muchia " << e -> source << " -> " << e -> sink << '\t' << e -> flow << '/' << e -> capacity << '\n';
            }

            for (edge* e = pred[t]; e != NULL; e = pred[e -> source]) {
                e -> flow += diff_flow;
                if (e -> source != s && e -> sink != t) {
                    listaCuplaje.push_back(*e);
                }
                // cout << "Adaugat " << diff_flow << " pe muchia " << e -> source << " -> " << e -> sink << '\t' << e -> flow << '/' << e -> capacity << '\n';
            }

            flow += diff_flow;
            // cout << "Flow = " << flow << '\n';
        }
    } while (pred[t] != NULL);

    return flow;
}

int         place[NMAX];
bool        visited[NMAX];

int		main()
{
    int flow = 0;

	f >> n >> m;
    s = n + 1;
    t = n + 2;
	// cout << "n = " << n << '\n';
    // cout << "s = " << s << '\n';
	// cout << "t = " << t << '\n';
	// cout << "m = " << m << '\n';

	for (int i = 0; i < m; i++) {
        int x, y;
        edge e;
        f >> x >> y;

        if (place[x] == 0 && place[y] == 0) {
            place[x] = 1;
            place[y] = 2;
        } else if (place[x] == 1) {
            place[y] = 2;
        } else if (place[y] == 1) {
            int z;
            place[x] = 2;
            z = y;
            y = x;
            y = z;
        }

        e.capacity = 1; e.flow = 0; e.source = x; e.sink = y;
        listaArce[x].push_back(e);
        // cout << "Adaugat muchia " << e.source << " -> " << e.sink << '\t' << e.flow << '/' << e.capacity << '\n';
        if (!visited[x]) {
            visited[x] = true;
            e.source = s; e.sink = x;
            listaArce[s].push_back(e);
            // cout << "Adaugat muchia " << e.source << " -> " << e.sink << '\t' << e.flow << '/' << e.capacity << '\n';
        }

        if (!visited[y]) {
            visited[y] = true;
            e.source = y; e.sink = t;
            listaArce[y].push_back(e);
            // cout << "Adaugat muchia " << e.source << " -> " << e.sink << '\t' << e.flow << '/' << e.capacity << '\n';
        }
    }

    cout << edmonds_karp() + flow << '\n';

    for (int i = 0; i < listaCuplaje.size(); i++) {
        cout << listaCuplaje[i].source << ' ' << listaCuplaje[i].sink << '\n';
    }

	return 0;
}