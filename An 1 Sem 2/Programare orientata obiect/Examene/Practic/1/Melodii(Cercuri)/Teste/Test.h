#pragma once

#include <cassert>
#include "../Service/Service.h"

class Teste {
private:
    static void test_fisier();
    static void test_adaugare();
    static void test_stergere();
    static void test_numarare_artist();
    static void test_numarare_gen();

public:
    static void test_all();
};