#include "TestScurt.h"
#include <assert.h>
#include "../Multime/Multime.h"
#include "../Multime/IteratorMultime.h"

void testAll() { //apelam fiecare functie sa vedem daca exista
    Multime m;
    assert(m.vida() == true);
    assert(m.dim() == 0); //adaug niste elemente
    assert(m.adauga(5)==true);
    assert(m.adauga(1)==true);
    assert(m.adauga(10)==true);
    assert(m.adauga(7)==true);
    assert(m.adauga(1)==false);
    assert(m.adauga(10)==false);
    assert(m.adauga(-3)==true);
    assert(m.dim() == 5);
    assert(m.cauta(10) == true);
    assert(m.cauta(16) == false);
    assert(m.sterge(1) == true);
    assert(m.sterge(6) == false);
    assert(m.dim() == 4);


    IteratorMultime im = m.iterator();
    im.prim();
    int s = 0;
    while (im.valid()) {
        TElem e = im.element();
        s += e;
        im.urmator();
    }
    assert(s == 19);

    Multime a;
    a.adauga(1);
    a.adauga(2);
    a.adauga(3);
    a.adauga(4);

    Multime b;
    b.adauga(5);
    b.adauga(6);
    b.adauga(7);
    b.adauga(8);

    a.reuniune(b);
    assert(a.dim() == 8);

    for (int i=0; i < 8; ++i)
        assert(a.cauta(i+1) == true);
    assert(a.cauta(9) == false);
}
