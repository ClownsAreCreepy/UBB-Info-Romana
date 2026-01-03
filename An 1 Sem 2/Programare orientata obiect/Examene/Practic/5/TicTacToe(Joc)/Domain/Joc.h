#pragma once

#include <string>

using namespace std;

class Joc {
private:
    int id;
    int dim;
    string tabla;
    string jucator;
    string stare;

public:
    Joc(int i, int d, string t, string j, string s) : id(i), dim(d), tabla(move(t)), jucator(move(j)), stare(move(s)) {}

    //Getteri
    int getId() const { return id; }
    int getDimensiune() const { return dim; }
    const string &getTabla() const { return tabla; }
    const string &getJucator() const { return jucator; }
    const string &getStare() const { return stare; }

    //Setteri
    void setDimensiune(int dim_noua) { dim = dim_noua; }
    void setTabla(const string &tabla_noua) { tabla = tabla_noua; }
    void setJucator(const string &jucator_nou) { jucator = jucator_nou; }
    void setStare(const string &stare_noua) { stare = stare_noua; }

};