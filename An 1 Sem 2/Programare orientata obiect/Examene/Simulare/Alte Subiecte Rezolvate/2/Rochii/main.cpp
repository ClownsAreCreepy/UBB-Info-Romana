#include "Tests/Teste.h"
#include "GUI/Window.h"

int main(int argc, char *argv[]) {
    Teste::test_all();

    RepoRochii repo{"D:\\C,C++\\CLion 2024.3.4\\Projects\\Examene\\Simulare\\Practice\\Rochii\\rochie.txt"};
    ServiceRochii service{repo};

    QApplication app{argc, argv};
    MainWindow main_window{service};

    main_window.show();

    return app.exec();
}