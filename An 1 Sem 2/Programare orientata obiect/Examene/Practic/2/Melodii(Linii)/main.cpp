#include "Teste/Teste.h"
#include "GUI/Main_Window.h"

int main(int argc, char *argv[]) {
    TesteMelodii::test_all();

    RepoMelodie repo("D:\\C,C++\\CLion 2024.3.4\\Projects\\Examene\\Practic\\Practice\\Melodii(Linii)\\fisier.txt");
    ServiceMelodii service(repo);
    
    QApplication app(argc, argv);
    MainWindow window(service);
    window.setWindowTitle("Melodii");

    window.show();
    return QApplication::exec();
}