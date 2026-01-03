#include "Teste.h"

void Teste::test_fisier() {
    RepoTask repo(R"(D:\C,C++\CLion 2024.3.4\Projects\Examene\Practic\Practice\Tasks(ObsBtn)\fisier_permanent.txt)");
    ServiceTask service(repo);

    assert(service.getAll().size() == 10);
    assert(service.getAll()[2].getDescriere() == "Uau");
}

void Teste::test_adaugare() {
    char temp[L_tmpnam];
    tmpnam(temp);

    RepoTask repo(temp);
    ServiceTask service(repo);

    assert(service.getAll().empty());

    service.adaugare_service(1,"A",{"AA", "AAA"},"open");
    service.adaugare_service(2,"B",{"BB", "BBB"},"closed");
    service.adaugare_service(3,"C",{"CC", "CCC"},"open");
    assert(service.getAll().size() == 3);
    assert(service.getAll()[1].getDescriere() == "A");

    service.adaugare_service(4,"D",{"DD", "DDD"},"closed");
    assert(service.getAll().size() == 4);
    assert(service.getAll()[1].getDescriere() == "D");
    assert(service.getAll()[2].getDescriere() == "A");

    try {
        service.adaugare_service(5,"D",{"DD", "DDD", "Inca unu", "Tot unu", "Si mai unu"},"closed");
        assert(false);
    } catch (const exception &e) {
        assert(string(e.what()) == "Trebuie minim 1 sau maxim 4 programatori!\n");
    }

    try {
        service.adaugare_service(4,"",{},"caca");
        assert(false);
    } catch (const exception &e) {
        assert(string(e.what()) == "Id-ul trebuie sa fie unic!\nDescirerea nu poate fi goala!\nTrebuie minim 1 sau maxim 4 programatori!\nStarea poate fi: open, inprogress sau closed\n");
    }

    remove(temp);
}

void Teste::test_filtrare() {
    char temp[L_tmpnam];
    tmpnam(temp);

    RepoTask repo(temp);
    ServiceTask service(repo);

    service.adaugare_service(1,"A",{"AA", "CC"},"open");
    service.adaugare_service(2,"B",{"BB", "AA"},"closed");
    service.adaugare_service(3,"C",{"CC", "CC"},"open");
    service.adaugare_service(4,"D",{"AA", "DDD"},"closed");

    vector<int> filtrata;

    service.filtrare_service(filtrata, "AA");
    vector expected{2, 4, 1};
    assert(filtrata == expected);

    service.filtrare_service(filtrata, "CC");
    expected = {1, 3};
    assert(filtrata == expected);

    service.filtrare_service(filtrata, "EE");
    expected = {};
    assert(filtrata == expected);

    remove(temp);
}

void Teste::test_stare() {
    char temp[L_tmpnam];
    tmpnam(temp);

    RepoTask repo(temp);
    ServiceTask service(repo);

    service.adaugare_service(1,"A",{"AA", "CC"},"open");
    service.adaugare_service(2,"B",{"BB", "AA"},"closed");

    service.set_stare_service(1, "stare noua");
    assert(service.getAll()[1].getStare() == "stare noua");

    service.set_stare_service(2, "abcdamn");
    assert(service.getAll()[0].getStare() == "abcdamn");
    assert(service.getAll()[0].getDescriere() == "B");


    remove(temp);
}

void Teste::test_all() {
    test_fisier();
    test_adaugare();
    test_filtrare();
    test_stare();
}
