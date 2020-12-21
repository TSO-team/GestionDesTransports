#ifndef PILOTETIMER2AUTORELOAD_H
#define PILOTETIMER2AUTORELOAD_H

//MODULE: piloteTimer2AutoReload
//DESCRIPTION: pour permettre des interruptions périodiques par Timer2
//HISTORIQUE:
// 2018-09-24, Yves Roy, creation

//DEFINITIONS REQUISES PAR LE MODULE:
//Dependances materielles
//(copiez et adaptez ce qui suit dans "main.h")
//pas de dependances matérielles

//Dependances logicielles
//(copiez et adaptez ce qui suit dans "main.h")
//pas de dependances logicielles

//INFORMATION PUBLIQUE:
//Definitions publiques:
// pas de definitions publiques

//Fonctions publiques:
void piloteTimer2AutoReload_initialise(void);

//Variables publiques:
extern void (*piloteTimer2AutoReload_execute)(void);

#endif
