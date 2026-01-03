#include "Service.h"

void ServiceProdus::adauga_service(int id, const string &nume, const string &tip, double pret) {
    string erori;

    for (const Produs &m: repo.getAll())
        if (m.getId() == id) {
            erori += "Id-ul deja exista!\n";
            break;
        }

    if (nume.empty())
        erori += "Numele nu poate fi gol!\n";

    if (pret < 1.0 || pret > 100.0)
        erori += "Pretul trebuie sa fie intre 1 si 100!\n";

    if (!erori.empty())
        throw runtime_error(erori);

    const Produs p{id, nume, tip, pret};
    repo.adaugare(p);

    ranges::sort(repo.getAll(), [](const Produs &a, const Produs &b) {
            return a.getPret() < b.getPret();
        });

    notify_all();
}

vector<int> ServiceProdus::filtrare_pret(double pret) const{
    vector<int> result;

    for (const Produs &m: repo.getAll())
        if (m.getPret() < pret)
            result.push_back(m.getId());

    return result;
}

int ServiceProdus::nr_vocale(const string &nume) const {
    int count = 0;
    for (char c: nume) {
        char lower = tolower(c);
        if (lower == 'a' || lower == 'e' || lower == 'i' || lower == 'o' || lower == 'u')
            count ++;
    }

    return count;
}
