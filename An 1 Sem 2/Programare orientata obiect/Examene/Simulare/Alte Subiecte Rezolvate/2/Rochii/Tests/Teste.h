#pragma once

#include <cassert>
#include "../Service/Service.h"

class Teste {
private:
    //Functia testeaza functionalitatea de adaugare din aplicatie
    static void test_adaugare();

public:
    static void test_all();
    static void test_inchiriere();
    static void test_sortare();
};