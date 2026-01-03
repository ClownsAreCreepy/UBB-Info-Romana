#include "Teste.h"

void Teste::test_fisier() {
    RepoTractoare repo(R"(D:\C,C++\CLion 2024.3.4\Projects\Examene\Practic\Practice\Tractoare(ClickDesen)\fisier_permanent.txt)");
    ServiceTractoare service(repo);

    assert(service.getAll().size() == 6);
    assert(service.getAll()[1].getDenumire() == "Angel");
}

void Teste::test_adaugare() {
    char temp[L_tmpnam];
    tmpnam(temp);

    RepoTractoare repo(temp);
    ServiceTractoare service(repo);

    assert(service.getAll().empty());

    service.adaugare_service(1, "B", "AA", 2);
    service.adaugare_service(2, "A", "BB", 4);
    service.adaugare_service(3, "C", "CC", 6);
    assert(service.getAll().size() == 3);
    assert(service.getAll()[1].getId() == 1);
    assert(service.getAll()[2].getId() == 3);
    assert(service.getAll()[0].getId() == 2);

    remove(temp);
}

void Teste::test_filtrare() {
    char temp[L_tmpnam];
    tmpnam(temp);

    RepoTractoare repo(temp);
    ServiceTractoare service(repo);

    service.adaugare_service(1, "B", "CC", 2);
    service.adaugare_service(2, "A", "BB", 4);
    service.adaugare_service(3, "C", "CC", 6);
    service.adaugare_service(5, "D", "EE", 6);
    service.adaugare_service(4, "E", "CC", 6);

    assert(service.filtrare_tip("BB") == 0);
    assert(service.filtrare_tip("CC") == 2);
    assert(service.filtrare_tip("FF") == -1);

    remove(temp);

}

void Teste::test_decrementare() {
    char temp[L_tmpnam];
    tmpnam(temp);

    RepoTractoare repo(temp);
    ServiceTractoare service(repo);

    service.adaugare_service(1, "B", "CC", 2);
    service.adaugare_service(2, "A", "BB", 4);
    service.adaugare_service(3, "C", "CC", 6);
    service.adaugare_service(5, "D", "EE", 6);
    service.adaugare_service(4, "E", "CC", 6);

    set<string> rezultat;
    service.getTipuri(rezultat);
    assert(rezultat.size() == 3);
    assert(rezultat.contains("CC"));
    assert(rezultat.contains("BB"));
    assert(rezultat.contains("EE"));
    assert(!rezultat.contains("AA"));

    remove(temp);
}

void Teste::test_get_tipuri() {
    char temp[L_tmpnam];
    tmpnam(temp);

    RepoTractoare repo(temp);
    ServiceTractoare service(repo);

    service.adaugare_service(1, "B", "CC", 8);
    service.adaugare_service(2, "A", "BB", 10);


    service.decrementare(1);
    assert(service.getAll()[1].getRoti() == 6);

    service.decrementare(2);
    assert(service.getAll()[0].getRoti() == 8);

    service.decrementare(1);
    assert(service.getAll()[1].getRoti() == 4);

    remove(temp);
}


void Teste::test_all() {
    test_fisier();
    test_adaugare();
    test_filtrare();
    test_decrementare();
    test_get_tipuri();
}
