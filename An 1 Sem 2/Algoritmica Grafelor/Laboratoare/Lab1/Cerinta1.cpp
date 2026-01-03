#include <iostream>
#include <fstream>
#include <vector>
using namespace std;
ifstream fin("D:\\Facultate\\Eu\\An 1 Sem 2\\Algoritmica Grafelor\\Laboratoare\\Lab1\\fisier.txt");

int n,x,y,i,j,mat_adi[100][100],mat_adi2[100][100];
int m=1,k,mat_inc[100][100];
vector <vector<int>> lista(100), lista2(100);

int main() {

    //Convertire fisier->matrice de adiacenta(+afisare)

    fin>>n;
    for (i=1; i<=n; ++i)
        for (j=1; j<=n; ++j)
            mat_adi[i][j]=0;

    while (fin>>x>>y)
    {
        mat_adi[x][y] = 1;
        mat_adi[y][x] = 1;
    }
    cout<<"Matricea de adiacenta: "<<endl;
    for (i=1; i<=n; ++i)
    {
        for (j=1; j<=n; ++j)
            cout<<mat_adi[i][j]<<" ";
        cout<<endl;
    }

    //Convertire matrice de adiacenta -> lista de adiacenta(+afisare)

    for (i=1; i<n; ++i)
        for (j=i+1; j<=n; ++j)
        {
            if (mat_adi[i][j]==1)
            {
                lista[i].push_back(j);          //Adaugam vecinii nodului i
                lista[j].push_back(i);          //Adaugam vecinii nodului j, deoarece graful e neorientat
            }
        }
    cout<<endl<<"Lista de adiacenta: "<<endl;
    for (i=1; i<=n; ++i)
    {
        cout<<i<<": ";
        for (int vecin : lista[i] )
            cout<<vecin<<" ";
        cout<<endl;
    }

    //Convertire lista de adiacenta -> matrice de incidenta(+afisare)

    for (i=1; i<=n; ++i)
        for (int vecin:lista[i])
            if (i<vecin)
            {
                mat_inc[i][m] = 1;
                mat_inc[vecin][m]=1;
                m++;
            }
    cout<<endl<<"Matricea de incidenta: "<<endl;
    for (i=1; i<=n; ++i)
    {
        for (j=1; j<=m; ++j)
            cout<<mat_inc[i][j]<<" ";
        cout<<endl;
    }

    //Convertire matrice de incidenta -> lista de adiacenta(+afisare)

    for (i=1;i<n;++i)
        for (j=1;j<=m;++j)
            if (mat_inc[i][j] == 1)
                for (k=i+1; k<=n; ++k)
                    if (mat_inc[k][j]==1)
                    {
                        lista2[i].push_back(k);
                        lista2[k].push_back(i);
                    }
    cout<<endl<<"Lista de adiacenta: "<<endl;
    for (i=1;i<=n;++i)
    {
        cout<<i<<": ";
        for (int vecin : lista2[i])
            cout<<vecin<<" ";
        cout<<endl;
    }

    //Convertire lista de adiacenta -> matrice de adiacenta(+afisare)

    for (i=1;i<=n;++i)
        for (j=1;j<=n;++j)
            mat_adi2[i][j]=0;

    for (i=1;i<=n;++i)
    {
        for (int vecin : lista2[i])
            mat_adi2[i][vecin]=1;
    }
    cout<<endl<<"Matricea de adiacenta: "<<endl;
    for (i=1; i<=n; ++i)
    {
        for (j=1; j<=n; ++j)
            cout<<mat_adi2[i][j]<<" ";
        cout<<endl;
    }
    return 0;
}