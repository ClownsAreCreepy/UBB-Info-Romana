#include "Test.h"

void Teste::test_fisier() {
    RepoMelodii repo(R"(D:\C,C++\CLion 2024.3.4\Projects\Examene\Practic\Practice\Melodii(Cercuri)\fisier_permanent.txt)");
    ServiceMelodii service(repo);
    assert(service.getAll().size() == 10);
    assert(service.getAll()[5].getTitlu() == "Mirrors");
}

void Teste::test_adaugare() {
    char temp[L_tmpnam];
    tmpnam(temp);

    RepoMelodii repo(temp);
    ServiceMelodii service(repo);

    assert(service.getAll().empty());
    service.adauga_service("A", "AA", "rock");
    service.adauga_service("B", "BB", "rock");
    service.adauga_service("C", "CC", "folk");
    service.adauga_service("D", "DD", "pop");
    assert(service.getAll().size() == 4);
    assert(service.getAll()[0].getTitlu() == "A");
    assert(service.getAll()[2].getArtist() == "CC");

    remove(temp);
}

void Teste::test_stergere() {
    char temp[L_tmpnam];
    tmpnam(temp);

    RepoMelodii repo(temp);
    ServiceMelodii service(repo);

    service.adauga_service("A", "AA", "rock");
    service.adauga_service("B", "BB", "rock");
    service.adauga_service("C", "CC", "folk");
    service.adauga_service("D", "DD", "pop");

    service.stergere_service(0);
    assert(service.getAll()[0].getTitlu() == "B");

    service.stergere_service(1);
    assert(service.getAll()[1].getTitlu() == "D");

    assert(service.getAll().size() == 2);

    remove(temp);
}

void Teste::test_numarare_artist() {
    char temp[L_tmpnam];
    tmpnam(temp);

    RepoMelodii repo(temp);
    ServiceMelodii service(repo);

    service.adauga_service("A", "AA", "rock");
    service.adauga_service("B", "BB", "rock");
    service.adauga_service("C", "CC", "folk");
    service.adauga_service("D", "CC", "pop");

    assert(service.melodii_cu_acelasi_autor("AA") == 0);
    assert(service.melodii_cu_acelasi_autor("CC") == 1);

    remove(temp);
}

void Teste::test_numarare_gen() {
    char temp[L_tmpnam];
    tmpnam(temp);

    RepoMelodii repo(temp);
    ServiceMelodii service(repo);

    service.adauga_service("A", "AA", "rock");
    service.adauga_service("B", "BB", "rock");
    service.adauga_service("C", "CC", "folk");
    service.adauga_service("D", "CC", "pop");

    assert(service.melodii_cu_acelasi_gen("folk") == 0);
    assert(service.melodii_cu_acelasi_gen("rock") == 1);

    remove(temp);
}


void Teste::test_all() {
    test_fisier();
    test_adaugare();
    test_stergere();
    test_numarare_artist();
    test_numarare_gen();
}
