#include "Teste.h"

void Teste::test_adaugare() {
    char temp[L_tmpnam];
    tmpnam(temp);

    RepoRochii repo(temp);
    const ServiceRochii service(repo);

    assert(service.getAll().empty());

    service.adauga_service(1,"Mimi","S",200,"True");
    assert(service.getAll().size() == 1);

    service.adauga_service(2,"Mumu","S",200,"True");
    assert(service.getAll().size() == 2);
    assert(service.getAll()[1].getID() == 2);

    remove(temp);
}


void Teste::test_inchiriere() {
    char temp[L_tmpnam];
    tmpnam(temp);

    RepoRochii repo(temp);
    const ServiceRochii service(repo);

    service.adauga_service(1,"Mimi","S",200,"True");
    assert(service.getAll()[0].getDisponibilitate() == "True");

    service.inchirieaza_service(0);
    assert(service.getAll()[0].getDisponibilitate() == "False");

    try {
        service.inchirieaza_service(0);
        assert(false);
    } catch (const exception &e) {
        assert(string(e.what()) == "Rochia este deja inchiriata");
    }

    remove(temp);
}


void Teste::test_sortare() {
    char temp[L_tmpnam];
    tmpnam(temp);

    RepoRochii repo(temp);
    const ServiceRochii service(repo);

    service.adauga_service(1,"Gucci","S",9000,"True");
    service.adauga_service(2,"Benoli","XS",1000,"True");
    service.adauga_service(3,"Mimi","L",10000,"False");
    service.adauga_service(4,"Mama","XL",8000,"True");
    service.adauga_service(5,"Mumu", "L", 10, "False");

    vector<Rochie> out;
    const Rochie *prev = nullptr;
    service.sorteaza_denumire(out);

    for (const auto &d: out) {
        if (prev != nullptr)
            assert(prev->getDenumire() <= d.getDenumire());
        prev = &d;
    }

    service.sorteaza_pret(out);
    prev = nullptr;
    for (const auto &d: out) {
        if (prev != nullptr)
            assert(prev->getPret() <= d.getPret());
        prev = &d;
    }

    remove(temp);
}



void Teste::test_all() {
    test_adaugare();
    test_inchiriere();
    test_sortare();
}
