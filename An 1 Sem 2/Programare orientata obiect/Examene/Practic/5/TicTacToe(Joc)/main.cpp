#include "Test/Teste.h"
#include "GUI/Window.h"

int main(int argc, char *argv[]) {
    Teste::test_all();

    RepoJoc repo(R"(D:\C,C++\CLion 2024.3.4\Projects\Examene\Practic\Practice\TicTacToe(Joc)\fisier.txt)");
    ServiceJoc service(repo);

    QApplication app(argc, argv);

    MainWindow window(service);
    window.setWindowTitle("Jocuri");
    window.show();
    return QApplication::exec();
}