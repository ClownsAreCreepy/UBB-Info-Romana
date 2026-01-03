#include "Teste.h"

void Teste::test_fisier() {
    RepoProdus repo(R"(D:\C,C++\CLion 2024.3.4\Projects\Examene\Practic\Practice\Produse(Observer)\fisier_permanent.txt)");
    ServiceProdus service(repo);
    assert(service.getAll().size() == 10);
    assert(service.getAll()[3].getNume() == "Oops");
}

void Teste::test_adaugare() {
    char temp[L_tmpnam];
    tmpnam(temp);

    RepoProdus repo(temp);
    ServiceProdus service(repo);

    assert(service.getAll().empty());

    service.adauga_service(1, "A", "AA", 10.2);
    assert(service.getAll().size() == 1);

    service.adauga_service(2, "B", "BB", 12.2);
    assert(service.getAll().size() == 2);
    assert(service.getAll()[1].getNume() == "B");

    service.adauga_service(3, "C", "CC", 12.2);
    assert(service.getAll().size() == 3);
    assert(service.getAll()[1].getNume() == "B");

    try {
        service.adauga_service(1, "", "", 1000.0);
        assert(false);
    } catch (const exception &e) {
        assert(string(e.what()) == "Id-ul deja exista!\nNumele nu poate fi gol!\nPretul trebuie sa fie intre 1 si 100!\n");
    }

    try {
        service.adauga_service(4, "D", "DD", 0.5);
        assert(false);
    } catch (const exception &e) {
        assert(string(e.what()) == "Pretul trebuie sa fie intre 1 si 100!\n");
    }

    remove(temp);
}

void Teste::test_filtrare() {
    char temp[L_tmpnam];
    tmpnam(temp);

    RepoProdus repo(temp);
    ServiceProdus service(repo);


    service.adauga_service(1, "A", "AA", 10.2);
    service.adauga_service(2, "B", "BB", 50.2);
    service.adauga_service(3, "C", "CC", 25.2);

    vector solution1 {1, 3};
    vector result = service.filtrare_pret(50);
    assert(solution1 == result);

    vector solution2 {1, 3, 2};
    result = service.filtrare_pret(51);
    assert(solution2 == result);

    vector<int> solution3 {};
    result = service.filtrare_pret(5);
    assert(solution3 == result);

    remove(temp);
}

void Teste::test_vocale() {
    char temp[L_tmpnam];
    tmpnam(temp);

    RepoProdus repo(temp);
    ServiceProdus service(repo);

    assert(service.nr_vocale("Mama") == 2);
    assert(service.nr_vocale("Mnmn") == 0);
    assert(service.nr_vocale("AoinuA") == 5);

    remove(temp);
}

void Teste::test_all() {
    test_fisier();
    test_adaugare();
    test_filtrare();
    test_vocale();
}
