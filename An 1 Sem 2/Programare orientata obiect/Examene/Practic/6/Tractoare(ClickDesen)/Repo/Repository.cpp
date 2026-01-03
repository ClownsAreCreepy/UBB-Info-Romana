#include "Repository.h"

void RepoTractoare::load_from_file() {
    tractoare.clear();
    ifstream in(file_path);
    if (!in.is_open()) return;      // daca nu exista o luam de la 0

    string line;
    while (getline(in, line)) {
        stringstream ss(line);
        int id = -1, nrRoti;
        string denumire, tip;

        ss >> id;
        ss.ignore(1);
        getline(ss, denumire, ',');
        getline(ss, tip, ',');
        ss >> nrRoti;

        if (id != -1) {
            Tractor t{id, denumire, tip, nrRoti};
            tractoare.emplace_back(t);
        }
    }

    in.close();
}

void RepoTractoare::save_to_file() {
    ofstream out(file_path);
    for (const Tractor &t : tractoare)
        out << t.getId() << ',' << t.getDenumire() << ',' << t.getTip() << ',' << t.getRoti() << '\n';

    out.close();
}

void RepoTractoare::adaugare(const Tractor &t) {
    load_from_file();
    tractoare.emplace_back(t);
    save_to_file();
}

void RepoTractoare::decrementare(int id) {
    load_from_file();
    for (Tractor &t: tractoare)
        if (t.getId() == id) {
            t.decRoti();
            break;
        }
    save_to_file();
}
