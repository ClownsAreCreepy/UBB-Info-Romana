#include "Service.h"

void ServiceJoc::sort_service() {
    ranges::sort(repo.getAll(), [](const Joc &a, const Joc &b) {
        return a.getStare() < b.getStare();
    });
}

void ServiceJoc::adauga_service(int dimensiune, const string &tabla, const string &jucator) {
    bool gasit = false;
    int id = 0;
    while (!gasit) {
        gasit = true;
        ++id;
        for (const auto &m : repo.getAll())
            if (id == m.getId()) {
                gasit = false;
                break;
            }
    }
    const Joc j{id, dimensiune, tabla, jucator, "Neinceput"};
    repo.adauga(j);
    sort_service();
}

void ServiceJoc::modifica_service(int id_joc_modificat, int dimensiune_noua, const string &tabla_noua, const string &jucator_nou, const string &stare_noua) {
    string erori;

    if (dimensiune_noua < 3 || dimensiune_noua > 5)
        erori += "Dimensiunea poate fi 3, 4 sau 5!\n";

    if (tabla_noua.size() != dimensiune_noua * dimensiune_noua)
        erori += "Tabla trebuie sa contina (dimensiune)^2 caractere!\n";

    for (const char &c : tabla_noua)
        if (c != 'X' && c != 'O' && c != '-') {
            erori += "Tabla contine doar caracterele X, O sau -!\n";
            break;
        }

    if (jucator_nou != "O" && jucator_nou != "X")
        erori += "Jucatorul poate fi doar X sau O!\n";

    if (!stari.contains(stare_noua))
        erori += "Starea poate fi doar Neinceput, In derulare sau Terminat!\n";

    if (!erori.empty())
        throw runtime_error(erori);

    const Joc j{id_joc_modificat, dimensiune_noua, tabla_noua, jucator_nou, stare_noua};
    repo.modifica(j);
    sort_service();
}
