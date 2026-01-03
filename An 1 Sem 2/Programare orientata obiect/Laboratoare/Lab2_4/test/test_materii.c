#include <assert.h>
#include <string.h>

#include "../service/materie_service.h"


void test_validare() {
    MateriePrima m1 = {"Faina", "Producator1", 50};
    MateriePrima m2 = {"", "Producator2", 30};
    MateriePrima m3 = {"Zahar", "", 20};
    MateriePrima m4 = {"Unt", "Producator3", -5};

    assert(validare(m1) == 1);
    assert(validare(m2) == 0);
    assert(validare(m3) == 0);
    assert(validare(m4) == 0);
}


void test_creeare() {
    ListaMaterii lista = creeare();
    assert(lista.nr_elemente == 0);
    assert(lista.capacitate == 2);
    eliberare(&lista);
}


void test_redimensionareCrestere() {
    ListaMaterii lista = creeare();
    MateriePrima m = {"Faina", "Producator1", 50};
    MateriePrima n = {"Carne", "Producator2", 150};
    MateriePrima p = {"Varza", "Producator3", 900};

    adaugare(&lista, m);
    adaugare(&lista, n);
    assert(lista.capacitate == 2);

    adaugare(&lista, p);
    assert(lista.capacitate == 4);
    eliberare(&lista);
}


void test_redimensionareScadere() {
    ListaMaterii lista = creeare();
    MateriePrima m1={"Faina", "Marcel", 20};
    MateriePrima m2={"Lalele", "Ciolacu", 300};
    MateriePrima m3={"Varza", "Vasile", 150};
    MateriePrima m4={"Oua", "Ciprian", 100};
    MateriePrima m5={"Carne", "Oana", 240};

    adaugare(&lista, m1);
    adaugare(&lista, m2);
    adaugare(&lista, m3);
    adaugare(&lista, m4);
    adaugare(&lista, m5);

    assert(lista.capacitate == 8);

    stergere(&lista, 0);
    stergere(&lista, 1);
    stergere(&lista, 2);
    stergere(&lista, 3);

    assert(lista.capacitate == 4);

    eliberare(&lista);
}


void test_adaugare() {
    ListaMaterii lista = creeare();
    MateriePrima m = {"Faina", "Producator1", 50};
    adaugare_validata(&lista, m);
    assert(lista.nr_elemente == 1);

    MateriePrima m2 = {"Faina", "Producator2", 150};
    adaugare_validata(&lista, m2);
    assert(lista.nr_elemente == 1);
    assert(lista.materii[0].cantitate == 200);

    MateriePrima m3 = {"", "Producator1", 20};
    adaugare_validata(&lista, m3);
    assert(lista.nr_elemente == 1);

    eliberare(&lista);
}


void test_modificare() {
    ListaMaterii lista = creeare();
    MateriePrima m1 = {"Faina", "Producator1", 50};
    MateriePrima m2 = {"Faina", "Producator2", 100};
    adaugare_validata(&lista, m1);
    modificare_validata(&lista, 0, m2);
    assert(lista.materii[0].cantitate == 100);

    MateriePrima m3 = {"Zahar", "", 20};
    modificare_validata(&lista,0, m3);
    assert(lista.materii[0].cantitate == 100);

    eliberare(&lista);
}


void test_stergere() {
    ListaMaterii lista = creeare();
    MateriePrima m1 = {"Faina", "Producator1", 50};
    MateriePrima m2 = {"Zahar", "Producator2", 30};
    adaugare_validata(&lista, m1);
    adaugare_validata(&lista, m2);

    stergere_validata(&lista, 0);
    assert(lista.nr_elemente == 1);
    assert(strcmp(lista.materii[0].nume, "Zahar") == 0);

    stergere_validata(&lista,20);
    assert(lista.nr_elemente == 1);

    eliberare(&lista);
}


void test_filtrare_dupa_nume() {
    ListaMaterii lista = creeare();
    adaugare_validata(&lista, (MateriePrima){"Faina", "Producator1", 50});
    adaugare_validata(&lista, (MateriePrima){"Zahar", "Producator2", 30});
    ListaMaterii filtrata = filtrare_dupa_nume(lista, 'F');
    assert(filtrata.nr_elemente == 1);
    assert(strcmp(filtrata.materii[0].nume, "Faina") == 0);

    eliberare(&lista);
    eliberare(&filtrata);
}


void test_filtrare_dupa_cantitate() {
    ListaMaterii lista = creeare();
    adaugare_validata(&lista, (MateriePrima){"Faina", "Producator1", 50});
    adaugare_validata(&lista, (MateriePrima){"Zahar", "Producator2", 30});
    ListaMaterii filtrata = filtrare_dupa_cantitate(lista, 40);
    assert(filtrata.nr_elemente == 1);
    assert(filtrata.materii[0].cantitate == 30);

    eliberare(&lista);
    eliberare(&filtrata);
}


void test_cmpDupaNume() {
    MateriePrima m = {"Faina", "Producator1", 50};
    MateriePrima n = {"Carne", "Producator2", 150};

    assert(cmpDupaNume(m,n)>0);
}

void test_cmpDupaCantitate() {
    MateriePrima m = {"Faina", "Producator1", 50};
    MateriePrima n = {"Carne", "Producator2", 150};

    assert(cmpDupaCantitate(m,n)<0);
}


void test_sortare() {
    ListaMaterii lista = creeare();
    adaugare_validata(&lista, (MateriePrima){"Zahar", "Producator2", 30});
    adaugare_validata(&lista, (MateriePrima){"Faina", "Producator1", 50});

    sortare(&lista, cmpDupaNume);
    assert(strcmp(lista.materii[0].nume, "Faina") == 0);

    sortare(&lista, cmpDupaCantitate);
    assert(lista.materii[0].cantitate == 30);

    eliberare(&lista);
}

void run_tests() {
    test_validare();
    test_creeare();
    test_redimensionareCrestere();
    test_redimensionareScadere();
    test_adaugare();
    test_modificare();
    test_stergere();
    test_filtrare_dupa_nume();
    test_filtrare_dupa_cantitate();
    test_cmpDupaNume();
    test_cmpDupaCantitate();
    test_sortare();
}