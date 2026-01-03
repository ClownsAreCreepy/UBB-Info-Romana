#include "Repository_Procesor.h"

void RepoProcesor::load_from_file() {
    procesoare.clear();
    ifstream in(file_path);
    if (!in.is_open()) return; // daca fisierul nu exista, incepem de la 0

    string line;
    while (getline(in, line)) {
        stringstream ss(line);
        string nume, soclu;
        int threads, pret;

        getline(ss, nume, ',');
        ss >> threads;
        ss.ignore(1);
        getline(ss, soclu, ',');
        ss >> pret;

        if (!nume.empty()) {
            Procesor p{nume, threads, soclu, pret};
            procesoare.emplace_back(p);
        }
    }

    in.close();
}

void RepoProcesor::adauga_procesoare(const Procesor &p) {
    procesoare.emplace_back(p);
}
