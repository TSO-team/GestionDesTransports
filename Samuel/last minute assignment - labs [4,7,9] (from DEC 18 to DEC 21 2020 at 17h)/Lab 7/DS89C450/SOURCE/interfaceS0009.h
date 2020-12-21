#ifndef INTERFACES0009_H
#define INTERFACES0009_H

//MODULE: interfaceS0009
//DESCRIPTION: implemente le protocole qui permet d'interagir avec un ensemble
//de developpement STM32F4-DISCO programme avec le logiciel 247-637 S-0009 en
//utilisant un pointeur de fonctions du module serviceBaseDeTemps

//HISTORIQUE:
// 2019-10-27, Yves Roy, creation

//DEFINITIONS REQUISES PAR LE MODULE:
//Dependances materielles
//(copiez et adaptez ce qui suit dans "main.h")
//pas de dependances materielles

//Dependances logicielles
//(copiez et adaptez ce qui suit dans "main.h")
//#define INTERFACES0009_PHASE_RECEPTION 0
//#define INTERFACES0009_PHASE_TRANSMISSION 1


//INFORMATION PUBLIQUE:
//Definitions publiques:
#define INTERFACES0009_RELACHE  0x00
#define INTERFACES0009_APPUYE  0xFF
#define INTERFACES0009_VALEUR_INVALIDE 0x0F;
#define INTERFACES0009_NOMBRE_D_OCTETS_A_RECEVOIR 4
#define INTERFACES0009_NOMBRE_D_OCTETS_A_TRANSMETTRE INTERFACES0009_NOMBRE_D_OCTETS_A_RECEVOIR
#define INTERFACES0009_PAS_D_ERREURS 0
#define INTERFACES0009_ERREUR_AU_NIVEAU_DU_PILOTE 1
#define INTERFACES0009_ERREUR_OCTET_INVALIDE 2

typedef struct
{
  unsigned char information;
  unsigned char statut;
  unsigned char octetsRecus[INTERFACES0009_NOMBRE_D_OCTETS_A_RECEVOIR];
  unsigned char requete;
  unsigned char octetsATransmettre[INTERFACES0009_NOMBRE_D_OCTETS_A_TRANSMETTRE];
} INTERFACES0009;

//Fonctions publiques:
void interfaceS0009_initialise(void);

//Variables publiques:
extern INTERFACES0009 interfaceS0009;

#endif
