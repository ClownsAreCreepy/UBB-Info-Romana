#include "Service.h"

void ServiceJucatori::adauga_service(const string &nume, const string &tara, int puncte, int rank) const {
    const Jucator j{nume, tara, puncte, rank};
    repo.adauga(j);
}

void ServiceJucatori::adauga_puncte(const string &nume_jucator, int puncte) const {
    if (puncte < 0)
        throw runtime_error("Punctele nu pot fi negative!");

    for (auto &j: repo.getAll())
        if (j.getNume() == nume_jucator) {
            j.setPuncte(j.getPuncte() + puncte);
            return;
        }

    throw runtime_error("Jucatorul pe care il doriti nu exista!");
}


void ServiceJucatori::recalculare() const {
    std::ranges::sort(repo.getAll(), [](const Jucator &a, const Jucator &b) {
       return a.getPuncte() > b.getPuncte();
    });

    for (int i = 1; i <= repo.getAll().size(); ++i)
        repo.getAll()[i-1].setRank(i);
}

void ServiceJucatori::sterge_service(int m) const {
    if (m * 2 > repo.getAll().size())
        throw runtime_error("Nu puteti sa eliminati mai mult de jumate de jucatori!");

    repo.sterge(m);
}
