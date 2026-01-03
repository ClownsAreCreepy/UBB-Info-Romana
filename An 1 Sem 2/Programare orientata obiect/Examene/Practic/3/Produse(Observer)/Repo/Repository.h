#pragma once

#include "../Domain/Produs.h"
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>

class RepoProdus {
private:
    vector<Produs> produse;
    string file_path;

    void load_from_file();
    void save_to_file();

public:
    RepoProdus(string fp) : file_path(move(fp)) { load_from_file(); }

    void adaugare(const Produs& p);

    vector<Produs> &getAll() { return produse; }
};