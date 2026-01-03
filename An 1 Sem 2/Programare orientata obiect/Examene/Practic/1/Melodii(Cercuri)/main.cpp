#include "Teste/Test.h"
#include "GUI/Window.h"

int main(int argc, char *argv[]) {
    Teste::test_all();

    RepoMelodii repo(R"(D:\C,C++\CLion 2024.3.4\Projects\Examene\Practic\Practice\Melodii(Cercuri)\fisier.txt)");
    ServiceMelodii service(repo);

    QApplication app(argc, argv);

    MainWindow window(service);
    window.setWindowTitle("Melodii");
    window.show();
    return QApplication::exec();
}