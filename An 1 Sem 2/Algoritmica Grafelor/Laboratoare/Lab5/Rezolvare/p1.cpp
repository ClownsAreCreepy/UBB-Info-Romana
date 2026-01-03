#include <fstream>
#include <vector>
#include <queue>
#include <limits>

using namespace std;

constexpr int INF = numeric_limits<int>::max();

int bfs(int s, int t, const vector<vector<int> > &capacitate, const vector<vector<int> > &adj, vector<int> &parinte) {
    fill(parinte.begin(), parinte.end(), -1);
    parinte[s] = -2;
    queue<pair<int, int> > q;
    q.emplace(s, INF);

    while (!q.empty()) {
        int curent = q.front().first;
        int flow = q.front().second;
        q.pop();

        for (int next: adj[curent])
            if (parinte[next] == -1 && capacitate[curent][next] > 0) {
                parinte[next] = curent;
                int new_flow = min(flow, capacitate[curent][next]); //check for bottleneck
                if (next == t)
                    return new_flow;
                q.emplace(next, new_flow);
            }
    }
    return 0;
}


int EdmondsKarp(int n, int s, int t, vector<vector<int> > &capacitate, const vector<vector<int> > &adj) {
    int flow = 0;
    vector<int> parent(n);

    int new_flow;
    while ((new_flow = bfs(s, t, capacitate, adj, parent)) != 0) {
        flow += new_flow;
        int curent = t;
        while (curent != s) {
            int prev = parent[curent];
            capacitate[prev][curent] -= new_flow;
            capacitate[curent][prev] += new_flow; //nodul rezidual
            curent = prev;
        }
    }

    return flow;
}


int main(int argc, char *argv[]) {
    ifstream fin(argv[1]);
    ofstream fout(argv[2]);


    int V, E;
    fin >> V >> E;

    vector<vector<int> > capacitate(V, vector<int>(V, 0));
    vector<vector<int> > adj(V);

    for (int i = 0; i < E; ++i) {
        int u, v, c;
        fin >> u >> v >> c;
        capacitate[u][v] += c; //muchii paralele
        adj[u].push_back(v);
        adj[v].push_back(u); //muchie inversa pentru graf rezidual
    }

    fin.close();

    int maxFlow = EdmondsKarp(V, 0, V - 1, capacitate, adj);

    fout << maxFlow;
    fout.close();
    return 0;
}
