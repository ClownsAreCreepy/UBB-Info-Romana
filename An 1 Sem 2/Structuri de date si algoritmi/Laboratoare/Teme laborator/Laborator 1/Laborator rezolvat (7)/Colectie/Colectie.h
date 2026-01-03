#pragma once

#define NULL_TELEM -1
typedef int TElem;

class IteratorColectie;

class Colectie
{
    friend class IteratorColectie;

private:
    //capacitate
    int capacitate;

    //dimensiunile
    int dim_pozitii;
    int dim_distincte;

    //vectorul de pozitii
    int *Pozitii;

    //vectorul de elemente
    TElem *Distincte;

    //pentru redimensionare cu o anumita capacitate
    void redimensionare(int cap);

public:
    //constructorul implicit
    Colectie();

    //adauga un element in colectie
    void adauga(TElem e);

    //sterge o aparitie a unui element din colectie
    //returneaza adevarat daca s-a putut sterge
    bool sterge(TElem e);

    //elimina nr aparitii ale elementului elem. In cazul in care elementul apare mai putin de nr ori, toate aparitiile sale vor fi eliminate
    //returneaza numarul de aparitii eliminate ale elementului
    //arunca exceptie in cazul in care nr este negativ
    int eliminaAparitii(int nr, TElem elem);

    //verifica daca un element se afla in colectie
    bool cauta(TElem elem) const;

    //returneaza numar de aparitii ale unui element in colectie
    int nrAparitii(TElem elem) const;

    //intoarce numarul de elemente din colectie;
    int dim() const;

    //verifica daca colectia e vida;
    bool vida() const;

    //returneaza un iterator pe colectie
    IteratorColectie iterator() const;

    // destructorul colectiei
    ~Colectie();

};

