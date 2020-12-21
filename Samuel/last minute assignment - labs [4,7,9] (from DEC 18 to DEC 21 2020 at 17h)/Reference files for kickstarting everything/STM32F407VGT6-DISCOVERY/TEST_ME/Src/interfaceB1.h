// interfaceB1.h

#ifndef INTERFACEB1_H
#define INTERFACEB1_H

#include "piloteIOB1.h"
#include "serviceBaseDeTemps.h"

//Dependances materielles
//(copiez et adaptez ce qui suit dans "main.h")
//#define INTERFACEB1_VALEUR_LUE_SI_APPUYE  1   
//#define INTERFACEB1_VALEUR_LUE_SI_RELACHE 0
//#define INTERFACEB1_FREQUENCE_DES_LECTURES_EN_HZ  100
//#define INTERFACEB1_NOMBRE_MINIMUM_DE_LECTURES_PAR_DECISION 10

// Dependances logicielles
// (copiez et adaptez ce qui suit dans "main.h")
//#define INTERFACEB1_PHASE 0
//#define INFORMATION_DISPONIBLE  1
//#define INFORMATION_TRAITEE  0
//#define REQUETE_ACTIVE  1
//#define REQUETE_TRAITEE 0
//#define MODULE_EN_FONCTION 1
//#define MODULE_PAS_EN_FONCTION 0


#define INTERFACEB1_RELACHE  0
#define INTERFACEB1_APPUYE  1
#define INTERFACEB1_INCONNU 2

#define INTERFACEB1_COMPTE_MAXIMUM_AVANT_LECTURE  (\
  FREQUENCE_DE_LA_BASE_DE_TEMPS_EN_HZ/INTERFACEB1_FREQUENCE_DES_LECTURES_EN_HZ)
#define INTERFACEB1_COMPTE_INITIAL (\
  INTERFACEB1_NOMBRE_MINIMUM_DE_LECTURES_PAR_DECISION / 2)

void interfaceB1_gere(void);

typedef struct {unsigned char etatDuModule, information, etatDuBouton;} INTERFACEB1;

void interfaceB1_initialise(void);

extern INTERFACEB1 interfaceB1;

#endif