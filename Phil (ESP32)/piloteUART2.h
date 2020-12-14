#ifndef PILOTEUART2_H
#define PILOTEUART2_H

//MODULE: piloteUART2
//DESCRIPTION: pour utiliser le UART0 avec Timer1 en mode 2
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
#define PILOTEUART2_DISPONIBLE  1
#define PILOTEUART2_PAS_DISPONIBLE 0
#define PILOTEUART2_TRANSMIS  1
#define PILOTEUART2_PAS_TRANSMIS  0

//Fonctions publiques:
void piloteUART2_initialise(void);
unsigned char piloteUART2_octetDisponible(void);
unsigned char piloteUART2_octetTransmis(void);
unsigned char piloteUART2_litUnOctetRecu(void);
void piloteUART2_confirmeLaReception(void);
void piloteUART2_confirmeLaFinDeTransmission(void);
void piloteUART2_transmet(unsigned char Octet);

//Variables publiques:
//pas de variables publiques

#endif