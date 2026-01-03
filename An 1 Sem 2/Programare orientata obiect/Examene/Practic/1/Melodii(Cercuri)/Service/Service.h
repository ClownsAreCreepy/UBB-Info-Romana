#pragma once

#include "../Repo/Repository.h"
#include <iostream>

class ServiceMelodii {
private:
    RepoMelodii &repo;

public:
    explicit ServiceMelodii(RepoMelodii &r) : repo(r) {}

    void adauga_service(const string &titlu, const string &artist, const string &gen);
    void stergere_service(int idx);

    int melodii_cu_acelasi_autor(const string &artist) const;
    int melodii_cu_acelasi_gen(const string &gen) const;

    const vector<Melodie> &getAll() const { return repo.getAll(); }
};