#include "Test/Test.h"
#include "GUI/Window.h"

int main(int argc, char *argv[]) {
    Teste::test_all();

    RepoJucatori repo("D:\\C,C++\\CLion 2024.3.4\\Projects\\Examene\\Simulare\\Practice\\Jucator_Slider\\jucatori.txt");
    ServiceJucatori service(repo);

    QApplication app(argc, argv);
    MainWindow main_window(service);

    main_window.show();

    return app.exec();
}