#pragma once

#define CAPACITATE_DE_INCEPUT 8
typedef int TElem;

class IteratorMultime;

class Multime {
    friend class IteratorMultime;

private:
    struct Nod {
        TElem elem;
        int urm;
        int prec;
    };

    Nod* noduri;            // vector de noduri
    int cap;                // capacitate
    int prim;               // indexul primului element (capul listei)
    int ultim;              // indexul ultimului element (coada listei)
    int primLiber;          // prima pozitie libera
    int lungime;            // numarul de elemente din vector

    //helpers
    int aloca();           // aloca un nod nou liber

    void dealoca(int i);    // elibereaza un nod

    void resize();          // mareste capacitatea vectorului cand acesta e plin

    int creeazaNod(TElem e);// creaza un nod nou

public:
    //constructorul implicit
    Multime();

    //adauga un element in multime
    //returneaza adevarat daca elementul a fost adaugat (nu exista deja in multime)
    bool adauga(TElem elem);

    //adauga toate elementele din multimea b in multimea curenta
    void reuniune(const Multime &b);

    //sterge un element din multime
    //returneaza adevarat daca elementul a existat si a fost sters
    bool sterge(TElem e);

    //verifica daca un element se afla in multime
    bool cauta(TElem elem) const;


    //intoarce numarul de elemente din multime;
    int dim() const;

    //verifica daca multimea e vida;
    bool vida() const;

    //returneaza un iterator pe multime
    IteratorMultime iterator() const;

    // destructorul multimii
    ~Multime();
};




