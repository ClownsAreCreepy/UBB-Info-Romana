#include <fstream>
#include <vector>
#include <queue>
#include <algorithm>
#include <climits>
#include <cstring>

using std::vector;
using std::pair;
using std::queue;
using std::ifstream;
using std::ofstream;
using std::fill;
using std::min;

constexpr int MAXN = 110; // nr maxim de noduri
constexpr int INF = 1e9; // pentru flux maxim
constexpr int MAXCAP = 1000; // capacitatea maxima

vector<pair<int, int> > muchii[2 * MAXN]; //graf original (pentru BFS): muchii[sursa] = {destinatie, capacitate}
int capacitate[MAXN][MAXN]; //matrice pentru capacitatea din graful rezidual

int N, C, D;
int cladirea_centrala;
int sursa_super;

vector<int> flux_per_camin; // fluxul maxim din fiecare camin


//Construim graful de fluiditate
void build_flow_network() {
    memset(capacitate, 0, sizeof(capacitate));
    for (int u = 0; u < N; ++u)
        for (auto [v, cap]: muchii[u])
            capacitate[u][v] += cap; // in caz ca e multigraf
}


// Conectam sursa super duper faina la camine, facand fiecare camin o sursa
void add_super_sursa() {
    sursa_super = N;

    for (int camin = 0; camin < C; camin++)
        capacitate[sursa_super][camin] = MAXCAP; // MAXCAP este capacitatea maxima din problema
}


//Edmonds-Karp (BFS)
int bfs_flux(int s, int t, vector<int> &parinte) {
    fill(parinte.begin(), parinte.end(), -1);
    parinte[s] = s;
    queue<pair<int, int> > q;
    q.push({s, INF});

    while (!q.empty()) {
        auto [u, flux] = q.front();
        q.pop();

        for (int v = 0; v <= N; ++v)
            if (parinte[v] == -1 && capacitate[u][v] > 0) {
                parinte[v] = u;
                int flux_nou = min(flux, capacitate[u][v]);
                if (v == t)
                    return flux_nou;
                q.emplace(v, flux_nou);
            }
    }

    return 0;
}

int maxFlow(int s, int t) {
    int flux = 0;
    vector<int> parinte(N + 1);
    int flux_nou;

    while ((flux_nou = bfs_flux(s, t, parinte))) {
        flux += flux_nou;
        int curent = t;
        while (curent != s) {
            int prev = parinte[curent];
            capacitate[prev][curent] -= flux_nou;
            capacitate[curent][prev] += flux_nou;
            curent = prev;
        }
    }

    return flux;
}


//Verificam cat flux a mers de la sursa super la camine
void compute_camin_outputs() {
    flux_per_camin.resize(C);
    for (int camin = 0; camin < C; ++camin) {
        flux_per_camin[camin] = capacitate[camin][sursa_super];
        //cat a ramas din graful rezidual = cat flux din sursa a ajuns la cladirea centrala
    }
}

int main(int argc, char *argv[]) {
    ifstream fin(argv[1]);
    ofstream fout(argv[2]);

    fin >> N >> C >> D;
    cladirea_centrala = N - 1;

    for (int i = 0; i < D; ++i) {
        int x, y, m;
        fin >> x >> y >> m;
        muchii[x].emplace_back(y, m);
        muchii[y].emplace_back(x, m); // graf rezidual
    }

    fin.close();


    build_flow_network();

    add_super_sursa();

    int flux_total_maxim = maxFlow(sursa_super, cladirea_centrala);
    fout << flux_total_maxim << "\n";

    compute_camin_outputs();
    for (int i = 0; i < C; ++i)
        fout << flux_per_camin[i] << (i + 1 < C ? " " : "");

    fout.close();
    return 0;
}
