/*
	Mitoi Stefan - Daniel
	Grupa 231
	Construcţia unui graf orientat - problema 3
*/

#include<bits/stdc++.h> 
#include <windows.h>

#define NMAX 100010
#define INF 0x3f3f3f3f

using namespace std;

ifstream f("suplimentar.in");
ofstream g("suplimentar.out");

class edge {
    public:
        int capacity;
        int flow;
        int source;
        int sink;
};

int n, s, t;
vector<edge> 	listaArce[NMAX], listaCuplaje;
edge* pred[NMAX];

bool bfs() {
    bool visited[NMAX];
    // cout << "Inceput BFS" << '\n';
    for (int i = 0; i <= 2 * n + 2; i++) {
        visited[i] = false; 
        pred[i] = NULL;
    }

    queue<int> q = queue<int>();
    q.push(s);
    visited[s] = true;

    while (q.empty() != true) {
        int u = q.front();
        q.pop();

        // cout << "Vizitat nod " << u << '\n';

        for (int i = 0; i < listaArce[u].size(); i++) {
            if (listaArce[u][i].flow == listaArce[u][i].capacity || pred[listaArce[u][i].sink] != NULL || listaArce[u][i].sink == s)
                continue;
            
            // cout << "Adaugat predecesor pentru " << listaArce[u][i].sink;

            pred[listaArce[u][i].sink] = &listaArce[u][i];
            visited[listaArce[u][i].sink] = true;

            if (listaArce[u][i].sink == t) {
                // cout << "BFS terminat cu succes\n";
                return true;
            }

            q.push(listaArce[u][i].sink);
        }
    }

    return false;
}

int     edmonds_karp() {
    int flow = 0;

    do {
        bool _bfs = bfs();

        if (_bfs == false) {
            break;
        }
        
        if (pred[t] != NULL) {
            int diffFlow = INF;

            for (edge* e = pred[t]; e != NULL; e = pred[e -> source]) {
                diffFlow = min(diffFlow, e -> capacity - e -> flow);
                // cout << "Verificam muchia " << e -> source << " -> " << e -> sink << '\t' << e -> flow << '/' << e -> capacity << '\n';
            }
            
            for (edge* e = pred[t]; e != NULL; e = pred[e -> source]) {
                e -> flow += diffFlow;
                if (e -> source != s && e -> sink != t) {
                    listaCuplaje.push_back(*e);
                }
                // cout << "Adaugat " << diff_flow << " pe muchia " << e -> source << " -> " << e -> sink << '\t' << e -> flow << '/' << e -> capacity << '\n';
            }

            flow += diffFlow;
            // cout << "Flow = " << flow << '\n';
        }
    } while (pred[t] != NULL);

    return flow;
}

int		main()
{
    int g_in = 0, g_out = 0;
    int flow = 0;
    f >> n;
    s = 2 * n + 1;
    t = 2 * n + 2;

	// cout << "n = " << n << '\n';
    // cout << "s = " << s << '\n';
	// cout << "t = " << t << '\n';
	// cout << "m = " << m << '\n';

	for (int i = 1; i <= n; i++) {
        int x, y;
        edge e;
        f >> x >> y; // x - grad iesire, y - grad intrare
        g_out += x; g_in += y;

        e.capacity = x; e.flow = 0; e.source = s; e.sink = i;
        listaArce[s].push_back(e);
        // cout << "Adaugat muchia " << e.source << " -> " << e.sink << '\t' << e.flow << '/' << e.capacity << '\n';
        e.capacity = y; e.flow = 0; e.source = i + n; e.sink = t;
        listaArce[i + n].push_back(e);
        // cout << "Adaugat muchia " << e.source << " -> " << e.sink << '\t' << e.flow << '/' << e.capacity << '\n';

        for (int j = 1; j <= n; j++) {
            if (i != j) {
                e.capacity = 1; e.flow = 0; e.source = i; e.sink = j + n;
                listaArce[i].push_back(e);
                // cout << "Adaugat muchia " << e.source << " -> " << e.sink << '\t' << e.flow << '/' << e.capacity << '\n';
            }
        }
    }

    if (g_in != g_out) {
        // cout << "Nu are solutie" << '\n';
        return 0;
    }

    cout << edmonds_karp() << '\n';

    for (int i = 0; i < listaCuplaje.size(); i++) {
        cout << listaCuplaje[i].source << ' ' << listaCuplaje[i].sink - n << '\n';
    }
	return 0;
}