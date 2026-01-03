#include "ServicePlacaDeBaza.h"

void ServicePlacaDeBaza::service_adauga_placi(const string &nume, const string &soclu, int pret) const {
    PlacaDeBaza p{nume, soclu, pret};
    repo.adauga_placi(p);
}

const vector<PlacaDeBaza> &ServicePlacaDeBaza::getAllPlaci() const {
    return repo.getAllPlaci();
}

void ServicePlacaDeBaza::filtrareSoclu(const string &soclu, vector<PlacaDeBaza> &rezultat) {
    rezultat.clear();
    for (const auto &p : repo.getAllPlaci())
        if (p.getSocluProcesor() == soclu)
            rezultat.emplace_back(p);
}
