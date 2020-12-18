// serviceProtocoleCom.h
// Jase avec la Dallas.

#ifndef SERVICEPROTOCOLECOM_H
#define SERVICEPROTOCOLECOM_H

#include "piloteUSART2.h"
#include "serviceBaseDeTemps.h"

// Dependances logicielles
// (copiez et adaptez ce qui suit dans "main.h")
//#define SERVICEPROTOCOLECOM_PHASE_RECEPTION 0
//#define SERVICEPROTOCOLECOM_PHASE_TRANSMISSION 1
//#define SERVICEPROTOCOLECOM_FREQUENCE_MAXIMALE_DES_TRANSMISSIONS_EN_HZ 500.0
//#define SERVICEPROTOCOLECOM_NOMBRE_DE_DONNEES_MAXIMUM  16
//#define SERVICEPROTOCOLECOM_DEBUT_DE_TRAME  $
//#define SERVICEPROTOCOLECOM_INSERTION 0x00
//#define SERVICEPROTOCOLECOM_TEMPS_D_ATTENTE_MAXIMAL_EN_MS 4
//#define SERVICEPROTOCOLECOM_FREQUENCE_MAXIMALE_DES_LECTURES_EN_HZ 2000.0

#define SERVICEPROTOCOLECOM_PAS_D_ERREURS 0
#define SERVICEPROTOCOLECOM_ERREUR_EN_ATTENTE 1
#define SERVICEPROTOCOLECOM_ERREUR_TEMPS_DEPASSE 2
#define SERVICEPROTOCOLECOM_ERREUR_LONGUEUR_NULLE 3
#define SERVICEPROTOCOLECOM_ERREUR_LONGUEUR_TROP_GRANDE 4
#define SERVICEPROTOCOLECOM_ERREUR_INSERTION_NON_NULLE 5
#define SERVICEPROTOCOLECOM_ERREUR_MAUVAIS_CHECKSUM 6

typedef struct {
  unsigned char etatDuModuleDeReception;  
  unsigned char information;
  unsigned char octetsRecus[SERVICEPROTOCOLECOM_NOMBRE_DE_DONNEES_MAXIMUM];
  unsigned char requete;
  unsigned char nombreATransmettre;
  unsigned char octetsATransmettre[SERVICEPROTOCOLECOM_NOMBRE_DE_DONNEES_MAXIMUM];
  unsigned char nombreARecevoir;
  unsigned char statut;
} SERVICEPROTOCOLECOM;

void serviceProtocoleCom_initialise(void);

extern SERVICEPROTOCOLECOM serviceProtocoleCom;

#endif
