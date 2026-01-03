#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <tuple>
#include <limits>
#include <algorithm>

using namespace std;

const int INF = numeric_limits<int>::max();

typedef tuple<int, int, int> Muchie; //{sursa, destinatie, pondere}

//Bellman-Ford de la nodul fals
bool bellmanFord(int V, const vector<Muchie>& muchii, vector<int>& h) {
    h.assign(V+1, INF);
    h[V] = 0;

    for (int i = 0; i < V; ++i)
        for (const auto& [s,d,p] : muchii)
            if (h[s] != INF && h[s] + p < h[d])
                h[d] = h[s] + p;

    //Daca dupa ce am gasit toate imbunatatirile INCA mai gasim, atunci avem de a face cu un ciclu infinit
    for (const auto& [s,d,p] : muchii)
        if (h[s] != INF && h[s] + p < h[d])
            return false;

    return true;
}

//Dijkstra
vector<int> dijkstra(int sursa, const vector<vector<pair<int, int>>>& adj) {
    int V = adj.size();
    vector<int> distanta (V, INF);

    priority_queue<pair<int, int>, vector<pair<int,int>>, greater<>> pq;

    distanta[sursa] = 0;
    pq.push({0,sursa});

    while (!pq.empty()) {
        auto [pondere,nod] = pq.top();
        pq.pop();
        if (pondere > distanta[nod])
            continue;

        for (const auto& [vecin, cost] : adj[nod])
            if (distanta[vecin] > distanta[nod] + cost) {
                distanta[vecin] = distanta[nod] + cost;
                pq.push({distanta[vecin], vecin});
            }
    }
    return distanta;
}

int main(int argc, char* argv[]) {
    if (argc < 3) return 1;

    ifstream fin(argv[1]);
    ofstream fout(argv[2]);

    int V, E;
    fin>>V>>E;

    vector<Muchie> muchii;

    for (int i = 0; i < E; ++i) {
        int s,d,p;
        fin>>s>>d>>p;
        muchii.push_back({s,d,p});
    }

    //Adaugam un nod fals
    for (int i = 0; i < V; ++i)
        muchii.push_back({V,i,0});

    vector<int> h;
    if (!bellmanFord(V, muchii, h)) {
        fout<<-1<<"\n";
        return 0;
    }

    //Restoram muchiile originale pentru reponderare
    muchii.resize(E);

    //Reponderam muchiile
    vector<Muchie> muchii_reponderate;
    vector<vector<pair<int,int>>> adj(V);
    for (const auto& [s,d,p] : muchii) {
        int PondereNoua = p + h[s] -h[d];
        muchii_reponderate.push_back({s,d,PondereNoua});
        adj[s].push_back({d, PondereNoua});
    }

    //Sortam muchiile dupa s, dupaia dupa d
    sort(muchii_reponderate.begin(), muchii_reponderate.end());

    //Tiparim muchiile reponderate
    for ( const auto& [s,d,p] : muchii_reponderate)
        fout<< s << " " << d << " " << p << endl;

    fout<<endl;
    //Matricea de distanta
    for (int s = 0; s < V; ++ s) {
        vector<int> distanta = dijkstra(s, adj);
        for (int d = 0; d < V; ++d) {
            if (distanta[d] == INF)
                fout<<"INF";
            else
                fout<<distanta[d] + h[d] - h[s];

            if (d-1 < V) fout<<" ";
        }
        fout<<endl;
    }
    return 0;
}