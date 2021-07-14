/*
	Mitoi Stefan - Daniel
	Grupa 231
	Fluxuri în reţele de transport - problema 1
*/

#include<bits/stdc++.h> 

#define NMAX 1010
#define INF 0x3f3f3f3f

using namespace std;

ifstream f("retea.in");
ofstream g("retea.out");

class edge {
    public:
        int capacity;
        int flow;
        int source;
        int sink;
        // edge* reverse;
        bool reverse;
};

int n, m, s, t;
vector<edge> 	listaArce[NMAX], listaMuchii;
edge* pred[NMAX];

bool bfs() {
    bool visited[NMAX];
    // cout << "Inceput BFS" << '\n';
    for (int i = 0; i <= n; i++) {
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

                for (int i = 0; i < listaArce[e -> sink].size(); i++) {
                    if (listaArce[e -> sink][i].source == e -> source && listaArce[e -> sink][i].sink == e -> sink) {
                        listaArce[e -> sink][i].flow -= diffFlow;
                        break;
                    }
                }
                // cout << "Adaugat " << diffFlow << " pe muchia " << e -> source << " -> " << e -> sink << '\t' << e -> flow << '/' << e -> capacity << '\n';
                // cout << "Scazut " << diffFlow << " pe muchia " << e -> sink << " -> " << e -> source << '\t';

            }
            flow += diffFlow;
            // cout << "Flow = " << flow << '\n';
        }
    } while (pred[t] != NULL);

    return flow;
}

bool visited[NMAX];

void    dfs(int s) {
    visited[s] = true;
    // cout << "Vizitat nodul " << s << '\n';
    for (int i = 0; i < listaArce[s].size(); i++)
        if (!visited[listaArce[s][i].sink] && (listaArce[s][i].flow < listaArce[s][i].capacity) && !listaArce[s][i].reverse)
            dfs(listaArce[s][i].sink);
}

void    find_min_cut() {
    dfs(s);

    for (int i = 1; i <= n; i++) {
        for (int j = 0; j < listaArce[i].size(); j++) {
            if (visited[i] && !visited[listaArce[i][j].sink] && listaArce[i][j].capacity) {
                cout << listaArce[i][j].source << ' ' << listaArce[i][j].sink << '\n';
            }
        }
    }
}

int     g_in[NMAX], g_out[NMAX];

int		main()
{
    int flow = 0;

	f >> n >> s >> t >> m;
	// cout << "n = " << n << '\n';
    // cout << "s = " << s << '\n';
	// cout << "t = " << t << '\n';
	// cout << "m = " << m << '\n';

	for (int i = 0; i < m; i++) {
        int x, y, c, s;
        edge e;
        edge er;
        f >> x >> y >> c >> s;
        // cout << "Citit muchia " << x << " -> " << y << '\t' << s << '/' << c << '\n';
        e.capacity = c; e.flow = s; e.sink = y; e.source = x; e.reverse = false;
        if (y == t) {
            flow += s;
            // cout << "Adaugat flow " << s << '\n';
        }
        listaArce[x].push_back(e);
        er.capacity = s; er.flow = 0; er.sink = x; er.source = y;
        er.reverse = true;
        listaArce[y].push_back(er);
        // cout << "Adaugat muchia " << x << " -> " << y << '\t' << s << '/' << c << '\n';
        if (s > c) {
            cout << "NU\n";
            return 0;
        }
        g_in[x] += e.flow;
        g_out[y] += e.flow;
    }

    for (int i = 1; i <= n; i++) {
        if (g_in[i] != g_out[i] && i != s && i != t) {
            cout << "NU\n";
            return 0;
        }
    }

    int max_flow = edmonds_karp() + flow;
    cout << max_flow << '\n';

    for (int i = 1; i <= n; i++) {
        for (int j = 0; j < listaArce[i].size(); j++) {
            edge e = listaArce[i][j];
            if (!e.reverse) {
                cout << e.source << ' ' << e.sink << ' ' << e.flow << '\n';
            }
        }
    }

    cout << max_flow << '\n';
    find_min_cut();
	return 0;
}