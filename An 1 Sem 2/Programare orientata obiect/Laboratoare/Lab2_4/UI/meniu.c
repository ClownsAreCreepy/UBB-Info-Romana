#include "meniu.h"
#include <stdlib.h>

void afisare(ListaMaterii lista) {
    if (lista.nr_elemente == 0) {
        printf("Nu exista materii.\n");
        return;
    }
    for (int i = 0; i < lista.nr_elemente; i++) {
        printf("%d - Nume: %s, Producator: %s, Cantitate: %d\n", i, lista.materii[i].nume, lista.materii[i].producator, lista.materii[i].cantitate);
    }
}

void meniu(ListaMaterii* lista) {
    int optiune;
    do {
        printf("\n");
        printf("\n");
        printf("--------------------MENIU_APLICATIE--------------------");
        printf("\n1. Adauga materie\n2. Modifica materie\n3. Sterge materie\n4. Afiseaza materii\n5. Filtreaza dupa nume\n6. Filtreaza dupa cantitate\n7. Sorteaza materii\n0. Iesire\n");
        printf("Alege optiunea: ");
        scanf("%d", &optiune);

        if (optiune == 1) {
            MateriePrima m;
            printf("Introdu numele, producatorul,si cantitatea: ");
            scanf("%s %s %d", m.nume, m.producator, &m.cantitate);
            adaugare_validata(lista, m);
        }

        else if (optiune == 2) {
            int index;
            MateriePrima m;
            printf("Index si materia noua: ");
            scanf("%d %s %s %d",&index, m.nume, m.producator, &m.cantitate);
            modificare_validata(lista, index, m);
        }

        else if (optiune == 3) {
            int index;
            printf("Index de sters: ");
            scanf("%d", &index);
            stergere_validata(lista, index);
        }

        else if (optiune == 4) {
            afisare(*lista);
        }

        else if (optiune == 5) {
            ListaMaterii filtrata;
            char litera;
            printf("Introdu litera cu care incep materiile filtrate: ");
            scanf("%s", &litera);
            filtrata = filtrare_dupa_nume(*lista, litera);

            afisare(filtrata);
            eliberare(&filtrata);
        }

        else if (optiune == 6) {
            ListaMaterii filtrata;
            int cantitate;
            printf("Introdu cantitatea maxima a materiilor filtrate: ");
            scanf("%d", &cantitate);
            filtrata = filtrare_dupa_cantitate(*lista, cantitate);

            afisare(filtrata);
            eliberare(&filtrata);
        }

        else if (optiune == 7) {
            ListaMaterii sortata = creeare();
            for (int i = 0; i < lista->nr_elemente;++i)
                adaugare(&sortata, lista->materii[i]);

            int criteriu;
            printf("Introdu campul dupa care se doreste sortarea(1->nume, 2->cantitate): ");
            scanf("%d", &criteriu);

            if (criteriu == 1) sortare(&sortata, cmpDupaNume);
            if (criteriu == 2) sortare(&sortata, cmpDupaCantitate);

            afisare(sortata);
            eliberare(&sortata);
        }

        else if (optiune !=0)  printf("Comanda invalida!");

    } while (optiune != 0);

}