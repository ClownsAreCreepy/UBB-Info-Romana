#include <fstream>
#include <vector>
#include <queue>

using namespace std;

int main(int argc, char *argv[]) {
    //O( (V+E) * log V)
    //ne uitam peste fiecare muchie si nod, push si pop de la priority queue are O(log n)

    ifstream fin(argv[1]);
    ofstream fout(argv[2]);

    int V, E;
    fin >> V >> E;

    vector<vector<pair<int, int> > > graf(V);
    for (int i = 0; i < E; ++i) {
        int u, v, w;
        fin >> u >> v >> w;
        graf[u].emplace_back(v, w);
        graf[v].emplace_back(u, w);
    }

    fin.close();


    vector<pair<int, int> > ama; // (sursa, destinatie)
    vector<bool> inAma(V, false); // marcam nodurile care sunt in ama
    vector<int> parinte(V, -1);
    int cost = 0;

    priority_queue<pair<int, int>, vector<pair<int, int> >, greater<> > pq;
    // pq pentru a lua muchiile cu ponderea cea mai mica
    pq.emplace(0, 0); // (cost, nod)

    while (!pq.empty()) {
        auto [w, u] = pq.top();
        pq.pop();

        if (inAma[u])
            continue; // daca e deja in ama, sarim peste el

        inAma[u] = true;
        cost += w; // modifcam costul de acoperire

        if (parinte[u] != -1)
            ama.emplace_back(parinte[u], u); // daca nu e in ama, adaugam muchia dintre parinte si el

        for (auto &[v, pondere]: graf[u])
            if (!inAma[v]) {
                pq.emplace(pondere, v); // cautam vecini care nu sunt in arbore
                parinte[v] = u;
            }
    }

    fout << cost << '\n' << ama.size() << '\n';

    for (auto &[u, v]: ama)
        fout << u << ' ' << v << '\n';

    fout.close();
    return 0;
}
