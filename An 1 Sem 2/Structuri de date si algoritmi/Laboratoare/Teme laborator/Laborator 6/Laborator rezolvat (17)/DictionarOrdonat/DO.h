#pragma once

typedef int TCheie;
typedef int TValoare;

#define NULL_TVALOARE (-1)
#define CAPACITATE_INITIALA 13
#define LIBER 0
#define OCUPAT 1
#define STERS 2


#include <utility>
#include <unordered_map>

typedef std::pair<TCheie, TValoare> TElem;

class Iterator;

typedef bool(*Relatie)(TCheie, TCheie);

class DO {
    friend class Iterator;
private:
    TElem *tabela;      // hash table
    int *stare;         // 0 = liber, 1 = ocupat, 2 = sters
    int m;              // current table size
    int len;            // current nr of elements
    Relatie rel;        // the ordering relation

    int hash1(TCheie c) const;
    int hash2(TCheie c) const;          // functii hash (trebe 2)
    int pozitie(TCheie c, int i) const; // functie pentru a combine ambele hash-uri
    int findPoz(TCheie c) const;        // helper pentru a gasi pozitia lui c
    void resize();                      // redimensioneaza tabela
public:

    // constructorul implicit al dictionarului
    DO(Relatie r);


    // adauga o pereche (cheie, valoare) in dictionar
    //daca exista deja cheia in dictionar, inlocuieste valoarea asociata cheii si returneaza vechea valoare
    // daca nu exista cheia, adauga perechea si returneaza null: NULL_TVALOARE
    TValoare adauga(TCheie c, TValoare v);


    //cauta o cheie si returneaza valoarea asociata (daca dictionarul contine cheia) sau null: NULL_TVALOARE
    TValoare cauta(TCheie c) const;


    // returneaza valoarea care apare cel mai frecvent in dictionar.
    // daca mai multe valori apar cel mai frecvent, se returneaza una (oricare) dintre ele
    // daca disctionarul este vid, operatia returneaza NULL_TVALOARE
    TValoare ceaMaiFrecventaValoare() const;


    //sterge o cheie si returneaza valoarea asociata (daca exista) sau null: NULL_TVALOARE
    TValoare sterge(TCheie c);

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
