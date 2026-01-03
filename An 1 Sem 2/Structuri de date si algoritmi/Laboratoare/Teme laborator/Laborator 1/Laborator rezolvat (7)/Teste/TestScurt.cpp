#include "TestScurt.h"
#include <assert.h>
#include <iostream>
#include "../Colectie/Colectie.h"
#include "../Colectie/IteratorColectie.h"





void testAll() { //apelam fiecare functie sa vedem daca exista
    Colectie c;
    assert(c.vida() == true);
    assert(c.dim() == 0); //adaug niste elemente
    c.adauga(5);
    c.adauga(1);
    c.adauga(10);
    c.adauga(7);
    c.adauga(1);
    c.adauga(11);
    c.adauga(-3);
    assert(c.dim() == 7);
    assert(c.cauta(10) == true);
    assert(c.cauta(16) == false);
    assert(c.nrAparitii(1) == 2);
    assert(c.nrAparitii(7) == 1);
    assert(c.sterge(1) == true);
    assert(c.sterge(6) == false);
    assert(c.dim() == 6);
    assert(c.nrAparitii(1) == 1);
    IteratorColectie ic = c.iterator();
    ic.prim();
    while (ic.valid()) {
        TElem e = ic.element();
        ic.urmator();
    }

    Colectie v;
    v.adauga(5);
    v.adauga(1);
    v.adauga(10);
    v.adauga(7);
    v.adauga(1);
    v.adauga(11);
    v.adauga(-3);
    assert(v.eliminaAparitii(4, 5) == 1);
    assert(v.cauta(5) == false);
    assert(v.eliminaAparitii(1,1) == 1);
    assert(v.cauta(1) == true);
    v.adauga(8);
    v.adauga(8);
    v.adauga(8);
    assert(v.eliminaAparitii(5,8) == 3);
    assert(v.cauta(8) == false);
    v.adauga(8);
    v.adauga(8);
    v.adauga(8);
    assert(v.eliminaAparitii(1,8) == 1);
    assert(v.nrAparitii(8) == 2);
}