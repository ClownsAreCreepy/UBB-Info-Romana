#include "Test.h"

void Teste::test_adaugare() {
    char temp[L_tmpnam];
    tmpnam(temp);

    RepoJucatori repo(temp);

    repo.getAll().push_back({"Mimi", "Mumu", 150, 1});
    repo.getAll().push_back({"Mimi", "Mumu", 140, 2});
    repo.getAll().push_back({"Mimi", "Mumu", 130, 3});
    repo.getAll().push_back({"Mimi", "Mumu", 120, 4});
    repo.getAll().push_back({"Mimi", "Mumu", 100, 5});

    ServiceJucatori service(repo);

    const auto &all =service.getAll();

    assert(all.size() == 5);

    service.adaugare_cu_rank("Mimi", "Mumu", 135);
    service.adaugare_cu_rank("Mimi", "Mumu", 136);
    service.adaugare_cu_rank("Mimi", "Mumu", 123);
    service.adaugare_cu_rank("Mimi", "Mumu", 170);
    service.adaugare_cu_rank("Mimi", "Mumu", 92);

    for (int i = 1; i < all.size(); ++i) {
        const Jucator j_trecut = all[i-1];
        const Jucator j_curent = all[i];
        assert(j_trecut.getPuncte() > j_curent.getPuncte());
        assert(j_curent.getRank() == i + 1);
        assert(j_trecut.getRank() == i);
    }

    remove(temp);
}

void Teste::test_raport() {
    char temp[L_tmpnam];
    tmpnam(temp);

    RepoJucatori repo(temp);

    repo.getAll().push_back({"Mimi", "Damn", 150, 1});
    repo.getAll().push_back({"Mama", "Papa", 140, 2});
    repo.getAll().push_back({"Pupu", "Papa", 130, 3});
    repo.getAll().push_back({"Lmao", "Lol", 120, 4});
    repo.getAll().push_back({"idk", "Damn", 100, 5});

    ServiceJucatori service(repo);

    const auto tipuri = service.raportTara();
    const vector<string> solutie = {"Lol", "Papa", "Damn"};
    assert(tipuri == solutie);

    remove(temp);
}

void Teste::test_alegere() {
    char temp[L_tmpnam];
    tmpnam(temp);

    RepoJucatori repo(temp);

    repo.getAll().push_back({"Mimi", "Damn", 150, 1});
    repo.getAll().push_back({"Mama", "Papa", 140, 2});
    repo.getAll().push_back({"Pupu", "Papa", 130, 3});
    repo.getAll().push_back({"Lmao", "Lol", 120, 4});
    repo.getAll().push_back({"idk", "Damn", 100, 5});

    ServiceJucatori service(repo);

    const auto &all =service.getAll();

    const auto jucatori = service.alegere_jucatori();
    assert(jucatori.size() == 2);

    auto it1 = std::ranges::find_if(all, [&](const Jucator &j) {
        return j.getNume() == jucatori[0].getNume();
    });

    auto it2 = std::ranges::find_if(all, [&](const Jucator &j) {
        return j.getNume() == jucatori[1].getNume();
    });

    assert(it1 != all.end());
    assert(it2 != all.end());
    remove(temp);
}

void Teste::test_all() {
    test_adaugare();
    test_raport();
    test_alegere();
}
