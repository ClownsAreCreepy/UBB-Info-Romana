#pragma once

#include "../Repo/Repository.h"
#include "../Observe/Observe.h"
#include <iostream>
#include <exception>

class ServiceProdus : public Observable{
private:
    RepoProdus &repo;

public:
    ServiceProdus(RepoProdus &repo) : repo(repo) {
        ranges::sort(repo.getAll(), [](const Produs &a, const Produs &b) {
            return a.getPret() < b.getPret();
        });
    }

    void adauga_service(int id, const string &nume, const string &tip, double pret);
    vector<int> filtrare_pret(double pret) const;
    int nr_vocale(const string &nume) const;

    const vector<Produs> &getAll() const { return repo.getAll(); }
};