#pragma once

#include "../Repo/Repository.h"
#include <algorithm>

class ServiceRochii {
private:
    RepoRochii &repo;

public:

    //Constructor explicit
    explicit ServiceRochii(RepoRochii &repo) : repo{repo} {}

    //Functia adauga o rochie in lista
    void adauga_service(int id, const string &denumire, const string &marime, int pret, const string &disponibil) const;

    void inchirieaza_service(int id) const;

    [[nodiscard]] const vector<Rochie> &getAll() const;

    void sorteaza_denumire(vector<Rochie> &out) const;
    void sorteaza_pret(vector<Rochie> &out) const;
};