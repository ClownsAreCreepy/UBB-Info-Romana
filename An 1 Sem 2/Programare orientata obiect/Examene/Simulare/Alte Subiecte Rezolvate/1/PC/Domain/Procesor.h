#pragma once

#include <string>

using namespace std;

class Procesor {
private:
    string nume;
    int nrThreaduri = 0;
    string socluProcesor;
    int pret = 0;

public:
    Procesor(string nume, int threads, string soclu, int pret) : nume(move(nume)), nrThreaduri(threads), socluProcesor(move(soclu)), pret(pret) {}
    Procesor() =default;

    //Getteri
    [[nodiscard]] const string &getNume() const noexcept { return nume; }
    [[nodiscard]] int getNrThreaduri() const { return nrThreaduri; }
    [[nodiscard]] const string &getSocluProcesor() const noexcept { return socluProcesor; }
    [[nodiscard]] int getPret() const { return pret; }
};