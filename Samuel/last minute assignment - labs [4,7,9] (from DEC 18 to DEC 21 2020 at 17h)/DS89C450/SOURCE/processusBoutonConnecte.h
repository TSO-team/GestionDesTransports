#ifndef PROCESSUSBOUTONCONNECTE_H
#define PROCESSUSBOUTONCONNECTE_H

//MODULE: processusBoutonConnecte
//DESCRIPTION: implemente la gestion des messages que s'echangent l'ensemble
//de developpement Dallas et un ensemble STM32F4-DISCO.

//HISTORIQUE:
// 2019-10-27, Yves Roy, creation

//DEFINITIONS REQUISES PAR LE MODULE:
//Dependances materielles
//(copiez et adaptez ce qui suit dans "main.h")
//pas de dependances materielles

//Dependances logicielles
//(copiez et adaptez ce qui suit dans "main.h")
//#define PROCESSUSBOUTONCONNECTE_PHASE 0

//INFORMATION PUBLIQUE:
//Definitions publiques:

typedef struct
{
  unsigned char etatDuModule;  
} PROCESSUSBOUTONCONNECTE;

//Fonctions publiques:
void processusBoutonConnecte_initialise(void);

//Variables publiques:
extern PROCESSUSBOUTONCONNECTE processusBoutonConnecte;

#endif
