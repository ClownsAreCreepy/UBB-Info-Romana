#include "Teste.h"

void Teste::test_adauga() {
    char temp[L_tmpnam];
    tmpnam(temp);

    RepoJucator repo(temp);
    const ServiceJucatori service(repo);

    assert(service.getAll().empty());

    service.adauga_service("Cineva", "Norvegia", 200, 1);
    assert(service.getAll().size() == 1);

    service.adauga_service("Damn", "idk", 40, 2);
    assert(service.getAll().size() == 2);
    assert(service.getAll()[1].getTara() == "idk");

    remove(temp);
}

void Teste::test_adauga_puncte() {
    char temp[L_tmpnam];
    tmpnam(temp);

    RepoJucator repo(temp);
    const ServiceJucatori service(repo);

    service.adauga_service("Cineva", "Norvegia", 200, 1);
    service.adauga_service("Damn", "idk", 40, 2);
    service.adauga_service("Maria", "Franta", 4, 14);

    try {
        service.adauga_puncte("Cineva", -1);
        assert(false);
    } catch (const exception &e) {
        assert(string(e.what()) == "Punctele nu pot fi negative!");
    }

    try {
        service.adauga_puncte("Umm", 20);
        assert(false);
    } catch (const exception &e) {
        assert(string(e.what()) == "Jucatorul pe care il doriti nu exista!");
    }

    service.adauga_puncte("Cineva", 50);
    assert(service.getAll()[0].getPuncte() == 250);

    remove(temp);
}


void Teste::test_sterge() {
    char temp[L_tmpnam];
    tmpnam(temp);

    RepoJucator repo(temp);
    const ServiceJucatori service(repo);

    service.adauga_service("Cineva", "Norvegia", 200, 1);
    service.adauga_service("Damn", "idk", 40, 2);
    service.adauga_service("Maria", "Franta", 4, 14);
    service.adauga_service("Oana", "Austria", 500, 2);
    service.adauga_service("Medeea", "America", 20, 2);
    service.adauga_service("Bianca", "Portugalia", 18, 2);
    service.adauga_service("Rudolf", "Polu nord", 400, 2);
    service.adauga_service("Oops", "Mongolia", 46, 27);

    service.recalculare();
    service.sterge_service(3);

    assert(repo.getAll().size() == 5);
    for (int i = 0; i < 5; ++i)
        assert(repo.getAll()[i].getRank() == i + 1);

    try {
        service.sterge_service(3);
        assert(false);
    } catch (const exception &e) {
        assert(string(e.what()) == "Nu puteti sa eliminati mai mult de jumate de jucatori!");
    }

    remove(temp);
}


void Teste::test_recalculare() {
    char temp[L_tmpnam];
    tmpnam(temp);

    RepoJucator repo(temp);
    const ServiceJucatori service(repo);

    service.adauga_service("Cineva", "Norvegia", 200, 1);
    service.adauga_service("Damn", "idk", 40, 2);
    service.adauga_service("Maria", "Franta", 4, 14);
    service.adauga_service("Oana", "Austria", 500, 2);
    service.adauga_service("Medeea", "America", 20, 2);
    service.adauga_service("Bianca", "Portugalia", 18, 2);
    service.adauga_service("Rudolf", "Polu nord", 400, 2);
    service.adauga_service("Oops", "Mongolia", 46, 27);

    service.recalculare();

    for (int i = 1; i < service.getAll().size(); ++i) {
        Jucator jucator_trecut = service.getAll()[i-1];
        Jucator jucator_actual = service.getAll()[i];
        assert(jucator_trecut.getPuncte() > jucator_actual.getPuncte());
        assert(jucator_trecut.getRank() == i);
        assert(jucator_actual.getRank() == i + 1);
    }

    remove(temp);
}


void Teste::test_all() {
    test_adauga();
    test_adauga_puncte();
    test_recalculare();
    test_sterge();
}
