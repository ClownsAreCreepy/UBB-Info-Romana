#include "Repository_PlacaDeBaza.h"

void RepoPlacaDeBaza::load_from_file() {
    placi.clear();
    ifstream in(file_path);
    if (!in.is_open()) return;

    string line;
    while (getline(in, line)) {
        stringstream ss(line);
        string nume, soclu;
        int pret;

        getline(ss, nume, ',');
        getline(ss, soclu, ',');
        ss >> pret;

        if (!nume.empty()) {
            PlacaDeBaza p{nume, soclu, pret};
            placi.emplace_back(p);
        }
    }

    in.close();
}

void RepoPlacaDeBaza::adauga_placi(const PlacaDeBaza &p) {
    placi.emplace_back(p);
}

