#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Formatul unei muchii pentru ca ele sa poata fi comarabile intre ele
struct Muchie {
    int u, v, w;

    bool operator<(const Muchie &other) const { return w < other.w; }
};


// Disjoint Set Union
struct DSU {
    vector<int> parent, rank;

    explicit DSU(int n) {
        parent.resize(n);
        rank.resize(n, 0);
        for (int i = 0; i < n; ++i)
            parent[i] = i;
    }

    // Gasim 'radacina' nodului x
    int find(int x) {
        if (x != parent[x])
            parent[x] = find(parent[x]);
        return parent[x];
    }

    bool unire(int x, int y) {
        int root_x = find(x);
        int root_y = find(y);

        if (root_x == root_y)
            return false; // fac parte din acelasi arbore. Daca le unim creem un ciclu

        if (rank[root_x] < rank[root_y])
            swap(root_x, root_y);

        parent[root_y] = root_x;

        if (rank[root_x] == rank[root_y])
            rank[root_x]++;

        return true;
    }
};


int main() {
    int V, E;
    cin >> V >> E;

    vector<Muchie> muchii(E);
    for (int i = 0; i < E; ++i)
        cin >> muchii[i].u >> muchii[i].v >> muchii[i].w;

    sort(muchii.begin(), muchii.end());

    DSU dsu(V);
    int cost = 0;
    vector<pair<int, int> > ama;
    for (auto &[sursa, destinatie, pondere]: muchii)
        if (dsu.unire(sursa, destinatie)) {
            cost += pondere;
            ama.emplace_back(sursa, destinatie);
        }

    cout << cost << '\n';
    cout << ama.size() << '\n';

    for (auto &[u, v]: ama)
        cout << u << " " << v << '\n';

    return 0;
}

/*
9 14
1 2 10
1 3 -11
2 4 11
2 5 11
5 6 13
3 4 10
4 6 12
4 7 5
3 7 4
3 8 5
8 7 5
8 9 4
9 7 3
6 7 11
*/
