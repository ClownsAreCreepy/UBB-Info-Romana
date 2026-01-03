#pragma once

#include "../Service/Service.h"
#include <cassert>
#include <iostream>

class TesteMelodii {
private:
    static void test_fisier();
    static void test_modificare();
    static void test_stergere();
    static void test_numarare();

public:
    static void test_all();
};