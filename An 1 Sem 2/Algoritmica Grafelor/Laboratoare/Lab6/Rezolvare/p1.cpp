#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

int N, M;
vector<vector<int>> graf;
vector<int> culoare;
bool rezolvat = false;


bool isSafe(const int nod, const int c) {
    for (const int vecin : graf[nod])
        if (culoare[vecin] == c)
            return false;

    return true;
}


bool backtrack(const int nodIndex, const int maxCulori, const vector<int> &ordine) {
    if (nodIndex == N) {
        rezolvat = true;
        return true;
    }

    int nod = ordine[nodIndex];
    for (int c = 0; c < maxCulori; ++c)
        if (isSafe(nod, c)) {
            culoare[nod] = c;
            if (backtrack(nodIndex + 1, maxCulori, ordine))
                return true;
            culoare[nod] = -1;
        }

    return false;
}


int main(int argc, char *argv[]) {
    ifstream fin(argv[1]);
    ofstream fout(argv[2]);

    fin >> N >> M;
    graf.resize(N);
    culoare.assign(N, -1);

    for (int i = 0; i < M; ++i) {
        int u, v;
        fin >> u >> v;
        graf[u].push_back(v);
        graf[v].push_back(u);       // neorientat
    }

    fin.close();


    // ordonam nodurile descrescator dupa grad (e un pic mai rapid)
    vector<int> ordine(N);
    for (int i = 0; i < N; ++i)
        ordine[i] = i;
    sort(ordine.begin(), ordine.end(), [](int a, int b) {
        return graf[a].size() > graf[b].size();
    });


    int minCulori = 1;
    while (!rezolvat) {
        culoare.assign(N, -1);          // Resetam toate culorile la -1 (fara culoare)
        backtrack(0, minCulori, ordine);        // Incercam sa coloram graful cu 'minCulori' culori
        if (!rezolvat)
            minCulori ++;                   // daca nu ne iese, incercam cu mai multe dupa
    }


    fout << minCulori << endl;
    for (int i = 0; i < N; ++i)
        fout << culoare[i] << (i+1 < N ? " ": "");

    fout.close();
    return 0;
}
