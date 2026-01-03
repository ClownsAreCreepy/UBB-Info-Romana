#include "Iterator.h"
#include "DO.h"
#include <iostream>

#include <exception>
using namespace std;


DO::DO(Relatie r) {
    //theta(capacitate)
    capacitate = 100;
    dimensiune = 0;
    relatie = r;
    radacina = -1;
    firstFree = 0;
    noduri = new Nod[capacitate];

    for (int i = 0; i < capacitate; ++i) {
        noduri[i].st = -1;
        noduri[i].dr = -1;
        noduri[i].height = 1;
    }
}


int DO::height(int index) {
    //theta(1)
    if (index == -1)
        return 0;
    return noduri[index].height;
}

int DO::balanceFactor(int index) {
    //theta(1)
    if (index == -1)
        return 0;
    return height(noduri[index].st) - height(noduri[index].dr);
}

void DO::updateHeight(int index) {
    // theta(1)
    if (index != -1)
        noduri[index].height = 1 + max(height(noduri[index].st), height(noduri[index].dr));
}


int DO::rotateLeft(int index) {
    //theta(1)
    int y = noduri[index].dr;
    int T2 = noduri[y].st;

    noduri[y].st = index;
    noduri[index].dr = T2;

    updateHeight(index);
    updateHeight(y);

    return y;
}

int DO::rotateRight(int index) {
    //theta(1)
    int y = noduri[index].st;
    int T2 = noduri[y].dr;

    noduri[y].dr = index;
    noduri[index].st = T2;

    updateHeight(index);
    updateHeight(y);

    return y;
}

int DO::rebalance(int index) {
    //theta(1)
    updateHeight(index);

    int bf = balanceFactor(index);

    //Stanga e grea
    if (bf > 1) {
        if (balanceFactor(noduri[index].st) < 0)
            noduri[index].st = rotateLeft(noduri[index].st); // Left Right   (Rotate Left -> LL -> Rotate Right)
        return rotateRight(index); // Left or Left Right
    }

    //Dreapta e grea
    if (bf < -1) {
        if (balanceFactor(noduri[index].dr) > 0)
            noduri[index].dr = rotateRight(noduri[index].dr); // Right Left   (Rotate Right -> RR -> Rotate Left
        return rotateLeft(index); // Right or Right Left
    }

    return index;
}


void DO::resize() {
    //theta(capacitate)
    int capacitate_noua = capacitate * 2;
    Nod *noduri_noi = new Nod[capacitate_noua];

    for (int i = 0; i < capacitate; ++i)
        noduri_noi[i] = noduri[i];

    for (int i = capacitate; i < capacitate_noua; ++i) {
        noduri_noi[i].st = -1;
        noduri_noi[i].dr = -1;
        noduri_noi[i].height = 1;
    }

    delete[] noduri;
    noduri = noduri_noi;
    capacitate = capacitate_noua;
}

int DO::adauga_rec(int index, TElem elem, TValoare &veche) {
    //O(height) / O(log n)
    if (index == -1) {
        if (firstFree == capacitate)
            resize();

        int newIndex = firstFree++;
        noduri[newIndex].e = elem;
        noduri[newIndex].st = -1;
        noduri[newIndex].dr = -1;
        noduri[newIndex].height = 1;
        veche = NULL_TVALOARE;
        return newIndex;
    }

    if (elem.first == noduri[index].e.first) {
        veche = noduri[index].e.second;
        noduri[index].e.second = elem.second;
        return index;
    }

    if (relatie(elem.first, noduri[index].e.first)) {
        int child = adauga_rec(noduri[index].st, elem, veche);
        noduri[index].st = child;
    } else {
        int child = adauga_rec(noduri[index].dr, elem, veche);
        noduri[index].dr = child;
    }

    int newRoot = rebalance(index);
    return newRoot;

}

//adauga o pereche (cheie, valoare) in dictionar
//daca exista deja cheia in dictionar, inlocuieste valoarea asociata cheii si returneaza vechea valoare
//daca nu exista cheia, adauga perechea si returneaza null
TValoare DO::adauga(TCheie c, TValoare v) {
    //O(height) / O(log n)
    TValoare veche = NULL_TVALOARE;
    radacina = adauga_rec(radacina, {c, v}, veche);
    if (veche == NULL_TVALOARE)
        dimensiune++;
    return veche;
}


TValoare DO::cauta_rec(int index, TCheie c) const {
    //O(height) / O(log n)
    if (index == -1)
        return NULL_TVALOARE;

    if (noduri[index].e.first == c)
        return noduri[index].e.second;

    if (relatie(c, noduri[index].e.first))
        return cauta_rec(noduri[index].st, c);
    else
        return cauta_rec(noduri[index].dr, c);
}

//cauta o cheie si returneaza valoarea asociata (daca dictionarul contine cheia) sau null
TValoare DO::cauta(TCheie c) const {
    //O(height) / O(log n)
    return cauta_rec(radacina, c);
}


int DO::minim(int index) const {
    while (index != -1 && noduri[index].st != -1)
        index = noduri[index].st;
    return index;
}

int DO::stergere_rec(int index, TCheie c, TValoare &veche) {
    //O(height) / O(log n)
    if (index == -1) {
        veche = NULL_TVALOARE;
        return -1;
    }


    if (c == noduri[index].e.first) {
        veche = noduri[index].e.second;

        //Caz 1: frunza
        if (noduri[index].st == -1 && noduri[index].dr == -1)
            return -1;

        //Caz 2: are un copil
        if (noduri[index].st == -1) {
            return noduri[index].dr;
        }
        if (noduri[index].dr == -1) {
            return noduri[index].st;
        }

        //Caz 3: doi copii
        int succ = minim(noduri[index].dr);
        noduri[index].e = noduri[succ].e;

    } else if (relatie(c, noduri[index].e.first))
        noduri[index].st = stergere_rec(noduri[index].st, c, veche);
    else
        noduri[index].dr = stergere_rec(noduri[index].dr, c, veche);

    return rebalance(index);
}

//sterge o cheie si returneaza valoarea asociata (daca exista) sau null
TValoare DO::sterge(TCheie c) {
    //O(height) / O(log n)
    TValoare veche = NULL_TVALOARE;
    radacina = stergere_rec(radacina, c, veche);
    if (veche != NULL_TVALOARE)
        dimensiune--;
    return veche;
}


//gaseste si returneaza cheia minima a dictionarului
//Daca dictionarul este vid, se returneaza NULL_TCHEIE
TCheie DO::cheieMinima() const {
    //O(height) / O(log n)
    if (dimensiune == 0)
        return NULL_TCHEIE;

    int index = radacina;

    while (noduri[index].st != -1)
            index = noduri[index].st;

    return noduri[index].e.first;
}


//returneaza numarul de perechi (cheie, valoare) din dictionar
int DO::dim() const {
    //theta(1)
    return dimensiune;
}

//verifica daca dictionarul e vid
bool DO::vid() const {
    //theta(1)
    return dimensiune == 0;
}

Iterator DO::iterator() const {
    return Iterator(*this);
}


DO::~DO() {
    //theta(n)
    delete[] noduri;
}
