#include "Iterator.h"
#include "DO.h"

using namespace std;

Iterator::Iterator(const DO& d) : dict(d){
    //O(height) / O(log n)
    int current = dict.radacina;
    while (current != -1) {
        stack.push(current);
        current = dict.noduri[current].st;
    }
}

void Iterator::prim(){
    //O(height) / O(log n)
    while (!stack.empty())
        stack.pop();

    int current = dict.radacina;
    while (current != -1) {
        stack.push(current);
        current = dict.noduri[current].st;
    }
}

void Iterator::urmator(){
    //O(height) / O(log n)
    if (!valid())
        throw exception();

    int current = dict.noduri[stack.top()].dr;
    stack.pop();

    while (current != -1) {
        stack.push(current);
        current = dict.noduri[current].st;
    }
}

bool Iterator::valid() const{
    //theta(1)
    return !stack.empty();
}

TElem Iterator::element() const{
    //theta(1)
    if (!valid())
        throw exception();
    return dict.noduri[stack.top()].e;
}


