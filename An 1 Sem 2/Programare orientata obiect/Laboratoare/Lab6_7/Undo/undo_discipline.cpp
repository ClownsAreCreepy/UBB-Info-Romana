#include "undo_discipline.h"

void UndoAdauga::doUndo() {
    //Ultima disciplina e intotdeauna adaugata la final
    repo.sterge(static_cast<int>(repo.getAll().size()) - 1);
}

void UndoModifica::doUndo() {
    repo.modifica(index, d_veche);
}

void UndoSterge::doUndo() {
    repo.inserare_la_index(index ,d);
}