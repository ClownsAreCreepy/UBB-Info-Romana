#include <iostream>
#include <vector>
#include <queue>
#include <fstream>
#include <string>

using namespace std;

struct Punct {
    int x, y;
};

//Directii de miscare
const vector<Punct> directii ={{-1,0}, {1,0}, {0,-1}, {0,1}};


//BFS sa gasim cea mai scurta cale de la S la F
bool BFS(const vector<vector<char>> &labirint, Punct start, Punct final, vector<vector<Punct>> &parinte) {
    int randuri = labirint.size(), coloane = labirint[0].size();
    queue<Punct> q;
    q.push(start);

    //Marcam pozitia de start
    parinte[start.x][start.y] = {-1, -1};

    while (!q.empty()) {
        Punct curent = q.front();
        q.pop();

        //Daca curent are aceleasi coordonate ca final, atunci am ajuns la destinatie
        if (curent.x == final.x && curent.y == final.y)
            return true;

        for (auto dir : directii) {
            Punct urmator = {curent.x + dir.x, curent.y + dir.y};

            //Verificam inconjurarile sa vedem daca avem spatiu liber
            if (urmator.x >= 0 && urmator.x < randuri && urmator.y >=0 && urmator.y < coloane &&
                (labirint[urmator.x][urmator.y] == ' ' || labirint[urmator.x][urmator.y] == 'F') &&
                parinte[urmator.x][urmator.y].x == -1)
            {
                parinte[urmator.x][urmator.y] = curent;
                q.push(urmator);
            }
        }
    }

    //Daca se iese din while, nu s-a gasit cale
    return false;
}


//Functie pentru a reconstrui si a marca labirintul
void reconstruire(vector<vector<char>> &labirint, Punct start, Punct final, vector<vector<Punct>> &parinte) {
    //Daca suntem in functie, inseamna ca am ajuns la final. Ne intoarcem urmarind vectorul parinte pana la start, marcand drumul cu '*"
    Punct curent = final;
    while (!(curent.x == start.x && curent.y == start.y)) {
        curent = parinte[curent.x][curent.y];
        labirint[curent.x][curent.y] = '*';
    }
}


//Functie de citire a labirintului
vector<vector<char>> citire(const string &filename, Punct &start, Punct &final) {
    ifstream fin(filename);
    vector<vector<char>> labirint;
    string linie;
    int rand = 0;

    while (getline(fin, linie)) {
        vector<char> rand_curent;

        //Citim fiecare caracter
        for (int coloana=0; coloana < linie.size(); coloana++) {
            char c = linie[coloana];
            rand_curent.push_back(c);

            //Vedem daca caracterul e start sau final
            if (c == 'S') start = {rand, coloana};
            if (c == 'F') final = {rand, coloana};
        }
        labirint.push_back(rand_curent);
        rand ++;
    }
    return labirint;
}


//Functie de a tipari labirintul
void arataLab(const vector<vector<char>> &labirint) {
    for (const auto &rand : labirint) {
        for (const char coloana : rand) {
            if (coloana == '*')
                cout<<coloana;
            else
                cout<<" ";
        }
        cout<<endl;
    }
}


int main() {
    Punct start, final;
    vector<vector<char>> labirint = citire("labirint_1.txt", start, final);

    //Initializam vectorul parinte cu {-1, -1} sa indicam ca nu e vizitat
    vector<vector<Punct>> parinte(labirint.size(), vector<Punct>(labirint[0].size(), {-1,-1}));

    if (BFS(labirint, start, final,parinte)) {
        reconstruire(labirint, start, final, parinte);
        cout << "Solutie gasita!"<<endl<<endl;
        arataLab(labirint);
    } else cout<<"Nu exista solutie :(";

    return 0;
}