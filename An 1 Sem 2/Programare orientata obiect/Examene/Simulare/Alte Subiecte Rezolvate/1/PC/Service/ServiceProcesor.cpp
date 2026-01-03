#include "ServiceProcesor.h"

void ServiceProcesor::service_adauga_procesoare(const string &nume, int threaduri, const string &soclu, int pret) const {
    Procesor p{nume, threaduri, soclu, pret};
    repo.adauga_procesoare(p);
}

const vector<Procesor> &ServiceProcesor::getAllProcesoare() const {
    return repo.getAllProcesoare();
}