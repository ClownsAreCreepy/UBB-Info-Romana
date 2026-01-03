#include "Iterator.h"
#include "DO.h"
#include <exception>

using namespace std;

Iterator::Iterator(const DO& d) : dict(d){ //theta(m + n^2)
    dim = dict.len;
    curent = 0;
    elemente = new TElem[dim];

    int idx = 0;
    for (int i = 0; i < dict.m; ++i)
        if (dict.stare[i] == OCUPAT)
            elemente[idx++] = dict.tabela[i];


    sort();
}

void Iterator::sort() { //theta(n^2)
    for (int i = 0; i < dim - 1; ++i)
        for (int j = i + 1; j < dim; ++j)
            if (!dict.rel(elemente[i].first, elemente[j].first))
                std::swap(elemente[i], elemente[j]);
}


void Iterator::prim(){ //theta(1)
    curent = 0;
}

void Iterator::urmator(){ //theta(1)
    if (!valid())
        throw std::exception();
    curent++;
}

bool Iterator::valid() const{ //theta(1)
    return curent < dim;
}

TElem Iterator::element() const{ //theta(1)
    if (!valid())
        throw std::exception();
    return elemente[curent];
}


