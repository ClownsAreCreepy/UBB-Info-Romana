#include "IteratorMultime.h"
#include "Multime.h"
#include <exception>


IteratorMultime::IteratorMultime(const Multime& m) : multime(m){ //theta(1)
    curent = multime.prim;      // incepem de la primul nod
}


void IteratorMultime::prim() { //theta(1)
    curent = multime.prim;
}


void IteratorMultime::urmator() { //theta(1)
    if ( ! valid())
        throw std::exception();

    curent = multime.noduri[curent].urm;
}


TElem IteratorMultime::element() const { //theta(1)
    if ( ! valid())
        throw std::exception();

    return multime.noduri[curent].elem;
}

bool IteratorMultime::valid() const { //theta(1)
    return curent != -1;
}
