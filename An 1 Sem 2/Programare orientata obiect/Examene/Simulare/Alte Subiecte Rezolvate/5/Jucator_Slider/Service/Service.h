#pragma once

#include "../Repo/Repository.h"
#include <algorithm>
#include <unordered_set>

class ServiceJucatori {
private:
    RepoJucatori &repo;

public:
    explicit ServiceJucatori(RepoJucatori &repo) : repo(repo) {}

    void adaugare_cu_rank(const string &nume, const string &tara, int puncte);

    const vector<Jucator> &getAll() const { return repo.getAll(); }

    const vector<string> &raportTara() const;

    const vector<Jucator> alegere_jucatori() const;
};