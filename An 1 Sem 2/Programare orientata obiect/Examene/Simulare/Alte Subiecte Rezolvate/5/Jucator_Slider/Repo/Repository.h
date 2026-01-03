#pragma once

#include "../Domain/Jucatori.h"
#include <vector>
#include <fstream>
#include <sstream>

class RepoJucatori {
private:
    vector<Jucator> jucatori;
    string file_path;

    void load_from_file();

public:
    explicit RepoJucatori(const string &file) : file_path(move(file)) { load_from_file(); }

    vector<Jucator> &getAll() { return jucatori; }
};
