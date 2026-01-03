#pragma once

#include "../Domain/Jucatori.h"
#include <vector>
#include <sstream>
#include <fstream>

class RepoJucatori {
private:
    vector<Jucator> jucatori;
    string file_path;

    void load_from_file();

public:
    RepoJucatori(string file) : file_path(move(file)) { load_from_file(); }

    void adauga(const Jucator &j);

    vector<Jucator> &getAll() { return jucatori; }
};
