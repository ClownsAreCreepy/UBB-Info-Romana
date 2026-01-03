#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <algorithm>
#include <limits>

using namespace std;
ifstream fin(R"(D:\Facultate\Eu\An 1 Sem 2\Algoritmica Grafelor\Teste laborator\Lab 1\graf.txt)");

constexpr int INF = numeric_limits<int>::max();

int main() {
    int V, E, S, D;
    fin >> V >> E >> S >> D;

    //citim graful din fisier si gasim lista de adiacenta
    vector<vector<pair<int, int> > > adi(V); //adi(i) = lista de {j, k}
    for (int l = 0; l < E; ++l) {
        int i, j, k;
        fin >> i >> j >> k;
        adi[i].emplace_back(j, k);
    }

    vector dist(V, INF);
    vector parent(V, -1);
    priority_queue<pair<int, int>, vector<pair<int, int> >, greater<> > pq; //memoram ponderea pe prima pozitie si nodul pe a doua

    //initializam varful sursa
    dist[S] = 0;
    pq.emplace(0, S);

    while (!pq.empty()) {
        auto [pondere, nod] = pq.top();
        pq.pop();

        if (nod == D) break; //daca nodul pe care il avem e destinatia, iesim din dijkstra, deoarece e nodul cu drumul cel mai mic dintre cele ramase

        if (pondere > dist[nod]) continue; //Trecem peste daca am gasit deja o distanta mai buna

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
        cout << "Nu exista drum de la orasul " << S << " la orasul " << D << "!";
    else {
        cout << "Distanta minima de la orasul " << S << " la orasul " << D << " este: " << dist[D] << endl;
        cout << "Drumul optim de la orasul " << S << " la orasul " << D << " este: ";
        for (size_t i = 0; i < path.size(); ++i) {
            cout << "orasul " << path[i];
            if (i < path.size() - 1)
                cout << " -> ";
        }
    }
}
