#include "Teste.h"

void Teste::test_fisier() {
    RepoJoc repo(R"(D:\C,C++\CLion 2024.3.4\Projects\Examene\Practic\Practice\TicTacToe(Joc)\fisier_permanent.txt)");
    ServiceJoc service(repo);

    assert(service.getAll().size() == 10);
    assert(service.getAll()[2].getId() == 7);
}

void Teste::test_adaugare() {
    char temp[L_tmpnam];
    tmpnam(temp);

    RepoJoc repo(temp);
    ServiceJoc service(repo);

    assert(service.getAll().size() == 0);

    service.adauga_service(3, "XXXXXXXXX", "X");
    assert(service.getAll().size() == 1);
    assert(service.getAll()[0].getId() == 1);

    service.adauga_service(3, "XXXOXXOXX", "O");
    assert(service.getAll().size() == 2);
    assert(service.getAll()[1].getId() == 2);
    assert(service.getAll()[1].getJucator() == "O");

    remove(temp);
}

void Teste::test_modificare() {
    char temp[L_tmpnam];
    tmpnam(temp);

    RepoJoc repo(temp);
    ServiceJoc service(repo);

    service.adauga_service(3, "XXXXXXXXX", "X");
    service.adauga_service(3, "XXXOXXOXX", "O");

    service.modifica_service(1, 3, "OOOOOOOOO", "O", "Neinceput");
    assert(service.getAll()[0].getJucator() == "O");

    try {
        service.modifica_service(1,3, "XOXOXOXO", "X", "Terminat");
        assert(false);
    } catch (const exception &e) {
        assert(string(e.what()) == "Tabla trebuie sa contina (dimensiune)^2 caractere!\n");
    }

    try {
        service.modifica_service(1,2, "Damn zaaz", "Eu", "Acum am inceput");
        assert(false);
    } catch (const exception &e) {
        assert(string(e.what()) == "Dimensiunea poate fi 3, 4 sau 5!\nTabla trebuie sa contina (dimensiune)^2 caractere!\nTabla contine doar caracterele X, O sau -!\nJucatorul poate fi doar X sau O!\nStarea poate fi doar Neinceput, In derulare sau Terminat!\n");
    }

    remove(temp);
}

void Teste::test_all() {
    test_fisier();
    test_adaugare();
    test_modificare();
}
