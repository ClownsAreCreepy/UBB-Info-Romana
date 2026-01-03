#pragma once

#include "../Repo/Repository.h"
#include <random>
#include <algorithm>
#include <exception>

class ServiceJucatori {
private:
    RepoJucatori &repo;

public:
    explicit ServiceJucatori(RepoJucatori &repo) : repo(repo) {
    }

    void adaugare_cu_ranc(string nume, string tara, int ranc);

    void sortare_ranc();

    const vector<Jucator> &getAll() const { return repo.getAll(); }
};
