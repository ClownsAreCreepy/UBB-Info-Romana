#include <fstream>
#include <vector>
#include <queue>
#include <limits>

using namespace std;

//Constante
const int INF = numeric_limits<int>::max();

//Citeste graful din fisier si returneaza lista de adiacenta
vector<vector<pair<int, int>>> citesteGraf(ifstream &fin, int &V, int &E, int &S) {
    fin>>V>>E>>S;

    vector<vector<pair<int, int>>> adi(V); //adi(u) = lista de {v, pondere}
    for (int i=0; i < E; ++i) {
        int u,v,w;
        fin>>u>>v>>w;
        adi[u].push_back({v,w});
    }
    return adi;
}

//Dijkstra din sursa S
vector<int> Dijkstra(const vector<vector<pair<int, int>>> &adi, int V, int S) {
    vector<int> dist(V, INF);
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;

    //Initializam varful sursa cu 0
    dist[S] = 0;
    pq.push({0,S});

    while (!pq.empty()) {
        auto [pondere, nod] = pq.top();
        pq.pop();

        if (pondere > dist[nod]) continue;      //Trecem peste daca am gasit o distanta mai buna

        for (const auto& [vecin, cost] : adi[nod])
            if (dist[vecin] > dist[nod] + cost) {
                dist[vecin] = dist[nod] + cost;
                pq.push({dist[vecin], vecin});
            }
    }

    return dist;
}

//Tipareste distantele in alt fisier
void scrieGraf(ofstream &fout, const vector<int> &dist) {
    for (int i = 0; i < dist.size(); ++i) {
        if (dist[i] == INF) fout<<"INF";
        else fout<<dist[i];
        if (i+1 < dist.size()) fout<<" ";
    }
}

int main(int argc, char* argv[]) {
    ifstream fin(argv[1]);
    ofstream fout(argv[2]);

    int V, E, S;
    vector<vector<pair<int, int>>> adi = citesteGraf(fin, V, E, S);
    vector<int> dist = Dijkstra(adi, V, S);
    scrieGraf(fout, dist);

    fin.close();
    fout.close();
    return 0;
}
