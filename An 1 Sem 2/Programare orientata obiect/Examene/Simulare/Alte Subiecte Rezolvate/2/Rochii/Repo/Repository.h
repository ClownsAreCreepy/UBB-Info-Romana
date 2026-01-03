#pragma once

#include "../Domain/rochii.h"
#include <utility>
#include <vector>
#include <fstream>
#include <sstream>
#include <exception>

class RepoRochii {
private:
    vector<Rochie> rochii;
    string file_path;

    //Functia incarca din fisier rochiile in repository
    void load_from_file();

    //Functie scrie intr-un fisier
    void save_to_file() const;

public:
    explicit RepoRochii(string file) : file_path(move(file)) { load_from_file(); }

    void adauga(const Rochie &ro);
    void inchiriaza(int index, const Rochie &roc);

    [[nodiscard]] const vector<Rochie> &getAll() const;
};