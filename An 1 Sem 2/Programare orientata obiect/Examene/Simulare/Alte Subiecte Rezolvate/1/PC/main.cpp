#include "Test/Teste.h"
#include "GUI/Window.h"

int main(int argc, char *argv[]) {
    Teste::test_all();

    RepoProcesor repo_procesor{"D:\\C,C++\\CLion 2024.3.4\\Projects\\Examene\\Simulare\\Practice\\PC\\procesoare.txt"};
    RepoPlacaDeBaza repo_placa{"D:\\C,C++\\CLion 2024.3.4\\Projects\\Examene\\Simulare\\Practice\\PC\\placiDeBaza.txt"};

    ServiceProcesor service_procesor{repo_procesor};
    ServicePlacaDeBaza service_placa{repo_placa};

    QApplication app(argc, argv);

    MainWindow main_window(service_procesor, service_placa);
    main_window.show();

    return app.exec();
}