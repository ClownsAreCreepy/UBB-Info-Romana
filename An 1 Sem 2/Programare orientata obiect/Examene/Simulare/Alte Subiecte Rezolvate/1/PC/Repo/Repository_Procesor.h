#pragma once

#include "../Domain/Procesor.h"
#include <vector>
#include <fstream>
#include <sstream>

class RepoProcesor {
private:
    vector<Procesor> procesoare;
    string file_path;

    void load_from_file();

public:
    explicit RepoProcesor(string file) : file_path{move(file)} {
        load_from_file();
    }

    void adauga_procesoare(const Procesor &p);

    //Getteri
    [[nodiscard]] const vector<Procesor> &getAllProcesoare() const { return procesoare; }
};
