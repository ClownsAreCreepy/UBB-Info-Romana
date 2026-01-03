#include <iostream>
#include <fstream>
using namespace std;

ifstream fin("D:\\Facultate\\Eu\\An 1 Sem 2\\Algoritmica Grafelor\\Laboratoare\\Lab1\\fisier.txt");

int x,y,n,i,j,k,a[100][100];

int main() {
  fin>>n;
  for (i=1;i<=n;++i)
    for(j=1;j<=n;++j)
      a[100][100] = 0;

  while(fin>>x>>y)
  {
    a[x][y] = 1;
    a[y][x] = 1;
  }

  //Subpunctul a) sa se determine nodurile izolate dintr-un graf

  int verificare=0, verificare_total=0;

  cout<<"Nodurile izolate: ";

  for (i=1;i<=n;++i)
  {
    for(j=1;j<=n;++j)
      if (a[i][j]==1)
        verificare = 1;
    if (verificare==0)
    {
      verificare_total=1;
      cout<<i<<" ";
    }
    verificare=0;
  }

  if(verificare_total==0)
    cout<<"Nu exista";
  cout<<endl<<endl;

  //Subpunctul b) sa se determine daca graful este regular

  int suma=0, suma2;
  bool regular = true;

  for (i=1;i<=n;++i)
  {
    suma2 = 0;
    for (j=1;j<=n;++j)
      if (i==1)
        suma += a[i][j];
      else
        suma2 += a[i][j];
    if (i!=1 and suma != suma2) {
      regular = false;
      break;
    }
  }

  if (regular==false)
    cout<<"Graful nu este regular"<<endl<<endl;
  else
    cout<<"Graful este regular"<<endl<<endl;

  //Subpunctul c) pentru un graf reprezentat cu matricea de adiacenta sa se determine matricea distantelor

  int mat_dist[100][100];
  const int INF = 1e9;

  cout<<"Matricea distantelor: "<<endl;

  for (i=1;i<=n;++i) {
    for (j=1;j<=n;++j)
      if (a[i][j]==1)
        mat_dist[i][j] = 1;
      else
        mat_dist[i][j] = INF;
    mat_dist[i][i] = 0;
  }

  for (k=1;k<=n;++k)
    for (i=1;i<=n;++i)
      for (j=1;j<=n;++j)
        if (mat_dist[i][k] != INF && mat_dist[k][j] != INF)
          mat_dist[i][j] = min(mat_dist[i][j], mat_dist[i][k] + mat_dist[k][j]);

  for (i=1;i<=n;++i) {
    for (j=1;j<=n;++j)
      cout<<mat_dist[i][j]<<" ";
    cout<<endl;
  }
  cout<<endl;

  //Subpunctul d) pentru un graf reprezentat cu o matrice de adiacenta sa se determine daca este conex.
  //Ne folosim de matricea de la subpunctul c)

  bool conex = true;

  for (i=1;i<=n;++i)
    for (j=1;j<=n;++j)
      if (mat_dist[i][j] == INF)
      {
        conex = false;
        break;
      }

  if (conex == true)
    cout<<"Graful este conex";
  else
    cout<<"Graful nu este conex";

}