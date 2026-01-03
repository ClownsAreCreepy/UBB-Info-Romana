cmake_minimum_required(VERSION 3.28.3)
project(Lab2_4 C)

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror")

set(CMAKE_C_STANDARD 11)

add_executable(Lab2_4
        main.c
        domain/materie_prima.c
        repository/lista_materii.c
        service/materie_service.c
        UI/meniu.c
        test/test_materii.c)
