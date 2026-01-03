#include "Repository.h"

void RepoProdus::load_from_file() {
    produse.clear();
    ifstream in(file_path);
    if (!in.is_open()) return;      // daca e gol incepem de la 0

    string line;
    while (getline(in, line)) {
        stringstream ss(line);
        int id = -1;
        double pret;
        string nume, tip;

        ss >> id;
        ss.ignore(1);
        getline(ss, nume, ',');
        getline(ss, tip, ',');
        ss >> pret;

        if (id != -1) {
            const Produs p{id, nume, tip, pret};
            produse.emplace_back(p);
        }
    }

    in.close();
}

void RepoProdus::save_to_file() {
    ofstream out(file_path);
    for (const auto &p : produse)
        out << p.getId() << "," << p.getNume() << "," << p.getTip() << "," << p.getPret() << "\n";

    out.close();
}

void RepoProdus::adaugare(const Produs &p) {
    load_from_file();
    produse.emplace_back(p);
    save_to_file();
}
