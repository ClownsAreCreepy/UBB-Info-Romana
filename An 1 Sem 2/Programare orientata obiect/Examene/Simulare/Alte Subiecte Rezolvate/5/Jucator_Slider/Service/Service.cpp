#include "Service.h"

void ServiceJucatori::adaugare_cu_rank(const string &nume, const string &tara, int puncte) {
    auto &all = repo.getAll();

    int insert_index = 0;
    while (insert_index < all.size() && all[insert_index].getPuncte() > puncte)
        insert_index ++;

    int new_rank = insert_index + 1;
    Jucator nou(nume, tara, puncte, new_rank);

    all.insert(all.begin() + insert_index, nou);

    for (int i = insert_index + 1; i < all.size(); ++i)
        all[i].setRank(i+1);
}

const vector<string> &ServiceJucatori::raportTara() const {
    static vector<string> tari_unice;
    tari_unice.clear();

    unordered_set<string> tari_set;
    for (const auto &j: repo.getAll())
        tari_set.insert(j.getTara());

    for (const auto &tara : tari_set)
        tari_unice.push_back(tara);

    return tari_unice;
}

const vector<Jucator> ServiceJucatori::alegere_jucatori() const {
    const auto &all = repo.getAll();
    vector<Jucator> rezultat;

    int i1 = rand() % all.size();
    int i2;
    do {
        i2 = rand() % all.size();
    } while (i2 == i1);

    rezultat.push_back(all[i1]);
    rezultat.push_back(all[i2]);

    return rezultat;
}
