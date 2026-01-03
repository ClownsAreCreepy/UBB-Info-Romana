#pragma once

#include "../Repo/Repository_PlacaDeBaza.h"

class ServicePlacaDeBaza {
private:
    RepoPlacaDeBaza &repo;

public:
    explicit ServicePlacaDeBaza(RepoPlacaDeBaza &placi) : repo(placi) {}

    void service_adauga_placi(const string &nume, const string &soclu, int pret) const;

    void filtrareSoclu(const string &soclu, vector<PlacaDeBaza> &rezultat);

    //Getteri
    [[nodiscard]] const vector<PlacaDeBaza> &getAllPlaci() const;
};