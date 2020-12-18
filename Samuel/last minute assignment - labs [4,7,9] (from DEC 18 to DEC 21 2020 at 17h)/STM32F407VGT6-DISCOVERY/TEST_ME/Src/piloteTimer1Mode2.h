// piloteTimer1Mode2.h

#ifndef PILOTETIMER1MODE2_H
#define PILOTETIMER1MODE2_H

#include "main.h"

#define PILOTETIMER1MODE2_COMPTE_DE_DEPART ( \
     256 - ((1 + PILOTETIMER1MODE2_UTILISE_LE_DOUBLEUR_DE_TAUX) * \
     MAIN_FREQUENCE_D_OSCILLATEUR_EN_KHZ * 1000.0) / \
     (32.0 * PILOTETIMER1MODE2_TAUX_DE_BITS))

// Dependances logicielles
// (copiez et adaptez ce qui suit dans "main.h")
//#define PILOTETIMER1MODE2_TAUX_DE_BITS 19200.0
//#define PILOTETIMER1MODE2_UTILISE_LE_DOUBLEUR_DE_TAUX 1

__interrupt void PiloteTimer2Autoreload_interruption(void);
void piloteTimer1Mode2_initialise(void);

#endif
