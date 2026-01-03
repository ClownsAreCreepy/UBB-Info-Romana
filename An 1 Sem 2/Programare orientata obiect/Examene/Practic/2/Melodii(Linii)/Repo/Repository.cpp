#include "Repository.h"

void RepoMelodie::load_from_file() {
    melodii.clear();
    ifstream in(file_path);
    if (!in.is_open()) return; // daca fisierul nu exista, o luam de la 0

    string line;
    while (getline(in, line)) {
        stringstream ss(line);
        string titlu, artist;
        int id=-1, rank;

        ss >> id;
        ss.ignore(1); // ignoram virgula
        getline(ss, titlu, ',');
        getline(ss, artist, ',');
        ss >> rank;

        if (id != -1) {
            Melodie m{id, titlu, artist, rank};
            melodii.emplace_back(m);
        }
    }

    in.close();
}

void RepoMelodie::save_to_file() {
    ofstream out(file_path);
    for (const auto &m: melodii)
        out << m.getId() << "," << m.getTitlu() << "," << m.getArtist() << "," << m.getRank() << '\n';
    out.close();
}

void RepoMelodie::adauga(const Melodie &m) {
    load_from_file();
    melodii.emplace_back(m);
    save_to_file();
}

void RepoMelodie::modifica(int id, const string &new_title, int new_rank) {
    load_from_file();
    for (Melodie &m : melodii)
        if (m.getId() == id) {
            m.setRank(new_rank);
            m.setTitlu(new_title);
            break;
        }
    save_to_file();
}

void RepoMelodie::sterge(int id) {
    load_from_file();
    auto new_end = remove_if(melodii.begin(), melodii.end(), [&id](const Melodie& m) {
        return m.getId() == id;
    });
    melodii.erase(new_end, melodii.end());
    save_to_file();
}
