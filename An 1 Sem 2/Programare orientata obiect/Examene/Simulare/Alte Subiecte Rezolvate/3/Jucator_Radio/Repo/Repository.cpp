#include "Repository.h"

void RepoJucator::load_from_file() {
    jucatori.clear();
    ifstream in(file_path);
    if (!in.is_open()) return;      //daca e gol incepem de la 0

    string line;
    while (getline(in, line)) {
        stringstream ss(line);

        string nume, tara;
        int puncte, rank;

        getline(ss, nume, ',');
        getline(ss, tara, ',');
        ss >> puncte;
        ss.ignore(1);
        ss >> rank;
        ss.ignore(1);

        if (!nume.empty()) {
            Jucator j{nume,tara,puncte, rank};
            jucatori.emplace_back(j);
        }
    }

    in.close();
}

void RepoJucator::adauga(const Jucator &j) {
    jucatori.emplace_back(j);
}

void RepoJucator::sterge(int m) {
    for (int i = 0; i < m; ++i)
        jucatori.pop_back();
}