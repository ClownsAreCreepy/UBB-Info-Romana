#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

ifstream fin("graf.txt");

int nr_varfuri,x,y,varf_inceput;
vector<vector<int>> lista(100);

void DFS_VISIT(vector<vector<int>> &lista, vector<bool> &vizitat, int nod) {
  vizitat[nod] = true;
  cout<<nod<<" ";

  for (int vecin:lista[nod])
    if (!vizitat[vecin])
      DFS_VISIT(lista, vizitat, vecin);
}

void DFS(vector<vector<int>> &lista, int vf_start) {
  vector<bool> vizitat(nr_varfuri, false);

  cout<<"DFS: ";
  DFS_VISIT(lista, vizitat, vf_start);
}

int main() {
  fin>>nr_varfuri;

  while(fin>>x>>y) {
    lista[x].push_back(y);
    lista[y].push_back(x);
  }

  cout<<"Introduceti nodul sursa: ";
  cin>>varf_inceput;

  DFS(lista, varf_inceput);

}