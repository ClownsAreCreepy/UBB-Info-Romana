#pragma once

#include "../Domain/Joc.h"
#include <vector>
#include <fstream>
#include <sstream>

class RepoJoc {
private:
    vector<Joc> jocuri;
    string file_path;

    void load_from_file();
    void save_to_file();

public:
    RepoJoc(string fp) : file_path(move(fp)) { load_from_file(); }

    void adauga(const Joc &j);
    void modifica(const Joc &joc);

    vector<Joc> &getAll() { return jocuri; }
};