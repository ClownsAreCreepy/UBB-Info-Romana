#pragma once

#include "../Repo/Repository.h"
#include <iostream>
#include <exception>
#include <algorithm>
#include <set>

class ServiceJoc {
private:
    RepoJoc &repo;
    set<string> stari;

    void sort_service();

public:
    ServiceJoc(RepoJoc &r) : repo(r) {
        sort_service();
        stari = {"Neinceput", "In derulare", "Terminat"};
    }

    void adauga_service(int dimensiune, const string &tabla, const string &jucator);
    void modifica_service(int id, int dimensiune_noua, const string &tabla_noua, const string &jucator_nou, const string &stare_noua);

    const vector<Joc> &getAll() const { return repo.getAll(); }
    const set<string> &getStari() const { return stari; }
};