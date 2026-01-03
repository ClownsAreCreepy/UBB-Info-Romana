#include "Service.h"

void ServiceTractoare::sort_service() {
    ranges::sort(repo.getAll(), [](const Tractor &a, const Tractor &b) {
        return a.getDenumire() < b.getDenumire();
    });
}

void ServiceTractoare::adaugare_service(int id, const string &denumire, const string &tip, int nrRoti) {
    string erori;

    for (const Tractor &t: repo.getAll())
        if (t.getId() == id) {
            erori += "Id-ul trebuie sa fie unic!\n";
            break;
        }

    if (denumire.empty())
        erori += "Denumirea nu poate fi vida!\n";

    if (tip.empty())
        erori += "Tipul nu poate fi vid!\n";

    if (nrRoti % 2 == 1)
        erori += "Numarul de roti trebuie sa fie par!\n";

    if (nrRoti < 2 || nrRoti > 16)
        erori += "Numarul de roti trebuie sa fie intre 2 si 16!\n";

    if (!erori.empty())
        throw runtime_error(erori);

    Tractor t{id, denumire, tip, nrRoti};
    repo.adaugare(t);
    sort_service();
}

int ServiceTractoare::filtrare_tip(const string &tip) {
    int count = -1;
    for (const Tractor &t: repo.getAll())
        if (t.getTip() == tip)
            count ++;
    return count;
}

void ServiceTractoare::decrementare(int id) {
    repo.decrementare(id);
    sort_service();
}

const set<string> &ServiceTractoare::getTipuri(set<string> &filtrata) {
    filtrata.clear();
    for (const Tractor &t: repo.getAll())
        if (!filtrata.contains(t.getTip()))
            filtrata.emplace(t.getTip());

    return filtrata;
}

