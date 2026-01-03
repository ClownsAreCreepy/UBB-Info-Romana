#include <iostream>
#include <vector>
#include <queue>
#include <fstream>

using namespace std;

ifstream fin("graf.txt");

int nr_varfuri,varf_start,x,y;
vector<vector<int>> lista(100);

void BFS(vector<vector<int>> &lista, int vf_start) {
    vector<bool> vizitat(nr_varfuri+1,false);
    vector<int> distanta(nr_varfuri+1,-1);
    queue<int> q;

    vizitat[vf_start]=true;         //Incepem BFS de la nodul dat
    distanta[vf_start]=0;
    q.push(vf_start);
    cout<<"BFS cu distanta din nodul "<<vf_start<<":"<<endl;

    while (!q.empty()) {
        int varf = q.front();
        q.pop();
        if (varf != vf_start)
            cout<<"Varful "<<varf<<", cu distanta "<<distanta[varf]<<endl;

        for (int vecin:lista[varf])
            if (!vizitat[vecin]) {
                vizitat[vecin] = true;
                distanta[vecin] = distanta[varf]+1;         //Modificam distanta
                q.push(vecin);
            }

    }
}
int main() {
    fin>>nr_varfuri;
    while (fin>>x>>y) {
        lista[x].push_back(y);
        lista[y].push_back(x);
    }

    cout<<"Introduceti nodul sursa:";
    cin>>varf_start;

    BFS(lista, varf_start);
    return 0;
}