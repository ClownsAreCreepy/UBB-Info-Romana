#pragma once

#include <string>

using namespace std;

class Melodie {
private:
    int id;
    string titlu;
    string artist;
    string gen;

public:
    Melodie(int i, string t, string a, string g) : id(i), titlu(move(t)), artist(move(a)), gen(move(g)) {}

    //Getteri
    [[nodiscard]] int getId() const { return id; }
    [[nodiscard]] const string &getTitlu() const { return titlu; }
    [[nodiscard]] const string &getArtist() const { return artist; }
    [[nodiscard]] const string &getGen() const { return gen; }
};