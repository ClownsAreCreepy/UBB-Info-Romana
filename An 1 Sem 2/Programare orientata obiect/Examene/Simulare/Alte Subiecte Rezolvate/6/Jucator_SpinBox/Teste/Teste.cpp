#include "Teste.h"

void Teste::test_adaugare() {
    char temp[L_tmpnam];
    tmpnam(temp);

    RepoJucatori repo(temp);
    ServiceJucatori service(repo);

    auto &jucatori = repo.getAll();

    jucatori.emplace_back("Damn", "UUh", 1000, 4);
    jucatori.emplace_back("Zamn", "idk", 500, 7);
    jucatori.emplace_back("Bam", "ce ii aia", 700, 6);
    jucatori.emplace_back("Mimi", "Asa", 150, 10);
    jucatori.emplace_back("Cucu", "Damn", 900, 5);

    assert(service.getAll().size() == 5);

    service.adaugare_cu_ranc("Caca", "Pipi", 3);
    assert(jucatori.back().getPuncte() > 1000);

    service.adaugare_cu_ranc("Caca", "Pipi", 8);
    assert(jucatori.back().getPuncte() > 150 && jucatori.back().getPuncte() < 500);

    service.adaugare_cu_ranc("Caca", "Pipi", 11);
    assert(jucatori.back().getPuncte() < 150);

    try {
        service.adaugare_cu_ranc("Caca", "Pipi", 3);
        assert(false);
    } catch (const exception &e) {
        assert(string(e.what()) == "Rancul exista deja!");
    }

    remove(temp);
}

void Teste::test_sortare() {
    char temp[L_tmpnam];
    tmpnam(temp);

    RepoJucatori repo(temp);
    ServiceJucatori service(repo);

    auto &jucatori = repo.getAll();

    jucatori.emplace_back("Damn", "UUh", 1000, 4);
    jucatori.emplace_back("Zamn", "idk", 500, 7);
    jucatori.emplace_back("Bam", "ce ii aia", 700, 6);
    jucatori.emplace_back("Mimi", "Asa", 150, 10);
    jucatori.emplace_back("Cucu", "Damn", 900, 5);
    service.adaugare_cu_ranc("Caca", "Pipi", 3);
    service.adaugare_cu_ranc("Caca", "Pipi", 8);
    service.adaugare_cu_ranc("Caca", "Pipi", 11);

    service.sortare_ranc();

    for (int i = 1; i < jucatori.size(); ++i) {
        assert(jucatori[i-1].getRank() < jucatori[i].getRank());
        assert(jucatori[i-1].getPuncte() > jucatori[i].getPuncte());
    }

    remove(temp);
}

void Teste::test_all() {
    test_adaugare();
    test_sortare();
}
