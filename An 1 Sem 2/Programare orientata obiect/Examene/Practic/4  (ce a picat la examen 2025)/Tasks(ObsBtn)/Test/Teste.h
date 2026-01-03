#pragma once

#include "../Service/Service.h"
#include <cassert>

class Teste {
private:
    static void test_fisier();
    static void test_adaugare();
    static void test_filtrare();
    static void test_stare();

public:
    static void test_all();
};