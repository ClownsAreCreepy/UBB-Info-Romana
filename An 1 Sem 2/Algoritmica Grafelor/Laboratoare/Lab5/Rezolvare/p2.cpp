#include <fstream>
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
int height[MAXN], exces[MAXN];


void addMuchie(int u, int v, int c) {
    adj[u].push_back({v, static_cast<int>(adj[v].size()), c});
    adj[v].push_back({u, static_cast<int>(adj[u].size()) - 1, 0}); // graf rezidual
}


void pompare(int u, Muchie &m) {
    int v = m.to;
    int flow = min(exces[u], m.cap);
    if (height[u] == height[v] + 1 && flow > 0) {
        m.cap -= flow;
        adj[v][m.rev].cap += flow;
        exces[u] -= flow;
        exces[v] += flow;
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
    while (exces[u] > 0) {
        bool pushed = false;
        for (Muchie &m: adj[u])
            if (m.cap > 0 && height[u] == height[m.to] + 1) {
                // daca putem sa adaugam flux, adaugam
                pompare(u, m);
                pushed = true;
                if (exces[u] == 0) break;
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
        exces[s] -= flow;
        exces[m.to] += flow;
    }

    // adaugam vecinii in coada
    queue<int> q;
    for (int i = 0; i < V; ++i)
        if (i != s && i != t && exces[i] > 0)
            q.push(i);


    while (!q.empty()) {
        int u = q.front();
        q.pop();

        int oldH = height[u];
        discharge(u); //incercam sa adaugam flux in vecini
        if (height[u] > oldH)
            q.push(u);
    }

    return exces[t];
}


int main(int argc, char *argv[]) {
    ifstream fin(argv[1]);
    ofstream fout(argv[2]);

    int E;
    fin >> V >> E;

    for (int i = 0; i < E; ++i) {
        int u, v, c;
        fin >> u >> v >> c;
        addMuchie(u, v, c);
    }
    fin.close();

    int rezultat = maxFlow(0, V - 1);
    fout << rezultat;
    fout.close();

    return 0;
}
