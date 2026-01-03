#pragma once

#include "../Domain/PlacaDeBaza.h"
#include <vector>
#include <fstream>
#include <sstream>

class RepoPlacaDeBaza {
private:
    vector<PlacaDeBaza> placi;
    string file_path;

    void load_from_file();

public:
    explicit RepoPlacaDeBaza(string file) : file_path{move(file)} {
        load_from_file();
    }

    void adauga_placi(const PlacaDeBaza &p);

    //Getteri
    [[nodiscard]] const vector<PlacaDeBaza> &getAllPlaci() const { return placi; }
};
