// interfaceS0006.h
// Protocole qui jase avec la Dallas.

#ifndef INTERFACES0006_H
#define INTERFACES0006_H

#include "serviceBaseDeTemps.h"
#include "serviceProtocoleCom.h"

// Dependances logicielles
// (copiez et adaptez ce qui suit dans "main.h")
//#define INTERFACES0006_PHASE_RECEPTION 0
//#define INTERFACES0006_PHASE_TRANSMISSION 1

#define INTERFACES0006_RELACHE 0x00
#define INTERFACES0006_APPUYE 0xFF

//#define INTERFACES0006_OCTET_A_TRANSMETTRE 0x5A
//#define INTERFACES0006_NOMBRE_D_ENTIERS_A_RECEVOIR 3

#define INTERFACES0006_NOMBRE_D_OCTETS_A_RECEVOIR 4
#define INTERFACES0006_NOMBRE_D_OCTETS_A_TRANSMETTRE 4
#define INTERFACES0006_PAS_D_ERREURS 0
#define INTERFACES0006_ERREUR_AU_NIVEAU_DU_PILOTE 1
#define INTERFACES0006_ERREUR_OCTET_INVALIDE 2
#define INTERFACES0006_ERREUR_ENTIER_0_INVALIDE 3
#define INTERFACES0006_ERREUR_ENTIER_1_INVALIDE 4
#define INTERFACES0006_ERREUR_ENTIER_2_INVALIDE 5

typedef struct {
  unsigned char information;
  unsigned char statut;
  unsigned char nombreARecevoir;
  unsigned char octetRecu;
  unsigned char octetsRecus[INTERFACES0006_NOMBRE_D_OCTETS_A_RECEVOIR];
  unsigned char requete;
  unsigned char nbOctetsATransmettre;
  unsigned char octetsATransmettre[INTERFACES0006_NOMBRE_D_OCTETS_A_TRANSMETTRE];
} INTERFACES0006;

void interfaceS0006_initialise(void);

extern INTERFACES0006 interfaceS0006;

#endif
