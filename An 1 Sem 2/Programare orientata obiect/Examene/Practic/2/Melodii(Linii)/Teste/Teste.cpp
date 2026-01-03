#include "Teste.h"

void TesteMelodii::test_fisier() {
    RepoMelodie repo(R"(D:\C,C++\CLion 2024.3.4\Projects\Examene\Practic\Practice\Melodii(Linii)\fisier_permanent)");
    ServiceMelodii service(repo);
    assert(service.getAll().size() == 10);
    assert(service.getAll()[0].getTitlu() == "Bad Romance");
}


void TesteMelodii::test_modificare() {
    char temp[L_tmpnam];
    tmpnam(temp);

    RepoMelodie repo(temp);

    repo.adauga({1, "A", "AA", 2});
    repo.adauga({2, "B", "BB", 1});

    const ServiceMelodii service(repo);

    assert(service.getAll()[1].getTitlu() == "A");
    assert(service.getAll()[1].getRank() == 2);

    service.modifica_service(1, "C", 9);
    assert(service.getAll()[1].getTitlu() == "C");
    assert(service.getAll()[1].getRank() == 9);

    remove(temp);
}

void TesteMelodii::test_stergere() {
    char temp[L_tmpnam];
    tmpnam(temp);

    RepoMelodie repo(temp);

    repo.adauga({1, "A", "AA", 2});
    repo.adauga({2, "B", "BB", 1});
    repo.adauga({3, "C", "AA", 3});

    const ServiceMelodii service(repo);

    service.sterge_service(1, "AA");
    assert(service.getAll()[1].getTitlu() == "C");
    assert(service.getAll().size() == 2);

    try {
        service.sterge_service(2, "BB");
        assert(false);
    } catch (const exception &e) {
        assert(static_cast<string>(e.what()) == "Melodia este ultima melodie a artistului! Nu se va sterge din bun simt!");
    }

    remove(temp);
}

void TesteMelodii::test_numarare() {
    char temp[L_tmpnam];
    tmpnam(temp);

    RepoMelodie repo(temp);

    const Melodie m1 {1, "A", "AA", 1};
    const Melodie m2 {2, "B", "BB", 1};
    const Melodie m3 {3, "C", "AA", 3};

    repo.adauga(m1);
    repo.adauga(m2);
    repo.adauga(m3);

    const ServiceMelodii service(repo);

    assert(service.melodii_cu_acelasi_rank(m1) == 1);
    assert(service.melodii_cu_acelasi_rank(m2) == 1);
    assert(service.melodii_cu_acelasi_rank(m3) == 0);

    remove(temp);
}

void TesteMelodii::test_all() {
    test_fisier();
    test_modificare();
    test_stergere();
    test_numarare();
}
