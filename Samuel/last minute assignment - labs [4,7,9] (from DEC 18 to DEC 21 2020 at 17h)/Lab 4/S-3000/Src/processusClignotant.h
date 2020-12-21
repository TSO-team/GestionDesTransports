#ifndef PROCESSUSCLIGNOTANT_H
#define PROCESSUSCLIGNOTANT_H

//MODULE: processusClignotant
//DESCRIPTION: implemente la gestion d'un clignotant en utilise un pointeur de
//fonctions fourni par serviceBaseDeTemps.

//HISTORIQUE:
// 2018-09-30, Yves Roy, creation
#include "main.h"
#include "serviceBaseDeTemps.h"
#include "interfaceT1.h"

//DEFINITIONS REQUISES PAR LE MODULE:
//Dependances materielles
//(copiez et adaptez ce qui suit dans "main.h")
//pas de dependances materielles

//Dependances logicielles
//(copiez et adaptez ce qui suit dans "main.h")
//#define PROCESSUSCLIGNOTANT_PHASE 0
//#define PROCESSUSCLIGNOTANT_TEMPS_COURT_ETEINT_EN_MS  300
//#define PROCESSUSCLIGNOTANT_TEMPS_COURT_ALLUME_EN_MS  200
//#define PROCESSUSCLIGNOTANT_TEMPS_LONG_ETEINT_EN_MS  500
//#define PROCESSUSCLIGNOTANT_TEMPS_LONG_ALLUME_EN_MS  1000

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

//INFORMATION PUBLIQUE:
//Definitions publiques:
//pas de definitions publiques

//Fonctions:
void processusClignotant_initialise(void);
void processusClignotant_eteintUnPeu(void);
void processusClignotant_allumeUnPeu(void);
void processusClignotant_eteintLongtemps(void);
void processusClignotant_allumeLongtemps(void);

//Variables publiques:
//pas de variables publiques

#endif


