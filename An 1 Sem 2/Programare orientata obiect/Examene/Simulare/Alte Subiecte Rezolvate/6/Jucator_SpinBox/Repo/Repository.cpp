#include "Repository.h"

void RepoJucatori::load_from_file() {
    jucatori.clear();
    ifstream in(file_path);
    if (!in.is_open()) return;

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
            const Jucator j{nume, tara, puncte, rank};
            jucatori.emplace_back(j);
        }
    }

    in.close();
}

void RepoJucatori::adauga(const Jucator &j) {
    jucatori.push_back(j);
}
