#ifndef PROCESSUSCLIGNOTANT_H
#define PROCESSUSCLIGNOTANT_H
#include "serviceBaseDeTemps.h"
#include "interfaceT1.h"

/*
#define PROCESSUSCLIGNOTANT_COMPTE_COURT_ETEINT (\
  PROCESSUSCLIGNOTANT_TEMPS_COURT_ETEINT_EN_MS * FREQUENCE_DE_LA_BASE_DE_TEMPS_EN_HZ \
  /1000.0)
#define PROCESSUSCLIGNOTANT_COMPTE_COURT_ALLUME (\
  PROCESSUSCLIGNOTANT_TEMPS_COURT_ALLUME_EN_MS * FREQUENCE_DE_LA_BASE_DE_TEMPS_EN_HZ \
  /1000.0)
#define PROCESSUSCLIGNOTANT_COMPTE_LONG_ETEINT (\
  PROCESSUSCLIGNOTANT_TEMPS_LONG_ETEINT_EN_MS * FREQUENCE_DE_LA_BASE_DE_TEMPS_EN_HZ \
  /1000.0)
#define PROCESSUSCLIGNOTANT_COMPTE_LONG_ALLUME (\
  PROCESSUSCLIGNOTANT_TEMPS_LONG_ALLUME_EN_MS * FREQUENCE_DE_LA_BASE_DE_TEMPS_EN_HZ \
  /1000.0)
*/

// MODULE: processusClignotant
// DESCRIPTION: implemente la gestion d'un clignotant en utilise un pointeur de
// fonctions fourni par serviceBaseDeTemps.

// Dependances logicielles
// (copiez et adaptez ce qui suit dans "main.h")
//#define PROCESSUSCLIGNOTANT_PHASE 0
//#define PROCESSUSCLIGNOTANT_TEMPS_COURT_ETEINT_EN_MS 300
//#define PROCESSUSCLIGNOTANT_TEMPS_COURT_ALLUME_EN_MS 200
//#define PROCESSUSCLIGNOTANT_TEMPS_LONG_ETEINT_EN_MS 500
//#define PROCESSUSCLIGNOTANT_TEMPS_LONG_ALLUME_EN_MS 1000

void processusClignotant_initialise(void);
void processusClignotant_eteintUnPeu(void);
void processusClignotant_allumeUnPeu(void);
void processusClignotant_eteintLongtemps(void);
void processusClignotant_allumeLongtemps(void);

//extern unsigned int processusClignotant_compteur;

#endif


