#include "Test/Teste.h"
#include "GUI/Window.h"

int main(int argc, char *argv[]) {
    Teste::test_all();

    RepoTractoare repo(R"(D:\C,C++\CLion 2024.3.4\Projects\Examene\Practic\Practice\Tractoare(ClickDesen)\fisier.txt)");
    ServiceTractoare service(repo);

    QApplication app(argc, argv);
    MainWindow window(service);
    window.setWindowTitle("Tractoare");
    window.show();
    return QApplication::exec();
}