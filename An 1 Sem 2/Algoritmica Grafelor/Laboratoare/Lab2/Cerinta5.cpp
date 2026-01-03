#include <iostream>
#include <vector>
#include <queue>
#include <fstream>

using namespace std;

ifstream fin("graf.txt");

int nr_varfuri, x, y, sursa;
vector<vector<int>> lista;

//BFS pentru a gasi cele mai scurte drumuri de la un nod sursa
vector<int> Moore_BFS(const vector<vector<int>> &lista, int sursa, vector<int> &parinte) {
    vector<int> dist(nr_varfuri+1, -1); // -1 inseamna ca nodul nu e accesibil
    queue<int> q;

    dist[sursa] = 0;
    q.push(sursa);

    while (!q.empty()) {
        int nod = q.front();
        q.pop();

        for (int vecin : lista [nod]) {
            if (dist[vecin] == -1) { //Daca nodul nu a fost vizitat
                dist[vecin] = dist[nod] + 1;
                parinte[vecin] = nod; // Salveaza de unde am venit
                q.push(vecin);
            }
        }
    }
    return dist;
}

// Functie pentru reconstruirea si afisarea celui mai scurt lant de la sursa la un nod destinatie
void AfiseazaLantul(int destinatie, const vector<int> &parinte) {
    vector<int> drum;
    int nod = destinatie;

    while (nod != -1) {
        drum.push_back(nod);
        nod = parinte[nod];
    }

    for (int i = drum.size() -1 ; i >= 0; --i) {
        cout << drum[i];
        if (i != 0 ) cout << " -> ";
    }
    cout<<endl;

}

int main(){
    fin>>nr_varfuri;
    lista.resize(nr_varfuri+1);

    while (fin>>x>>y)
        lista[x].push_back(y);

    cout<<"Introduceti varful sursa: ";
    cin>>sursa;

    //Vectorul de parinti pentru reconstructia drumului
    vector<int> parinte(nr_varfuri+1, -1);
    vector<int> distanta = Moore_BFS(lista, sursa, parinte);

    cout<<"Drumul cel mai scurt de la nodul " << sursa << " la celelalte noduri:"<<endl;
    for (int i = 1; i <= nr_varfuri; ++i) {
        if (distanta[i] == -1)
            cout<<"Nu exista drum de la "<<sursa<<" la "<<i<<endl;
        else {
            cout<<"Distanta pana la "<<i<<" :"<<distanta[i]<<" | Drum: ";
            AfiseazaLantul(i, parinte);
        }
    }
}
