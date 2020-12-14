#ifndef INTERFACESTM_H
#define INTERFACESTM_H

//MODULE: interfaceSTM
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
//#define INTERFACESTM_PHASE_RECEPTION 0
//#define INTERFACESTM_PHASE_TRANSMISSION 1


//INFORMATION PUBLIQUE:
//Definitions publiques:
#define INTERFACESTM_RELACHE  0x00
#define INTERFACESTM_APPUYE  0xFF
#define INTERFACESTM_VALEUR_INVALIDE 0x0F;
#define INTERFACESTM_NOMBRE_D_OCTETS_A_RECEVOIR 8
#define INTERFACESTM_NOMBRE_D_OCTETS_A_TRANSMETTRE INTERFACESTM_NOMBRE_D_OCTETS_A_RECEVOIR
#define INTERFACESTM_PAS_D_ERREURS 0
#define INTERFACESTM_ERREUR_AU_NIVEAU_DU_PILOTE 1
#define INTERFACESTM_ERREUR_OCTET_INVALIDE 2

typedef struct
{
  unsigned char information;
  unsigned char statut;
  unsigned char octetsRecus[INTERFACESTM_NOMBRE_D_OCTETS_A_RECEVOIR];
  unsigned char requete;
  unsigned char octetsATransmettre[INTERFACESTM_NOMBRE_D_OCTETS_A_TRANSMETTRE];
} INTERFACESTM;

//Fonctions publiques:
void interfaceSTM_initialise(void);

//Variables publiques:
extern INTERFACESTM interfaceSTM;

#endif
