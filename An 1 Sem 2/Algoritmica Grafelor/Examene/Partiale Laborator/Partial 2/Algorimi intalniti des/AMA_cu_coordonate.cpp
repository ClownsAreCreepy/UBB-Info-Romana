#include <iostream>
#include <vector>
#include <numeric>
#include <cmath>
#include <algorithm>

using std::vector;
using std::pair;
using std::tuple;
using std::cin;
using std::cout;
using std::sort;

struct DSU {
    vector<int> parinte;

    DSU(int n): parinte(n) {
        iota(parinte.begin(), parinte.end(), 0);
    }

    int find(int x) {
        if (parinte[x] != x)
            parinte[x] = find(parinte[x]);
        return parinte[x];
    }

    void unite(int x, int y) {
        parinte[find(x)] = find(y);
    }
};


double dist(pair<int, int> a, pair<int, int> b) {
    int dx = a.first - b.first;
    int dy = a.second - b.second;
    return sqrt(dx * dx + dy * dy);
}

int main() {
    int N;
    cin >> N;
    vector<pair<int, int>> orase(N);
    for (int i = 0; i < N; ++i)
        cin >> orase[i].first >> orase[i].second;

    vector<tuple<double, int, int>> muchii;
    for (int i = 0; i < N; ++i)
        for (int j = i + 1; j < N; ++j)
            muchii.emplace_back(dist(orase[i], orase[j]), i, j);

    sort(muchii.begin(), muchii.end());

    DSU dsu(N);
    double total = 0;
    for (auto [cost, u, v]: muchii)
        if (dsu.find(u) != dsu.find(v)) {
            dsu.unite(u, v);
            total += cost;
        }

    cout << total;
}
/*
9
0 0
1 0
2 0
0 1
1 1
2 1
0 2
1 2
2 2
 */