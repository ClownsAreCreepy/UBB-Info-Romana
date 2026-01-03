cmake_minimum_required(VERSION 3.30)
project(Laborator_pregatire)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(Laborator_pregatire
    Iterator.cpp
    main.cpp
    Stiva.cpp
    TestExtins.cpp
    TestScurt.cpp)
