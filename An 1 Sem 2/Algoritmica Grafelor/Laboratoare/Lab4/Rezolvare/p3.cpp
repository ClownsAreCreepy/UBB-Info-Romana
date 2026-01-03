#include <fstream>
#include <unordered_map>
#include <map>
#include<queue>
#include <string>
#include <algorithm>
#include <iostream>

using namespace std;


//Nod din arbore
struct Nod {
    char ch;
    int freq;
    Nod *left, *right;

    //Constructor pentru nod frunza
    Nod(const char c, int f) : ch(c), freq(f), left(nullptr), right(nullptr) {}

    //Constructor pentru celelalte noduri
    Nod(Nod *l, Nod *r) : ch('\0'), freq(l->freq + r->freq), left(l), right(r) {}
};


//logica de comparare pentru coada cu prioritate
struct Compare {
    bool operator()(const Nod *a, const Nod *b) const {
        if (a->freq == b->freq)
            return a->ch > b->ch; //daca sunt egale, luam ordinea lexicografica
        return a->freq > b->freq;
    }
};


//generam arborele Huffman
void generateCode(const Nod *root, const string &code, unordered_map<char, string> &huff) {
    if (!root) return;
    if (!root->left && !root->right) {
        huff[root->ch] = code;
        return;
    }
    generateCode(root->left, code + "0", huff);
    generateCode(root->right, code + "1", huff);
}

//eliberam memorie
void deleteTree(const Nod *root) {
    if (!root) return;
    deleteTree(root->left);
    deleteTree(root->right);
    delete root;
}

int main(int argc, char *argv[]) {
    ifstream fin(argv[1]);
    ofstream fout(argv[2]);

    string text;
    getline(fin, text);
    fin.close();


    //Numaram frecventa fiecarui caracter
    unordered_map<char, int> freq;
    for (char c: text)
        freq[c]++;


    //Construim lista de prioritati
    priority_queue<Nod *, vector<Nod *>, Compare> pq;
    for (auto &[c, f]: freq)
        pq.push(new Nod(c, f));


    //Construim arborele Huffman
    while (pq.size() > 1) {
        Nod *left = pq.top();
        pq.pop();

        Nod *right = pq.top();
        pq.pop();

        auto unire = new Nod(left, right);
        pq.push(unire);
    }

    Nod *root = pq.top();


    //Generam codul Huffman din arbore
    unordered_map<char, string> CodHuff;
    generateCode(root, "", CodHuff);


    //Codam input-ul
    string encoded;
    for (char c: text)
        encoded += CodHuff[c];


    //sortam aflabetic si scriem in fisierul de output
    fout << freq.size() << '\n';

    map<char, int> sorted(freq.begin(), freq.end());
    for (auto &[c, f]: sorted)
        fout << c << " " << f << '\n';

    fout << encoded << '\n';

    fout.close();
    deleteTree(root);
    return 0;
}
