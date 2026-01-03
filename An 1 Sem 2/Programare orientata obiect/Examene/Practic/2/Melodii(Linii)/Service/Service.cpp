#include "Service.h"

#include <bits/ranges_algo.h>

void ServiceMelodii::modifica_service(int id, const string &new_title, int new_rank) const {
    repo.modifica(id, new_title, new_rank);
    ranges::sort(repo.getAll(), [](const Melodie &a, const Melodie &b) {
        return a.getRank() < b.getRank();
    });
}

void ServiceMelodii::sterge_service(int id, const string &artist) const {
    bool exista = false;
    const vector<Melodie> &all = repo.getAll();
    for (int i = 0; i < all.size(); ++i)
        if (all[i].getArtist() == artist && all[i].getId() != id)
            exista = true;

    if (!exista)
        throw runtime_error("Melodia este ultima melodie a artistului! Nu se va sterge din bun simt!");

    repo.sterge(id);

    ranges::sort(repo.getAll(), [](const Melodie &a, const Melodie &b) {
        return a.getRank() < b.getRank();
    });
}

int ServiceMelodii::melodii_cu_acelasi_rank(const Melodie &m) const {
    int count=0;

    for (const Melodie &melodie : repo.getAll())
        if (melodie.getRank() == m.getRank())
            count ++;

    return count - 1;
}
