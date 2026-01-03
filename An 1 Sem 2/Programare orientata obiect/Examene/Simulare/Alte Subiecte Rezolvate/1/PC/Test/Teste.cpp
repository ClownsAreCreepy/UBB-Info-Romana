#include "Teste.h"

void Teste::test_adaugare() {
    {
        char temp[L_tmpnam];
        tmpnam(temp);

        RepoProcesor repo{temp};
        const ServiceProcesor service{repo};

        assert(service.getAllProcesoare().empty());

        service.service_adauga_procesoare("Pipi", 10, "GMX", 1000);
        assert(service.getAllProcesoare().size() == 1);

        service.service_adauga_procesoare("Mumu", 20, "PMX", 200);
        assert(service.getAllProcesoare().size() == 2);
        assert(service.getAllProcesoare()[1].getNrThreaduri() == 20);

        remove(temp);
    }

    {
        char temp[L_tmpnam];
        tmpnam(temp);

        RepoPlacaDeBaza repo{temp};
        const ServicePlacaDeBaza service{repo};

        assert(service.getAllPlaci().empty());

        service.service_adauga_placi("Pipi", "GMX", 1000);
        assert(service.getAllPlaci().size() == 1);

        service.service_adauga_placi("Mumu", "PMX", 200);
        assert(service.getAllPlaci().size() == 2);
        assert(service.getAllPlaci()[1].getNume() == "Mumu");

        remove(temp);
    }
}


void Teste::test_filtrare() {
    char temp[L_tmpnam];
    tmpnam(temp);

    RepoPlacaDeBaza repo(temp);
    ServicePlacaDeBaza service(repo);

    service.service_adauga_placi("Pipi", "yes", 1000);
    service.service_adauga_placi("Mumu", "nah", 1000);
    service.service_adauga_placi("Damn", "yes", 1000);
    service.service_adauga_placi("Um", "yes", 1000);
    service.service_adauga_placi("Lmao", "nah", 1000);

    vector<PlacaDeBaza> rezultat;
    service.filtrareSoclu("yes",rezultat);

    assert(rezultat.size() == 3);
    for (const auto &p: rezultat)
        assert(p.getSocluProcesor() == "yes");

    remove(temp);
}



void Teste::test_all() {
    test_adaugare();
}

