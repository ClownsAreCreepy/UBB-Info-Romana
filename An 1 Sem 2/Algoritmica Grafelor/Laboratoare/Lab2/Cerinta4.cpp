#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

ifstream fin("graf.txt");

int nr_varfuri,x,y;
vector<vector<int>> lista;

void DFS_VISIT(const vector<vector<int>> &lista, vector<bool> &vizitat,const int nod) {
    vizitat[nod] = true;

    for (int vecin : lista[nod]) {
        if (!vizitat[vecin])
            DFS_VISIT(lista, vizitat, vecin);
    }
}

vector<vector<int>> InchidereTranzitiva(const vector<vector<int>> &lista, int nr_varfuri) {
    vector<vector<int>> matrice_inchidere(nr_varfuri+1, vector<int>(nr_varfuri+1,0));

    for (int i = 1; i <= nr_varfuri; ++i) {
        vector<bool> vizitat(nr_varfuri+1, false);
        DFS_VISIT(lista,vizitat,i);

        for (int j = 1; j <= nr_varfuri; ++j) {
            if (vizitat[j])
                matrice_inchidere[i][j] = 1;
        }
    }
    return matrice_inchidere;
}

int main() {
    fin>>nr_varfuri;
    lista.resize(nr_varfuri+1);

    while (fin>>x>>y)
        lista[x].push_back(y);

    vector<vector<int>> matrice_inchidere = InchidereTranzitiva(lista, nr_varfuri);

    for (int i=1; i <= nr_varfuri; ++i){
        for (int j=1; j <=nr_varfuri; ++j)
            cout<<matrice_inchidere[i][j]<<" ";
        cout<<endl;
    }
}