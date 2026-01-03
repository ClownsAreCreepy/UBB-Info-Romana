#pragma once

#include "../Service/Service.h"
#include <cassert>
#include <iostream>

class Teste {
private:
    static void test_adaugare();
    static void test_raport();
    static void test_alegere();

public:
    static void test_all();
};