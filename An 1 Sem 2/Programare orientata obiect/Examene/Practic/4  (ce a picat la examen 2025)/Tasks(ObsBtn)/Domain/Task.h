#pragma once

#include <string>
#include <vector>

using namespace std;

class Task {
private:
    int id;
    string descriere;
    vector<string> programatori;
    string stare;

public:
    Task(int i, string d, vector<string> p, string s) : id(i), descriere(move(d)), programatori(move(p)), stare(move(s)) {}

    // Getteri
    int getId() const { return id; }
    const string &getDescriere() const { return descriere; }
    const vector<string> &getProgramatori() const { return programatori; }
    const string &getStare() const { return stare; }

    // Setteri
    void setStare(const string &stare_noua) { stare = stare_noua; }
};