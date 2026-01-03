#pragma once

#include "../Service/Service.h"
#include <cassert>

class Teste {
private:
    static void test_fisier();
    static void test_adaugare();
    static void test_filtrare();
    static void test_get_tipuri();
    static void test_decrementare();

public:
    static void test_all();
};