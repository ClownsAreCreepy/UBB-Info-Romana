#include "Multime.h"
#include "IteratorMultime.h"


Multime::Multime() { //theta(1)
    //lista e vida
    prim = -1;
    ultim = -1;
    lungime = 0;

    //capacitatea de inceput e de 8
    cap = CAPACITATE_DE_INCEPUT;

    //referina sprea prima pozitie libera din lista
    primLiber = 0;

    //alocam spatiu pentru vector
    noduri = new Nod[cap];

    // se initializeaza lista spatiului liber - toate pozitiile din vector sunt marcate ca fiind libere
    for (int i = 0; i < cap - 1; ++i)
        noduri[i].urm = i + 1;
    noduri[cap - 1].urm = -1; //ultima pozitie nu duce la nimic
}


int Multime::aloca() { //theta(1)
    //se sterge primul element din lista spatiului liber
    const int i = primLiber;
    primLiber = noduri[primLiber].urm;
    return i;
}


void Multime::dealoca(int i) { //theta(1)
    //se trece pozitia i in lista spatiului liber
    noduri[i].urm = primLiber;
    primLiber = i;
}


void Multime::resize() { //theta(n)
    const int cap_noua = 2 * cap;
    const auto noduri_noi = new Nod[cap_noua];

    //copiem nodurile existente
    for (int i = 0; i < cap; ++i)
        noduri_noi[i] = noduri[i];

    //pregatim pozitiile noi
    for (int i = cap; i < cap_noua - 1; ++i)
        noduri_noi[i].urm = i + 1;
    noduri_noi[cap_noua - 1].urm = -1;

    //modificam primLiber sa fie pe pozitia capacitatii anterioare, pentru ca acuma e pe -1
    primLiber = cap;

    //modificam capacitatea
    cap = cap_noua;

    //eliberam memoria veche
    delete[] noduri;
    noduri = noduri_noi;
}


int Multime::creeazaNod(TElem e) { //theta(1)
    if (primLiber == -1)
        resize(); // daca nu mai avem spatiu, marim vectorul

    const int i = aloca();
    if (i != -1) {
        //exista spatiu liber in lista
        noduri[i].elem = e;
        noduri[i].prec = -1;
        noduri[i].urm = -1; //nu avem inainte si inapoi inca
    }
    return i;
}


//inseram la inceputul multimii
bool Multime::adauga(TElem elem) { //O(n)
    //intai verificam daca elementul exista deja in multime
    int i = prim;
    while (i != -1) {
        if (noduri[i].elem == elem)
            return false;
        i = noduri[i].urm;
    }

    //daca nu exista, il adaugam:
    //creem un nod nou si modificam lungimea
    const int nod_nou = creeazaNod(elem);
    lungime ++;

    //adaugam nodul pe prima pozitie
    noduri[nod_nou].urm = prim;
    noduri[nod_nou].prec = -1;

    //daca lista e goala, atunci nodul nou devine si ultim
    if (prim != -1)
        noduri[prim].prec = nod_nou;
    else
        ultim = nod_nou;

    prim = nod_nou;
    return true;
}

void Multime::reuniune(const Multime &b) { //O((nr_elem_din_b) * n)
    IteratorMultime it = b.iterator();
    while (it.valid()) {
        const TElem elem = it.element();
        adauga(elem);
        it.urmator();
    }
}

bool Multime::sterge(const TElem e) { //O(n)
    int i = prim;

    //verificam daca exista un nod care contine elementul
    while (i != -1 && noduri[i].elem != e)
        i = noduri[i].urm;

    //daca elementul nu exista, iesim din functie
    if (i == -1)
        return false;

    //avem 3 cazuri: stergem cap, coada sau undeva in mijloc

    if (i == prim) {  //stergem cap:
        prim = noduri[i].urm;
        if (prim == -1) // daca coada e goala dupa stergere
            ultim = -1;
        else            // daca nu, setam precedentul nodului nou prim
            noduri[prim].prec = -1;

    }
    else if (i == ultim) {  //stergem coada
        ultim = noduri[i].prec;
        noduri[ultim].urm = -1;
    }

    else {  //stergem in mijloc
        const int prev = noduri[i].prec;
        const int next = noduri[i].urm;
        noduri[prev].urm = next;
        noduri[next].prec = prev;
    }

    dealoca(i);     //eliberam nodul
    lungime --;     //modificam lungimea
    return true;
}


bool Multime::cauta(TElem elem) const { //O(n)
    int i = prim;
    while (i != -1) {
        if (noduri[i].elem == elem)
            return true;
        i = noduri[i].urm;
    }
    return false;
}


int Multime::dim() const { //theta(1)
    return lungime;
}


bool Multime::vida() const { //theta(1)
    return lungime == 0;
}


Multime::~Multime() { //theta(1)
    //stergem vectorul
    delete[] noduri;
    noduri = nullptr;

    //anihilam variabilele
    cap = 0;
    primLiber = -1;
    prim = -1;
    ultim = -1;
    lungime = 0;
}


IteratorMultime Multime::iterator() const { //theta(1)
    return IteratorMultime(*this);
}