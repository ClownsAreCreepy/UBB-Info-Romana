#include "Repository.h"


void RepoRochii::load_from_file() {
    rochii.clear();
    ifstream in(file_path);
    if (!in.is_open())
        return;     // daca fisierul nu exista, incepem de la 0

    string line;
    while (getline(in, line)) {
        stringstream ss(line);
        int id = 0, pret;
        string denumire, marime, disponibil;

        ss >> id;
        ss.ignore(1);
        getline(ss, denumire, ',');
        getline(ss, marime, ',');
        ss >> pret;
        ss.ignore(1);
        getline(ss, disponibil, ',');

        if (id > 0) {
            Rochie r{id, denumire, marime, pret, disponibil};
            rochii.emplace_back(r);
        }
    }

    in.close();
}

void RepoRochii::save_to_file() const {
    ofstream out(file_path);
    for (const auto &r : rochii)
        out << r.getID() << "," << r.getDenumire() << "," << r.getMarime() << "," << r.getPret() << "," << r.getDisponibilitate() << '\n';
    out.close();
}



void RepoRochii::adauga(const Rochie &ro) {
    load_from_file();
    rochii.emplace_back(ro);
    save_to_file();
}

void RepoRochii::inchiriaza(int index, const Rochie &roc) {
    load_from_file();

    if (rochii[index].getDisponibilitate() == "False")
        throw runtime_error("Rochia este deja inchiriata");

    rochii[index] = roc;

    save_to_file();
}


const vector<Rochie> &RepoRochii::getAll() const {
    return rochii;
}
