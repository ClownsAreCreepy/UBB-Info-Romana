#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <limits>

using namespace std;

constexpr int MAXN = 1000;
constexpr int INF = numeric_limits<int>::max();


struct Muchie {
    int to, rev, cap;
};

int V;
vector<Muchie> adj[MAXN];
int height[MAXN], excess[MAXN];


void addMuchie(int u, int v, int c) {
    adj[u].push_back({v, static_cast<int>(adj[v].size()), c});
    adj[v].push_back({u, static_cast<int>(adj[u].size()) - 1, 0});
}


void pompare(int u, Muchie &m) {
    int v = m.to;
    int flow = min(excess[u], m.cap);
    if (height[u] == height[v] + 1 && flow > 0) {
        m.cap -= flow;
        adj[v][m.rev].cap += flow;
        excess[u] -= flow;
        excess[v] += flow;
    }
}


void inaltare(int u) {
    int minH = INF;

    for (Muchie &m: adj[u])
        if (m.cap > 0)
            minH = min(minH, height[m.to]); // inaltam cu 1 peste vecinul cu cea mai mica inaltime

    if (minH < INF)
        height[u] = minH + 1;
}


void discharge(int u) {
    while (excess[u] > 0) {
        bool pushed = false;
        for (Muchie &m: adj[u])
            if (m.cap > 0 && height[u] == height[m.to] + 1) {
                // daca putem sa adaugam flux, adaugam
                pompare(u, m);
                pushed = true;
                if (excess[u] == 0)
                    break;
            }
        if (!pushed) inaltare(u); // daca nu putem adauga, inaltam u
    }
}


int maxFlow(int s, int t) {
    height[s] = V;

    // impunem flux maxim in vecinii sursei
    for (Muchie &m: adj[s]) {
        int flow = m.cap;
        m.cap = 0;
        adj[m.to][m.rev].cap += flow;
        excess[s] -= flow;
        excess[m.to] += flow;
    }

    // folosim pomparea topologica ( highest-label)
    priority_queue<pair<int, int> > pq; // <inaltime, nod>
    vector<bool> inQueue(V + 1, false);

    for (int i = 1; i <= V; ++i)
        if (i != s && i != t && excess[i] > 0) {
            pq.emplace(height[i], i);
            inQueue[i] = true;
        }

    while (!pq.empty()) {
        int u = pq.top().second;
        pq.pop();
        inQueue[u] = false;

        int oldH = height[u];
        discharge(u); // incercam sa adaugam flux in vecini
        if (height[u] > oldH && !inQueue[u] && excess[u] > 0) {
            pq.emplace(height[u], u);
            inQueue[u] = true;
        }
    }

    return excess[t];
}


int main() {
    int E;
    cin >> V >> E;

    for (int i = 0; i < E; ++i) {
        int u, v, c;
        cin >> u >> v >> c;
        addMuchie(u, v, c);
    }

    int rezultat = maxFlow(1, V);
    cout << rezultat;

    return 0;
}

/*
4 5
1 2 3
1 3 5
2 4 6
3 4 4
3 2 3
 */
