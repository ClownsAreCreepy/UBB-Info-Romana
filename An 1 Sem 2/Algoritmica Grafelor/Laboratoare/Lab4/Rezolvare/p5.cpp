#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;


//Formatul unei muchii pentru ca ele sa pot fi comparabile intre ele
struct Muchie {
    int u, v, w;

    bool operator<(const Muchie &other) const {
        return w < other.w;
    }
};


//Disjoint Set Union
struct DSU {
    vector<int> parent, rank;

    explicit DSU(int n) {
        parent.resize(n);
        rank.resize(n, 0);
        for (int i = 0; i < n; ++i)
            parent[i] = i;
    }

    //Gasim 'radacina' nodului x
    int find(int x) {
        if (x != parent[x])
            parent[x] = find(parent[x]);
        return parent[x];
    }

    bool unire(int x, int y) {
        int rx = find(x);
        int ry = find(y);

        if (rx == ry)
            return false;

        if (rank[rx] < rank[ry])
            swap(rx, ry);

        parent[ry] = rx;

        if (rank[rx] == rank[ry])
            rank[rx]++;

        return true;
    }
};


int main(int argc, char *argv[]) {
    ifstream fin(argv[1]);
    ofstream fout(argv[2]);


    //Luam lista de adiacenta din fisier si o memoram ca o lista de muchii
    int V, E;
    fin >> V >> E;

    vector<Muchie> muchii(E);
    for (int i = 0; i < E; ++i)
        fin >> muchii[i].u >> muchii[i].v >> muchii[i].w;

    fin.close();


    //Sortam dupa pondere
    sort(muchii.begin(), muchii.end());


    //Aplicam algoritmul lui Kruskal
    DSU dsu(V);
    int cost = 0;
    vector<pair<int, int> > ama;
    for (auto &[sursa, destinatie, pondere]: muchii)
        if (dsu.unire(sursa, destinatie)) {
            cost += pondere;
            ama.emplace_back(sursa, destinatie);
        }


    //Tiparim in fisierul de iesire costul total, nr de muchii din arbore si muchiile respective
    fout << cost << '\n';
    fout << ama.size() << '\n';

    for (auto &[u, v]: ama)
        fout << u << ' ' << v << '\n';

    fout.close();
    return 0;
}
