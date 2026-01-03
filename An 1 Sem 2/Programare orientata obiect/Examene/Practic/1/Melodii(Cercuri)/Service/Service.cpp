#include "Service.h"

void ServiceMelodii::adauga_service(const string &titlu, const string &artist, const string &gen) {
    bool gasit = false;
    int id = 0;
    while (!gasit) {
        gasit = true;
        id++;
        for (const auto &m : repo.getAll())
            if (id == m.getId()) {
                gasit = false;
                break;
            }
    }

    const Melodie m{id, titlu, artist, gen};
    repo.adaugare(m);
}

void ServiceMelodii::stergere_service(int idx) {
    repo.stergere(idx);
}

int ServiceMelodii::melodii_cu_acelasi_autor(const string &artist) const {
    int count = -1;
    for (const auto &m : repo.getAll())
        if (m.getArtist() == artist)
            count ++;
    return count;
}

int ServiceMelodii::melodii_cu_acelasi_gen(const string &gen) const {
    return static_cast<int>(ranges::count_if(repo.getAll(), [&gen](const Melodie &m) {
        return m.getGen() == gen;
    })) - 1;
}
