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
    Jucator(string name, string tara, int points, int rank) : nume(move(name)), tara(move(tara)), puncte(points),
                                                              ranking(rank) {
    }

    Jucator() = default;

    //Getteri
    const string &getNume() const { return nume; }
    const string &getTara() const { return tara; }
    int getPuncte() const { return puncte; }
    int getRank() const { return ranking; }

    //Setteri
    void setRank(int ranc) { ranking = ranc; };
};
