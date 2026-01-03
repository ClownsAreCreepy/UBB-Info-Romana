#include <fstream>
#include <queue>
#include <unordered_map>
#include <string>
#include <map>

using namespace std;


//Nod din arbore
struct Nod {
    char ch;
    int freq;
    Nod *left, *right;

    //Constructor pentru nodul frunza
    Nod(const char c, int f) : ch(c), freq(f), left(nullptr), right(nullptr) {}

    //Constructor pentru celelalte noduri
    Nod(Nod *l, Nod *r) : ch('\0'), freq(l->freq + r->freq), left(l), right(r) {}
};


//Functie de comparare pentru coada cu prioritate
struct Compare {
    bool operator()(const Nod *a, const Nod *b) const {
        if (a->freq == b->freq)
            return a->ch > b->ch; //daca sunt egale, le luam in ordine lexicografica
        return a->freq > b->freq;
    }
};


//stergem arborele Huffman
void deleteTree(const Nod *root) {
    if (!root) return;
    deleteTree(root->left);
    deleteTree(root->right);
    delete root;
}

int main(int argc, char *argv[]) {
    ifstream fin(argv[1]);
    ofstream fout(argv[2]);

    //Citim fisierul si luam numarul de litere distincte, literele, cu frecventele lor, si codul Huffman
    int N;
    fin >> N;
    map<char, int> freqMap;

    for (int i = 0; i < N; ++i) {
        char ch;
        int freq;
        fin >> ws; //sarim peste new line
        ch = fin.get(); //citim caracterul cu tot cu spatiu
        fin >> freq;
        freqMap[ch] = freq;
    }

    string bitstring;
    fin >> bitstring;
    fin.close();

    //construim arborele Huffman din freqMap
    priority_queue<Nod *, vector<Nod *>, Compare> pq;
    for (auto &[c, f]: freqMap)
        pq.push(new Nod(c, f));

    while (pq.size() > 1) {
        Nod *a = pq.top();
        pq.pop();

        Nod *b = pq.top();
        pq.pop();

        pq.push(new Nod(a, b));
    }

    Nod *root = pq.top();

    //decodam insiruirea de biti
    string decoded;
    Nod *NodCurent = root;

    for (char bit: bitstring) {
        if (bit == '0')
            NodCurent = NodCurent->left;
        else
            NodCurent = NodCurent->right;

        if (!NodCurent->left && !NodCurent->right) {
            decoded += NodCurent->ch;
            NodCurent = root;
        }
    }

    fout << decoded;
    fout.close();

    deleteTree(root);
    return 0;
}
