#include "repository_file_discipline.h"

void RepoDisciplinaFile::load_from_file() {
    discipline.clear();
    ifstream in(file_path);
    if (!in.is_open()) return; // daca fisierul nu exista, incepem de la 0

    string line;
    while (getline(in, line)) {
        std::stringstream ss(line);
        string nume, tip, profesor;
        int ore;

        getline(ss, nume, ',');
        ss >> ore;
        ss.ignore(1); //ignoram virgula
        getline(ss, tip, ',');
        getline(ss, profesor);

        if (!nume.empty()) {
            Disciplina d{nume, ore, tip, profesor};
            discipline.emplace_back(d);
        }
    }
    in.close();
}

void RepoDisciplinaFile::save_to_file() const {
    ofstream out(file_path);
    for (const auto &d: discipline)
        out << d.getNume() << "," << d.getOre() << "," << d.getTip() << "," << d.getProfesor() << "\n";
    out.close();
}


void RepoDisciplinaFile::adauga(const Disciplina &dis) {
    load_from_file();
    RepoDisciplinaMem::adauga(dis);
    save_to_file();
}

void RepoDisciplinaFile::modifica(size_t index, const Disciplina &ot) {
    load_from_file();
    RepoDisciplinaMem::modifica(index, ot);
    save_to_file();
}

void RepoDisciplinaFile::sterge(int index) {
    load_from_file();
    RepoDisciplinaMem::sterge(index);
    save_to_file();
}

void RepoDisciplinaFile::inserare_la_index(size_t index, const Disciplina &d) {
    RepoDisciplinaMem::inserare_la_index(index, d);
    save_to_file();
}

