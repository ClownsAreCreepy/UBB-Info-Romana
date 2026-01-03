#pragma once

#include "../Repo/Repository.h"
#include <algorithm>
#include <exception>


class ServiceJucatori {
private:
    RepoJucator &repo;

public:
    explicit ServiceJucatori(RepoJucator &repo) : repo(repo) {}

    void adauga_service(const string &nume, const string &tara, int puncte, int rank) const;
    void adauga_puncte(const string &jucator, int puncte) const;
    void sterge_service(int m) const;
    void recalculare() const;

    vector<Jucator> getAll() const {return repo.getAll(); }
};