#include "Repository.h"

void RepoMelodii::load_from_file() {
    melodii.clear();
    ifstream in(file_path);
    if (!in.is_open()) return;  // o luam de la 0

    string line;
    while (getline(in, line)) {
        stringstream ss(line);
        int id = -1;
        string titlu, artist, gen;

        ss >> id;
        ss.ignore(1);
        getline(ss, titlu, ',');
        getline(ss, artist, ',');
        getline(ss, gen, ',');

        if (id != -1) {
            Melodie m{id, titlu, artist, gen};
            melodii.emplace_back(m);
        }
    }

    in.close();
}

void RepoMelodii::save_to_file() const {
    ofstream out(file_path);
    for (const auto &m: melodii)
        out << m.getId() << "," << m.getTitlu() << "," << m.getArtist() << "," << m.getGen() << '\n';

    out.close();
}

void RepoMelodii::adaugare(const Melodie &m) {
    load_from_file();
    melodii.emplace_back(m);
    save_to_file();
}

void RepoMelodii::stergere(int idx) {
    load_from_file();
    melodii.erase(melodii.begin() + idx);
    save_to_file();
}
