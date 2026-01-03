#include "DO.h"
#include "Iterator.h"
#include "DO.h"
#include <iostream>

#include <exception>
using namespace std;

DO::DO(Relatie r) { //theta(1) (in caz general theta(m)
    m = CAPACITATE_INITIALA;
    len = 0;
    rel = r;

    tabela = new TElem[m];
    stare = new int[m];

    for (int i = 0; i < m; ++i)
        stare[i] = LIBER;
}

int DO::hash1(TCheie c) const { //theta(1)
    return abs(c) % m;
}

int DO::hash2(TCheie c) const { //theta(1)
    return 1 + abs(c) % (m - 1);
}

int DO::pozitie(TCheie c, int i) const { //theta(1)
    return (hash1(c) + i*hash2(c)) % m;
}

int DO::findPoz(TCheie c) const { //O(m)
    for (int i = 0; i < m; ++i) {
        int index = pozitie(c, i);

        if (stare[index] == LIBER)
            return -1;              // nu e in tabela

        if (stare[index] == OCUPAT && tabela[index].first == c)
            return index; // GASIT!

        // else, stare == STERS sau cheia e gresita -> ne mai uitam
    }

    return -1; // ciclu complet, nu exista
}

void DO::resize() { //theta(m)
    int oldM = m;
    m = 2 * m + 1; // sau urmatorul numar prim

    TElem *oldTabela = tabela;
    int *oldStare = stare;

    tabela = new TElem[m];
    stare = new int[m];

    for (int i = 0; i < m; ++i)
        stare[i] = LIBER;

    len = 0;

    for (int i = 0; i < oldM; ++i)
        if (oldStare[i] == OCUPAT) {
            TCheie c = oldTabela[i].first;
            TValoare v = oldTabela[i].second;

            adauga(c, v);
        }

    delete[] oldTabela;
    delete[] oldStare;
}




//adauga o pereche (cheie, valoare) in dictionar
//daca exista deja cheia in dictionar, inlocuieste valoarea asociata cheii si returneaza vechea valoare
//daca nu exista cheia, adauga perechea si returneaza null
TValoare DO::adauga(TCheie c, TValoare v) { //O(m)
    int primaStergere = -1;

    for (int i = 0; i < m; ++i) {
        int index = pozitie(c,i);

        if (stare[index] == OCUPAT && tabela[index].first == c) {
                // cheia exista deja -> inlocuim valoarea
                TValoare veche = tabela[index].second;
                tabela[index].second = v;
                return veche;
            }

        if (stare[index] == STERS) {
            if (primaStergere == -1)
                primaStergere = index;
        }
        else if (stare[index] == LIBER) {
            if (primaStergere != -1)
                index = primaStergere;

            tabela[index] = std::make_pair(c, v);
            stare[index] = OCUPAT;
            len++;

            if (len > m * 0.7)
                resize();

            return NULL_TVALOARE;
        }

    }

    // daca nu s-a gasit un LIBER, dar aveam un loc STERS inainte
    if (primaStergere != -1) {
        tabela[primaStergere] = std::make_pair(c, v);
        stare[primaStergere] = OCUPAT;
        len++;

        if (len > m * 0.7)
            resize();

        return NULL_TVALOARE;
    }
}

//cauta o cheie si returneaza valoarea asociata (daca dictionarul contine cheia) sau null
TValoare DO::cauta(TCheie c) const { //O(m)
    int index = findPoz(c);
    if (index == -1)
        return NULL_TVALOARE;
    return tabela[index].second;
}

//sterge o cheie si returneaza valoarea asociata (daca exista) sau null
TValoare DO::sterge(TCheie c) { //O(m)
    int index = findPoz(c);
    if (index == -1)
        return NULL_TVALOARE;

    TValoare valoare = tabela[index].second;
    stare[index] = STERS;
    len --;
    return valoare;
}


// returneaza valoarea care apare cel mai frecvent in dictionar.
// daca mai multe valori apar cel mai frecvent, se returneaza una (oricare) dintre ele
// daca disctionarul este vid, operatia returneaza NULL_TVALOARE
TValoare DO::ceaMaiFrecventaValoare() const { //O(m)
    Iterator it = iterator();
    unordered_map<TValoare, int> freq;
    int max = 0;
    TValoare max_val;

    if (vid())
        return NULL_TVALOARE;

    while (it.valid()) {
        TValoare val_curenta = it.element().second;
        freq[val_curenta] ++;
        if (freq[val_curenta] > max) {
            max = freq[val_curenta];
            max_val = val_curenta;
        }
        it.urmator();
    }

    return max_val;
}



//returneaza numarul de perechi (cheie, valoare) din dictionar
int DO::dim() const { //theta(1)
    return len;
}

//verifica daca dictionarul e vid
bool DO::vid() const { //theta(1)
    return len == 0;
}

Iterator DO::iterator() const { //theta(1)
    return  Iterator(*this);
}

DO::~DO() {
    delete[] tabela;
    delete[] stare;
}