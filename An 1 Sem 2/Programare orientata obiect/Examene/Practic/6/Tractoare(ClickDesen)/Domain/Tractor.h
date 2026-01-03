#pragma once

#include <string>

using namespace std;

class Tractor {
private:
    int id;
    string denumire;
    string tip;
    int numarRoti;

public:
    Tractor(int i, string d, string t, int n) : id(i), denumire(move(d)), tip(move(t)), numarRoti(n) {}

    //Getteri
    int getId() const { return id; }
    const string &getDenumire() const { return denumire; }
    const string &getTip() const { return tip; }
    int getRoti() const { return numarRoti; }

    // Setteri
    void decRoti() { numarRoti -= 2; }
};