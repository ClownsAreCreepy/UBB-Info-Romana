#pragma once

#include "../Domain/Melodii.h"
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>

class RepoMelodii {
private:
    vector<Melodie> melodii;
    string file_path;

    void load_from_file();
    void save_to_file() const;

public:
    explicit RepoMelodii(string fp) : file_path(move(fp)) { load_from_file(); }

    void adaugare(const Melodie &m);
    void stergere(int idx);

    const vector<Melodie> &getAll() const { return melodii; }
};