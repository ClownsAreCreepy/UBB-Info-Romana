#include "Service.h"

void ServiceRochii::adauga_service(int id, const string &denumire, const string &marime, int pret, const string &disponibil) const {
    const Rochie r{id, denumire, marime, pret, disponibil};
    repo.adauga(r);
}

void ServiceRochii::inchirieaza_service(int id) const {
    const Rochie roc = repo.getAll()[id];
    const Rochie roc_indisp {roc.getID(), roc.getDenumire(), roc.getMarime(), roc.getPret(), "False"};
    repo.inchiriaza(id, roc_indisp);
}

const vector<Rochie> &ServiceRochii::getAll() const {
    return repo.getAll();
}

void ServiceRochii::sorteaza_denumire(vector<Rochie> &out) const {
    out = repo.getAll();
    std::ranges::sort(out, [](const Rochie &a, const Rochie &b) {
       return a.getDenumire() < b.getDenumire();
    });
}

void ServiceRochii::sorteaza_pret(vector<Rochie> &out) const {
    out = repo.getAll();
    std::ranges::sort(out, [](const Rochie &a, const Rochie &b) {
       return a.getPret() < b.getPret();
    });
}
