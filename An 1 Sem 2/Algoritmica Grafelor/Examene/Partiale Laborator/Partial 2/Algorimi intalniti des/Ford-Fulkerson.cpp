#include <iostream>
#include <vector>
#include <limits>

using namespace std;

constexpr int INF = numeric_limits<int>::max();


int dfs(int current, int t,int flow, vector<vector<int>> &capacitate, const vector<vector<int>> &adj, vector<int> &parinte) {
    if (current == t)
        return flow;

    for (int next: adj[current])
        if (parinte[next] == -1 && capacitate[current][next] > 0) {
            parinte[next] = current;
            int new_flow = dfs(next, t, min(flow, capacitate[current][next]), capacitate, adj, parinte);
            if (new_flow > 0)
                return new_flow;
        }

    return 0;
}


int FordFulkerson(int n, int s, int t, vector<vector<int>> &capacitate, const vector<vector<int>> &adj) {
    int flow = 0;
    vector<int> parent(n);

    while (true) {
        fill(parent.begin(), parent.end(), -1);
        parent[s] = -2;
        int new_flow = dfs(s, t, INF, capacitate, adj, parent);
        if (new_flow == 0)
            break;

        flow += new_flow;
        int current = t;
        while (current != s) {
            int prev = parent[current];
            capacitate[prev][current] -= new_flow;
            capacitate[current][prev] += new_flow;      // nodul rezidual
            current = prev;
        }
    }

    return flow;
}

int main() {
    int V, E;
    cin >> V >>E;

    vector<vector<int>> capacitate(V, vector<int>(V, 0));
    vector<vector<int>> adj(V);

    for (int i = 0; i < E; ++i) {
        int u,v,c;
        cin >> u >> v >>c;
        capacitate[u][v] += c;      // += pentru muchii paralele
        adj[u].emplace_back(v);
        adj[v].emplace_back(u);     // muchie inversa pentru graf rezidual
    }

    int maxFlow = FordFulkerson(V, 0, V - 1, capacitate, adj);
    cout << maxFlow;

    return 0;
}

/*
5 6
0 1 5
0 3 5
0 2 10
1 4 11
2 3 2
3 4 8
 */