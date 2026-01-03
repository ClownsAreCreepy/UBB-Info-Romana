#include "Test/Teste.h"
#include "GUI/Window.h"

int main(int argc, char *argv[]) {
    Teste::test_all();

    RepoTask repo(R"(D:\C,C++\CLion 2024.3.4\Projects\Examene\Practic\Practice\Tasks(ObsBtn)\fisier.txt)");
    ServiceTask service(repo);

    QApplication app(argc, argv);

    MainWindow window(service);
    window.setWindowTitle("Tasks");
    window.show();

    return QApplication::exec();
}