#include "repository/lista_materii.h"
#include "ui/meniu.h"
#include "test/test_materii.h"

int main() {
    ListaMaterii lista = creeare();

    MateriePrima m1={"Faina", "Marcel", 20};
    adaugare_validata(&lista, m1);

    MateriePrima m2={"Lalele", "Ciolacu", 300};
    adaugare_validata(&lista, m2);

    MateriePrima m3={"Varza", "Vasile", 150};
    adaugare_validata(&lista, m3);

    MateriePrima m4={"Oua", "Ciprian", 100};
    adaugare_validata(&lista, m4);

    MateriePrima m5={"Carne", "Oana", 240};
    adaugare_validata(&lista, m5);

    run_tests();
    meniu(&lista);
    eliberare(&lista);
    return 0;
}