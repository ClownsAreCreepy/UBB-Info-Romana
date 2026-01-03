#include "Repository.h"

void RepoJoc::load_from_file() {
    jocuri.clear();
    ifstream in(file_path);
    if (!in.is_open()) return;      // daca e gol o luam de la capat

    string line;
    while (getline(in, line)) {
        stringstream ss(line);
        int id = -1, dim;
        string tabla, jucator, stare;

        ss >> id;
        ss.ignore(1);
        ss >> dim;
        ss.ignore(1);
        getline(ss, tabla, ' ');
        getline(ss, jucator, ' ');
        getline(ss, stare);

        if (id != -1) {
            const Joc j {id, dim, tabla, jucator, stare};
            jocuri.emplace_back(j);
        }
    }

    in.close();
}

void RepoJoc::save_to_file() {
    ofstream out(file_path);
    for (const Joc &j : jocuri)
        out << j.getId() << ' ' << j.getDimensiune() << ' ' << j.getTabla() << ' ' << j.getJucator() << ' ' << j.getStare() << '\n';

    out.close();
}

void RepoJoc::adauga(const Joc &j) {
    load_from_file();
    jocuri.emplace_back(j);
    save_to_file();
}

void RepoJoc::modifica(const Joc &joc) {
    load_from_file();
    for (Joc &j : jocuri)
        if (j.getId() == joc.getId()) {
            j.setDimensiune(joc.getDimensiune());
            j.setTabla(joc.getTabla());
            j.setJucator(joc.getJucator());
            j.setStare(joc.getStare());
        }
    save_to_file();
}
