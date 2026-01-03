#pragma once

#include "../Domain/Tractor.h"
#include <vector>
#include <fstream>
#include <sstream>

class RepoTractoare {
private:
    vector<Tractor> tractoare;
    string file_path;

    void load_from_file();
    void save_to_file();

public:
    RepoTractoare(string fp) : file_path(fp) { load_from_file(); }

    void adaugare(const Tractor &t);
    void decrementare(int id);

    vector<Tractor> &getAll() { return tractoare; }
};