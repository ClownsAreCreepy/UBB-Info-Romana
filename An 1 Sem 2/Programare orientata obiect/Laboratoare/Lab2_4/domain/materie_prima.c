#include <stdlib.h>
#include <string.h>
#include "materie_prima.h"


int validare(MateriePrima m) {
    if (strlen(m.nume) == 0 || strlen(m.producator) == 0) return 0;
    if (m.cantitate < 0) return 0;
    return 1;
}