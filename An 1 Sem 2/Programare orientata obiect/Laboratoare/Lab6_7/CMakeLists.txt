cmake_minimum_required(VERSION 3.28)
project(Lab6_7)

# QT
set(CMAKE_PREFIX_PATH "D:/QT/6.9.0/mingw_64/lib/cmake")
find_package(Qt6 COMPONENTS Widgets REQUIRED)
set(CMAKE_AUTOMOC ON)

# Compiler settings
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
add_compile_options(-Wno-trigraphs)

# Warnings
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wnon-virtual-dtor -Wold-style-cast -Wunused -Woverloaded-virtual -Wuseless-cast -Wall -Wextra -Werror -Wpedantic -Wconversion -Wsign-conversion")

add_executable(Lab6_7
        main.cpp
        Domain/discipline.cpp
        Repo/repository_discipline.cpp
        Repo/repository_file_discipline.cpp
        Repo/repository_fals_discipline.cpp
        Test/teste_discipline.cpp
        Service/service_discipline.cpp
        UI/consola_discipline.cpp
        Valid/validare_discipline.cpp
        Contract/contract_discipline.cpp
        DTO/dto_discipline.cpp
        Undo/undo_discipline.cpp
        GUI/main_window.cpp
        GUI/contract_window.cpp
        Observer/observer_discipline.cpp
        GUI/contract_window_readonly.cpp
        GUI/model_tabel_disciplina.cpp
        GUI/model_lista_disciplina.cpp
)

target_link_libraries(Lab6_7 Qt6::Widgets)