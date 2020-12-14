#ifndef SERVICEBASEDETEMPS_H
#define SERVICEBASEDETEMPS_H

//MODULE: serviceBaseDeTemps
//DESCRIPTION: pour mettre en place un service d'appels periodiques de fonctions
//pointees par un tableau de pointeurs de fonctions. Le service met en place
//une base de temps qui reposent sur l'emploi du module Ticker qui est specifie
//dans le fichier main.h.

//HISTORIQUE:
// 2020-11-13, Yves Roy, creation

//DEFINITIONS REQUISES PAR LE MODULE:
//Dependances materielles
//(copiez et adaptez ce qui suit dans "main.h")
//pas de dependances materielles

//Dependances logicielles
//(copiez et adaptez ce qui suit dans "main.h")
//#define SERVICEBASEDETEMPS_NOMBRE_DE_PHASES 2

//INFORMATION PUBLIQUE:

//Definitions publiques:
#define SERVICEBASEDETEMPS_FREQUENCE_EN_HZ (1000.0/PILOTETICKER_PERIODE_EN_MS)

//Fonctions publiques:
void serviceBaseDeTemps_initialise(void);

//Variables publiques:
extern void (*serviceBaseDeTemps_execute[SERVICEBASEDETEMPS_NOMBRE_DE_PHASES])(void);

#endif
