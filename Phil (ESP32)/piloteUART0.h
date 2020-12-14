#ifndef PILOTEUART0_H
#define PILOTEUART0_H

//MODULE: piloteUART0
//DESCRIPTION: pour utiliser le UART0 du ESP32, celui qui permet de communiquer avec l'ordinateur
//HISTORIQUE:
// 2018-09-08, Yves Roy, creation

//DEFINITIONS REQUISES PAR LE MODULE:
//Dependances materielle
//pas de dépendances matérielles

//Dependances logicielles
//(copiez et adaptez ce qui suit dans "main.h")
//pas de dépendances logicielles

//INFORMATION PUBLIQUE:
//Definitions publiques:
#define PILOTEUART0_DISPONIBLE  1
#define PILOTEUART0_PAS_DISPONIBLE 0
#define PILOTEUART0_TRANSMIS  1
#define PILOTEUART0_PAS_TRANSMIS  0

//Fonctions publiques:
void piloteUART0_initialise(void);
unsigned char piloteUART0_octetDisponible(void);
unsigned char piloteUART0_octetTransmis(void);
unsigned char piloteUART0_litUnOctetRecu(void);
void piloteUART0_confirmeLaReception(void);
void piloteUART0_confirmeLaFinDeTransmission(void);
void piloteUART0_transmet(unsigned char Octet);

//Variables publiques:
//pas de variables publiques

#endif