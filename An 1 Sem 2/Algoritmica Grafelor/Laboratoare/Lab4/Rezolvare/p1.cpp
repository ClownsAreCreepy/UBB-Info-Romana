#include <fstream>
#include <vector>
#include <queue>

using namespace std;


//functie pentru a genera codarea Prufer
vector<int> Prufer(const int n, const vector<int> &parinte) {
    //Aflam numarul de copii ai tuturor nodurilor arborelui in afara de radacina
    //Astfel gasim frunzele arborelui foarte usor
    vector<int> grad(n, 0);
    for (int i = 0; i < n; ++i)
        if (parinte[i] != -1)
            grad[parinte[i]]++;

    //Putem toate frunzele intr-o coada cu prioritati(greater -> cel mai mic vine primul)
    priority_queue<int, vector<int>, greater<> > frunze;
    for (int i = 0; i < n; ++i)
        if (grad[i] == 0)
            frunze.push(i);

    //Codam
    //Lungimea codului este intotdeauna n-2
    vector<int> prufer;
    for (int i = 0; i < n - 1; ++i) {
        //Alegem frunza cu cel mai mic index
        const int frunza = frunze.top();
        frunze.pop();

        //Luam parintele frunzei si il bagam in codarea prufer, daca parintele nu e radacina
        //Deoarece stergem o frunza, eliminam numarul de copii ai parintelui
        if (int par = parinte[frunza]; par != -1) {
            prufer.push_back(par);
            grad[par]--;

            //Daca parintele nu mai are copii, el devine copil si il bagam in lista de frunze
            if (grad[par] == 0)
                frunze.push(par);
        }
    }
    return prufer;
}


int main(int argc, char *argv[]) {
    ifstream fin(argv[1]);
    ofstream fout(argv[2]);

    //Preluam datele din fisierul de intrare
    int n;
    fin >> n;
    vector<int> parinte(n);
    for (int i = 0; i < n; ++i)
        fin >> parinte[i];

    vector<int> prufer = Prufer(n, parinte);

    //Scriem codarea in fisierul de iesire
    fout << prufer.size() << "\n";
    for (const int i: prufer)
        fout << i << " ";

    fin.close();
    fout.close();
}
