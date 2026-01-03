#pragma once

#include "../Domain/Jucator.h"
#include <vector>
#include <fstream>
#include <sstream>

class RepoJucator {
private:
    vector<Jucator> jucatori;
    string file_path;

    void load_from_file();

public:
    explicit RepoJucator(string file) : file_path(move(file)) { load_from_file(); }

    void adauga(const Jucator &j);
    void sterge(int m);

     vector<Jucator> &getAll() { return jucatori; }
};
