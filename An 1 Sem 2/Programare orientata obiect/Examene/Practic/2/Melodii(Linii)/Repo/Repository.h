#pragma once

#include "../Domain/Melodii.h"
#include <vector>
#include <sstream>
#include <fstream>
#include <algorithm>

using std::vector;

class RepoMelodie {
private:
    vector<Melodie> melodii;
    string file_path;

    void load_from_file();
    void save_to_file();

public:
    explicit RepoMelodie(string file) : file_path(move(file)) { load_from_file(); }

    void adauga(const Melodie &m);
    void modifica(int id, const string &new_title,int new_rank);
    void sterge(int id);

    [[nodiscard]] vector<Melodie> &getAll() { return melodii; }

};