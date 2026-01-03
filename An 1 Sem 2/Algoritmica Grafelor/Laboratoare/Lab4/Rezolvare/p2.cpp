#include <fstream>
#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int n, x;
vector<int> prufer, nr_copii;

vector<int> Decodare(const vector<int>& prufer, vector<int> nr_copii) {
    //Populam lista de frunze cu nodurile frunza (care au 0 copii)
    priority_queue<int, vector<int>, greater<> > frunze;
    for (int i = 0; i < n + 1; ++i)
        if (nr_copii[i] == 0)
            frunze.push(i);

    vector<int> parinti(prufer.size() + 1, -1);

    for (int par_nod_min: prufer) {
        const int nod_min = frunze.top();
        frunze.pop();

        parinti[nod_min] = par_nod_min;
        nr_copii[par_nod_min]--;
        if (nr_copii[par_nod_min] == 0)
            frunze.push(par_nod_min);
    }

    return parinti;
}

int main(int argc, char *argv[]) {
    ifstream fin(argv[1]);
    ofstream fout(argv[2]);

    //Preluam numarul de valori din codarea prufer, care vor fi numarul de noduri - 1
    fin >> n;
    prufer.resize(n);
    nr_copii.resize(n + 1, 0);
    fout << n + 1 << endl;

    //Preluam numerele din codarea prufer, si astfel aflam cati copii are fiecare nod
    for (int i = 0; i < n; ++i) {
        fin >> x;
        nr_copii[x]++;
        prufer[i] = x;
    }

    vector<int> parinte = Decodare(prufer, nr_copii);
    for (const int i: parinte)
        fout << i << " ";

    fin.close();
    fout.close();
}
