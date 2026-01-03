#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

constexpr double INF = 1e18;

int n, m;
vector<pair<pair<int, int>, double> > muchii;
vector<double> distanta;

// Incercam sa relaxam muchia (u,v) cu costul c
bool relax(int u, int v, double c) {
    if (distanta[v] > distanta[u] + c) {
        distanta[v] = distanta[u] + c;
        return true;
    }

    return false;
}


bool bellman_ford() {
    int super_sursa = n;

    // Introducem nodul sursa, conectand-ul cu fiecare nod, cu cost 0
    for (int i = 0; i < n; ++i)
        muchii.emplace_back(make_pair(super_sursa, i), 0);

    distanta.assign(n + 1, INF);
    distanta[super_sursa] = 0;

    // Relaxam muchiile (de n ori = nr de noduri, fara sursa)
    for (int i = 0; i < n; ++i)
        for (const auto &[muchie, cost]: muchii)
            relax(muchie.first, muchie.second, cost);

    // Verificam daca mai exista o muchie care poate fi relaxata
    // Daca da -> ciclu negativ -> nu avem solutie
    for (const auto &[muchie, cost]: muchii)
        if (relax(muchie.first, muchie.second, cost))
            return false;

    return true;
}

int main(int argc, char *argv[]) {
    ifstream fin(argv[1]);
    fin >> m >> n;

    // Citim matricea si creem lista de adiacenta
    for (int i = 0; i < m; ++i) {
        int from = -1, to = -1, val;
        for (int j = 0; j < n; ++j) {
            fin >> val;
            if (val == -1) from = j;
            if (val == 1) to = j;
        }
        muchii.emplace_back(make_pair(from, to), 0);
    }

    // Citim vectorul b si punem costul fiecarei muchii
    for (int i = 0; i < m; ++i) {
        double x;
        fin >> x;
        muchii[i].second = x;
    }

    fin.close();


    if (!bellman_ford())
        cout << "Nu exista solutie!\n";
    else
        for (int i = 0; i < n; ++i)
            cout << distanta[i] << " ";

    return 0;
}
