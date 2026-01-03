#include <iostream>
#include <vector>
#include <algorithm>
#include <set>

using namespace std;

int n,m;
vector<vector<int>> lista;
vector<bool> vizitat;
bool has_cicle = false;


void dfs(const int nod, const int parinte) {
    vizitat[nod] = true;

    for (int vecin : lista[nod]){
        if (vizitat[vecin] == false)
            dfs(vecin, nod);
        else if (vecin != parinte)
            has_cicle = true;
    }
}


int main() {
    cin>>n>>m;
    lista.resize(n+1);
    vizitat.resize(n+1, false);

    for (int i = 0; i < m; ++i) {
        int x,y;
        cin>>x>>y;
        lista[x].emplace_back(y);
        lista[y].emplace_back(x);
    }

    for (int i = 1; i <= n ; ++i)
        if (!vizitat[i] && !has_cicle)
            dfs(i, -1);

    if (!has_cicle)
        cout<<"DA"; // nu are cicluri
    else
        cout<<"NU"; // are muchii nevizitate => cicluri
}

/*
7 7
1 2
2 3
3 4
4 1
1 5
5 6
5 7
 */