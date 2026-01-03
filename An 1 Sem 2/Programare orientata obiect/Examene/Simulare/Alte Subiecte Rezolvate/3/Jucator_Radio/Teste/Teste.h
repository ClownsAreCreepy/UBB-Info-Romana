#pragma once

#include "../Service/Service.h"
#include <cassert>
#include <iostream>

class Teste {
private:
    static void test_adauga();
    static void test_adauga_puncte();
    static void test_sterge();
    static void test_recalculare();

public:
    static void test_all();
};