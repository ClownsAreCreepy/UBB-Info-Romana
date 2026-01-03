#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <limits>

using namespace std;

constexpr int INF = numeric_limits<int>::max();

int main() {
    int V, E, S, D;
    cin >> V >> E >> S >> D;

    //citim graful din fisier si gasim lista de adiacenta
    vector<vector<pair<int, int> > > adi(V); //adi(u) = lista de {v, pondere}
    for (int i = 0; i < E; ++i) {
        int u, v, p;
        cin >> u >> v >> p;
        adi[u].emplace_back(v, p);
    }

    vector<int> dist(V, INF);
    vector<int> parent(V, -1);
    priority_queue<pair<int, int>, vector<pair<int, int> >, greater<> > pq; //memoram ponderea pe prima pozitie si nodul pe a doua

    //initializam varful sursa
    dist[S] = 0;
    pq.emplace(0, S);

    while (!pq.empty()) {
        auto [pondere, nod] = pq.top();
        pq.pop();

        if (nod == D) break; //daca nodul pe care il avem e destinatia, iesim din dijkstra, deoarece e nodul cu drumul cel mai mic dintre cele ramase

        if (pondere > dist[nod]) continue; //Trecem peste daca am gasit o distanta mai buna

        for (const auto &[vecin, cost]: adi[nod])
            if (dist[vecin] > dist[nod] + cost) {
                dist[vecin] = dist[nod] + cost;
                pq.emplace(dist[vecin], vecin);
                parent[vecin] = nod;
            }
    }

    vector<int> path; //salvam calea catre destinatie (e inversa, deci va trebui sa o inversam dupa aceea)
    for (int aux_D = D; aux_D != -1; aux_D = parent[aux_D])
        path.push_back(aux_D);
    ranges::reverse(path);

    if (dist[D] == INF)
        cout << "Nu exista drum de la casa " << S << " la casa " << D << "!";
    else {
        cout << "Distanta minima de la casa " << S << " la casa " << D << " este: " << dist[D] << endl;
        cout << "Drumul optim de la casa " << S << " la casa " << D << " este: ";
        for (size_t i = 0; i < path.size(); ++i) {
            cout << "casa " << path[i];
            if (i < path.size() - 1)
                cout << " -> ";
        }
    }
}

/*
5 7 1 3
0 2 4
0 3 1
1 0 1
1 2 4
2 0 1
2 3 1
3 4 1
Pentru verificare daca exista*/

/*
5 9 0 2
0 1 10
0 3 5
1 3 2
1 2 1
3 1 3
3 2 9
3 4 2
2 4 4
4 2 6
Pentru verificare distanta*/
