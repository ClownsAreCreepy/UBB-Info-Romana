#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void DFS_VISIT(vector<vector<int> > &lista, vector<bool> &vizitat, int nod, vector<int> &grupa) {
    vizitat[nod] = true;
    grupa.push_back(nod);

    for (const int vecin: lista[nod])
        if (!vizitat[vecin])
            DFS_VISIT(lista, vizitat, vecin, grupa);
}

int main() {
    int x, y, nr_copii, m, nr_grupe = 0;
    cin >> nr_copii >> m;

    vector<vector<int> > lista(nr_copii + 1);
    for (int i = 1; i <= m; ++i) {
        cin >> x >> y;
        lista[x].push_back(y);
        lista[y].push_back(x);
    }

    vector<bool> vizitat(nr_copii+1, false);
    vector<vector<int>> grupuri;
    for (int i = 1; i <=nr_copii; ++i){
        if (!vizitat[i]) {
            vector<int> grupa;
            DFS_VISIT(lista, vizitat,i, grupa);
            sort(grupa.begin(), grupa.end());
            grupuri.push_back(grupa);
        }
    }

    for (size_t i = 0; i < grupuri.size(); ++i) {
        cout<<"Grupa "<<i+1<<": ";
        for (int j : grupuri[i])
            cout<<j<<" ";
        cout<<endl;
    }
}

/*
10 7
1 2
2 3
3 4
4 5
6 10
7 8
7 9
 */
