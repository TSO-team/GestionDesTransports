#ifndef SERVICEBASEDETEMPS_H
#define SERVICEBASEDETEMPS_H
#include "piloteTimer6Up.h"

// Dependances logicielles
// (copiez et adaptez ce qui suit dans "main.h")
#define SERVICEBASEDETEMPS_NOMBRE_DE_PHASES 5
// pas de dépendances logicielles

void serviceBaseDeTemps_initialise(void), serviceBaseDeTemps_gere(void);
extern void (*serviceBaseDeTemps_execute[SERVICEBASEDETEMPS_NOMBRE_DE_PHASES])(void);

#endif
