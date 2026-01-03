#pragma once

#include <string>

using namespace std;

class Produs {
private:
    int id;
    string nume;
    string tip;
    double pret;

public:
    Produs(int i, string n, string t, double p) : id(i), nume(move(n)), tip(move(t)), pret(p) {}

    //Getteri
    [[nodiscard]] int getId() const { return id; }
    [[nodiscard]] const string &getNume() const { return nume; }
    [[nodiscard]] const string &getTip() const { return tip; }
    [[nodiscard]] double getPret() const { return pret; }
};