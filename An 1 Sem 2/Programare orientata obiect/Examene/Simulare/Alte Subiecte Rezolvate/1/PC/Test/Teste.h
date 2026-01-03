#pragma once

#include "../Service/ServiceProcesor.h"
#include "../Service/ServicePlacaDeBaza.h"
#include <cassert>
#include <iostream>

class Teste {
private:
    static void test_adaugare();
    static void test_filtrare();

public:
    static void test_all();
};