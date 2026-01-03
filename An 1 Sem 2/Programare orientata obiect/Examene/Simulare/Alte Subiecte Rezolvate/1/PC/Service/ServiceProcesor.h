#pragma once

#include "../Repo/Repository_Procesor.h"

class ServiceProcesor {
private:
    RepoProcesor &repo;

public:
    explicit ServiceProcesor(RepoProcesor &procesoare) : repo(procesoare) {}

    void service_adauga_procesoare(const string &nume, int threaduri, const string &soclu, int pret) const;

    //Getteri
    [[nodiscard]] const vector<Procesor> &getAllProcesoare() const;
};