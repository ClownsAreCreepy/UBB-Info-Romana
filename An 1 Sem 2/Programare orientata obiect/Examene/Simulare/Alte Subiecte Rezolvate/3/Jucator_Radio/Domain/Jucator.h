#pragma once

#include <string>

using namespace std;

class Jucator {
private:
    string nume;
    string tara;
    int puncte;
    int ranking;

public:
    Jucator(string nume, string tara, int puncte, int ranking) : nume(move(nume)), tara(move(tara)), puncte(puncte),
                                                                 ranking(ranking) {
    }

    Jucator() = default;

    //Getteri
    [[nodiscard]] const string &getNume() const { return nume; }
    [[nodiscard]] const string &getTara() const { return tara; }
    [[nodiscard]] int getPuncte() const { return puncte; }
    [[nodiscard]] int getRank() const { return ranking; }

    //Setteri
    void setPuncte(int points) { puncte = points; }
    void setRank(int rank) { ranking = rank; }
};
