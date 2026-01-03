#include "Teste/Teste.h"
#include "GUI/Window.h"

int main(int argc, char *argv[]) {
    Teste::test_all();

    RepoProdus repo(R"(D:\C,C++\CLion 2024.3.4\Projects\Examene\Practic\Practice\Produse(Observer)\fisier.txt)");
    ServiceProdus service(repo);

    QApplication app(argc, argv);
    MainWindow window(service);
    window.setWindowTitle("Produse");
    window.show();
    return QApplication::exec();
}