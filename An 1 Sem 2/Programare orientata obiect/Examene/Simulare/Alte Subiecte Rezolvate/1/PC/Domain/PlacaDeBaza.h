#pragma once

#include <string>

using namespace std;

class PlacaDeBaza {
private:
    string nume;
    string socluProcesor;
    int pret = 0;

public:
    PlacaDeBaza(string nume, string soclu, int pret) : nume(move(nume)), socluProcesor(move(soclu)), pret(pret) {}
    PlacaDeBaza() = default;

    //Getteri
    [[nodiscard]] const string &getNume() const noexcept{ return nume; }
    [[nodiscard]] const string &getSocluProcesor() const noexcept { return socluProcesor; }
    [[nodiscard]] int getPret() const { return pret; }
};
