#ifndef MENIU_H
#define MENIU_H

#include "../service/materie_service.h"
#include <stdio.h>


/**
 * Functia tipareste lista de materii oferita
 * @param lista o lista de materii
 */
void afisare(ListaMaterii lista);

/**
 * Functia ruleaza aplicatia
 * @param lista o lista de materii
 */
void meniu(ListaMaterii* lista);

#endif