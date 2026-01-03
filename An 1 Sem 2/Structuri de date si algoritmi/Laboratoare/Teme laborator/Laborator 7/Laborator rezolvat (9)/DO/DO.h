#pragma once

typedef int TCheie;
typedef int TValoare;

#include <utility>
typedef std::pair<TCheie, TValoare> TElem;

#include <limits>

#define NULL_TVALOARE std::numeric_limits<int>::min()
#define NULL_TCHEIE 0


class Iterator;

typedef bool (*Relatie)(TCheie, TCheie);

struct Nod {
    TElem e;
    int st;
    int dr;
    int height;
};

class DO {
    friend class Iterator;

private:
    int radacina;
    int firstFree;
    int capacitate;
    int dimensiune;
    Relatie relatie;

    Nod *noduri;


    int height(int index); // returneaza inaltimea nodului (0 daca nu exista)

    int balanceFactor(int index); // returneaza factorul de balanta

    void updateHeight(int index); // seteaza inaltimea unui nod

    int rotateLeft(int index); // roteste arborele la care index e radacina la stanga, returneaza noua radacina

    int rotateRight(int index); // roteste arborele la care index e radacina la dreapta, returneaza noua radacina

    int rebalance(int index); // verifica factorul de balanta si aplica rotatia potrivita, returneaza radacina

    void resize(); // mareste capacitatea vectorului de noduri de 2 ori cat era inainte


    int adauga_rec(int index, TElem elem, TValoare &veche);

    TValoare cauta_rec(int index, TCheie c) const;

    int stergere_rec(int index, TCheie c, TValoare &veche);

    int minim(int index) const; // returneaza cel mai mic copil al nodului

public:
    // constructorul implicit al dictionarului
    DO(Relatie r);


    // adauga o pereche (cheie, valoare) in dictionar
    //daca exista deja cheia in dictionar, inlocuieste valoarea asociata cheii si returneaza vechea valoare
    // daca nu exista cheia, adauga perechea si returneaza null: NULL_TVALOARE
    TValoare adauga(TCheie c, TValoare v);


    //cauta o cheie si returneaza valoarea asociata (daca dictionarul contine cheia) sau null: NULL_TVALOARE
    TValoare cauta(TCheie c) const;


    //sterge o cheie si returneaza valoarea asociata (daca exista) sau null: NULL_TVALOARE
    TValoare sterge(TCheie c);


    //gaseste si returneaza cheia minima a dictionarului
    //Daca dictionarul este vid, se returneaza NULL_TCHEIE
    TCheie cheieMinima() const;


    //returneaza numarul de perechi (cheie, valoare) din dictionar
    int dim() const;

    //verifica daca dictionarul e vid
    bool vid() const;

    // se returneaza iterator pe dictionar
    // iteratorul va returna perechile in ordine dupa relatia de ordine (pe cheie)
    Iterator iterator() const;


    // destructorul dictionarului
    ~DO();
};
