#include "Test/teste_discipline.h"
#include "UI/consola_discipline.h"
#include "GUI/main_window.h"


int main(int argc, char* argv[]) {
    TesteDiscipline::testAll();

    //CLI

    //Memorie
    RepoDisciplinaMem repo_mem;
    ServiceDisciplina service_mem{repo_mem};
    Consola::preload_data(service_mem);

    //Fisier
    RepoDisciplinaFile repo_file{"fisier.txt"};
    ServiceDisciplina service_file{repo_file};

    //Fals
    RepoDisciplinaFals repo_fals{0.5};
    ServiceDisciplina service_fals{repo_fals};

    //const Consola ui {service_mem};
    //const Consola ui{service_file};
    //const Consola ui{service_fals};


    //ui.run();

    //return 0;

    //GUI

    QApplication app(argc, argv);
    MainWindow main_window(service_mem);
    main_window.setWindowTitle("Discipline");

    main_window.show();

    return QApplication::exec();
}