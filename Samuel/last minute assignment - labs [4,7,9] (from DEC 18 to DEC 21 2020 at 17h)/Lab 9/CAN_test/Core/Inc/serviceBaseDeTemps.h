#ifndef SERVICEBASEDETEMPS_H
#define SERVICEBASEDETEMPS_H

//MODULE: serviceBaseDeTemps
//DESCRIPTION: pour mettre en place un service d'appels periodiques de fonctions
//point�es par un tableau de pointeurs de fonctions. Le service met en place
//une base de temps qui reposent sur l'emploi d'interruptions qui sont g�n�r�es
//par le compteur Timer6 du STM32F407 qui op�re en mode Up

//HISTORIQUE:
// 2018-09-30, Yves Roy, creation

//DEFINITIONS REQUISES PAR LE MODULE:
//Dependances materielles
//(copiez et adaptez ce qui suit dans "main.h")
//pas de dependances materielles

//Dependances logicielles
//(copiez et adaptez ce qui suit dans "main.h")
//#define SERVICEBASEDETEMPS_NOMBRE_DE_PHASES 3
//pas de d�pendances logicielles

//INFORMATION PUBLIQUE:

//Definitions publiques:
//pas de definitions publiques
#define SERVICEBASEDETEMPS_NOMBRE_DE_PHASES 7

//Fonctions publiques:
void serviceBaseDeTemps_initialise(void);
void serviceBaseDeTemps_gere(void);

//Variables publiques:
extern void (*serviceBaseDeTemps_execute[SERVICEBASEDETEMPS_NOMBRE_DE_PHASES])(void);

#endif
