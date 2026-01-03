#pragma once

#include <string>
#include <iostream>

using namespace std;

class Rochie {
private:
    int id;
    string denumire;
    string marime;
    int pret;
    string disponibilitate;

public:
    //Constructor implicit
    Rochie() = default;

    //Constructor explicit
    Rochie(int id, string nume, string marime, int pret, string disponibil) : id{id}, denumire{move(nume)},
                                                                              marime{move(marime)},
                                                                              pret{pret},
                                                                              disponibilitate{move(disponibil)} {
    }

    //Constructor de copiere
    Rochie(const Rochie &ot) = default;


    //Getteri
    [[nodiscard]] int getID() const noexcept { return id; }
    [[nodiscard]] const string &getDenumire() const noexcept { return denumire; }
    [[nodiscard]] const string &getMarime() const noexcept { return marime; }
    [[nodiscard]] int getPret() const noexcept { return pret; }
    [[nodiscard]] const string &getDisponibilitate() const noexcept { return disponibilitate; }
};
