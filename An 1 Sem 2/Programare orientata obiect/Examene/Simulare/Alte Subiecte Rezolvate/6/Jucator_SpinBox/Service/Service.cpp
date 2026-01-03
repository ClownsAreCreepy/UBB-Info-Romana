#include "Service.h"
#include <iostream>

void ServiceJucatori::adaugare_cu_ranc(string nume, string tara, int ranc) {
    auto &jucatori = repo.getAll();

    vector<Jucator> lista = jucatori;
    std::ranges::sort(lista, [](const Jucator &a, const Jucator &b) {
        return a.getRank() < b.getRank();
    });

    int maxScor = lista.front().getPuncte();
    int minScor = lista.back().getPuncte();
    int scor_nou = 0;

    if (ranc < lista.front().getRank()) {
        scor_nou = maxScor + 1 + (rand() % (4999 - maxScor));
        Jucator j {nume, tara, scor_nou, ranc};
        repo.adauga(j);
        return;
    }
    if (ranc > lista.back().getRank()) {
        int interval = max(1, minScor - 10);
        scor_nou = 10 + (rand() % interval);
        Jucator j {nume, tara, scor_nou, ranc};
        repo.adauga(j);
        return;
    }
    for (int i = 0; i < lista.size() - 1; ++i)
        if (lista[i].getRank() < ranc && ranc < lista[i + 1].getRank()) {
            int minP = lista[i+1].getPuncte();
            int maxP = lista[i].getPuncte();
            scor_nou = minP + rand() % (maxP - minP);
            Jucator j {nume, tara, scor_nou, ranc};
            repo.adauga(j);
            return;
        }

    throw runtime_error("Rancul exista deja!");
}

void ServiceJucatori::sortare_ranc() {
    std::ranges::sort(repo.getAll(), [](const Jucator &a, const Jucator &b) {
        return a.getRank() < b.getRank();
    });
}
