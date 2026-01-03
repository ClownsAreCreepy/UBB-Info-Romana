#pragma once
#include <string>

using namespace std;

class Melodie {
private:
    int id;
    string titlu;
    string artist;
    int rank;

public:
    Melodie(int id, string titlu, string artist, int rank) : id(id), titlu(move(titlu)), artist(move(artist)), rank(rank) {}
    Melodie() = default;

    // Getteri
    [[nodiscard]] int getId() const { return id; }
    [[nodiscard]] const string &getTitlu() const { return titlu; }
    [[nodiscard]] const string &getArtist() const { return artist; }
    [[nodiscard]] int getRank () const { return rank; }

    // Setteri
    void setTitlu(const string &titlu_nou) { titlu = titlu_nou; }
    void setRank(int rank_nou) { rank = rank_nou; }
};