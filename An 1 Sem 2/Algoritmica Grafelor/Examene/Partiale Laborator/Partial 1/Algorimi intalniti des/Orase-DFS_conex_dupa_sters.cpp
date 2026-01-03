#include <iostream>
#include <fstream>
#include <vector>

using namespace std;
ifstream fin("graf.txt");

int surs_elim,dest_elim,orase,legaturi,x,y;
vector<vector<int>> judet;
vector<bool> vizitat;

void DFS(vector<vector<int>> &judet, vector<bool> &vizitat, int oras_sursa) {
    vizitat[oras_sursa] = true;

    for (int vecin : judet[oras_sursa])
        if (vizitat[vecin] == false)
            DFS(judet, vizitat, vecin);
}

void lets_see(vector<bool> &vizitat, int nr_orase) {
    for (int i = 1; i <=nr_orase; ++i)
        if (vizitat[i] == false) {
            cout<<"NU";
            return;
        }
    cout<<"DA";
}

int main() {
    cin >> surs_elim >> dest_elim;
    fin>>orase>>legaturi;

    judet.resize(orase+1);
    vizitat.resize(orase+1, false);

    while (fin>>x>>y)
        if (! ((x==surs_elim && y==dest_elim) || (x==dest_elim && y==surs_elim)) ) {
            judet[x].push_back(y);
            judet[y].emplace_back(x);
        }

    //Am populat lista cu toate drumurile in afara de cele date de la tastatura
    //Verificam daca graful inca mai este conex

    DFS(judet, vizitat, 1);
    lets_see(vizitat, orase);
}

/*
7 8
1 2
1 3
2 3
2 4
2 5
6 4
6 5
7 2
 */