#pragma once

#include "../Repo/Repository.h"
#include <exception>

class ServiceMelodii {
private:
    RepoMelodie &repo;

public:
    explicit ServiceMelodii(RepoMelodie &repo) : repo(repo) {
        ranges::sort(repo.getAll(), [](const Melodie &a, const Melodie &b) {
            return a.getRank() < b.getRank();
        });
    }

    void modifica_service(int id, const string &new_title, int new_rank) const;
    void sterge_service(int id, const string &artist) const;
    int melodii_cu_acelasi_rank(const Melodie &m) const;

    const vector<Melodie> &getAll() const { return repo.getAll(); }
};