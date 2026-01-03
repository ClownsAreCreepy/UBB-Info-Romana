#pragma once

#include "../Repo/Repository.h"
#include <algorithm>
#include <iostream>
#include <exception>
#include <set>

class ServiceTractoare {
private:
    RepoTractoare &repo;

    void sort_service();

public:
    ServiceTractoare(RepoTractoare &r) : repo(r) { sort_service(); }

    void adaugare_service(int id, const string &denumire, const string &tip, int nrRoti);
    int filtrare_tip(const string &tip);
    void decrementare(int id);

    const vector<Tractor> &getAll() const { return repo.getAll(); }
    const set<string> &getTipuri(set<string> &filtrata);
};