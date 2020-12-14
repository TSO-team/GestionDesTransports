#ifndef PILOTETICKER_H
#define PILOTETICKER_H

//MODULE: piloteTicker
//DESCRIPTION: pour permettre l'emploi d'un objet Ticker de la librairie ESP32
//HISTORIQUE:
// 2020-11-13, Yves Roy, creation

//DEFINITIONS REQUISES PAR LE MODULE:
//Dependances materielles
//(copiez et adaptez ce qui suit dans "main.h")
//pas de dependances materielles

//Dependances logicielles
//(copiez et adaptez ce qui suit dans "main.h")
//#define PILOTETICKER_PERIODE_EN_MS 1.0

//INFORMATION PUBLIQUE:
//Definitions publiques:
// pas de definitions publiques

//Fonctions publiques:
void piloteTicker_lanceLeTickerALaTouteFinDeSetup(void);
void piloteTicker_initialise(void);

//Variables publiques:
extern void (*piloteTicker_execute)(void);

#endif
