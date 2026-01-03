#include "IteratorColectie.h"
#include "Colectie.h"


IteratorColectie::IteratorColectie(const Colectie& c): col(c) {
    //seteaza iteratorul pe prima pozitie din vector
    curent = 0;
}

void IteratorColectie::prim() {
    //seteaza iteratorul pe prima pozitie din vector
    curent = 0;
}


void IteratorColectie::urmator() {
    //trece la urmatoarea pozitie
    curent++;
}


bool IteratorColectie::valid() const {
    //verifica daca iteratorul indica spre un element al vectorului
    return curent < col.dim();
}


TElem IteratorColectie::element() const {
    //tipareste elementul curent
    if(valid())
        return col.Distincte[col.Pozitii[curent]];
    else
        return -1;
}
