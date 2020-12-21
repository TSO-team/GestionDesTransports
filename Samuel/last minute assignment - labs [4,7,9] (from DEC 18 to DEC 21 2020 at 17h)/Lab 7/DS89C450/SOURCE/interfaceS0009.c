//interfaceS0009:
//Historique: 
// 2018-10-28, Yves Roy, creation

//INCLUSIONS
#include "main.h"
#ifdef SERVICEPROTOCOLE637_DEBUG
  #include "piloteUART0.h"
#endif
#include "piloteUART1.h"
#include "serviceBaseDeTemps.h"
#include "serviceProtocole637.h"
#include "interfaceB1.h"
#include "interfaceS0009.h"

//Definitions privees
//pas de définitions privees

//Declarations de fonctions privees:
void interfaceS0009_recupereLesDonneesRecues(void);
unsigned char interfaceS0009_valideLaReception(void);
void interfaceS0009_prepareLaTransmission(void);
void interfaceS0009_gereLaReception(void);
void interfaceS0009_gereLaTransmission(void);

//Definitions de variables privees:
unsigned char interfaceS0009_octetsTraites[INTERFACES0009_NOMBRE_D_OCTETS_A_RECEVOIR];

//Definitions de fonctions privees:
void interfaceS0009_recupereLesDonneesRecues(void)
{
unsigned char i;
  for (i = 0; i < INTERFACES0009_NOMBRE_D_OCTETS_A_RECEVOIR; i++)
  {
    interfaceS0009.octetsRecus[i] = serviceProtocole637.octetsRecus[i];
  }
}

unsigned char interfaceS0009_valideLaReception(void)
{
unsigned char i;
  for (i = 0; i < INTERFACES0009_NOMBRE_D_OCTETS_A_RECEVOIR; i++)
  {
    if (interfaceS0009.octetsRecus[i] != i)
    {
      return INTERFACES0009_ERREUR_OCTET_INVALIDE;
    }
  }  
  return INTERFACES0009_PAS_D_ERREURS;
}

void interfaceS0009_prepareLaTransmission(void)
{
unsigned char i;
  for (i = 0; i < INTERFACES0009_NOMBRE_D_OCTETS_A_TRANSMETTRE; i++)
  {
    serviceProtocole637.octetsATransmettre[i] = interfaceS0009.octetsATransmettre[i];
  }
  serviceProtocole637.nombreATransmettre = INTERFACES0009_NOMBRE_D_OCTETS_A_TRANSMETTRE;
}

void interfaceS0009_gereLaReception(void)
{
  if (serviceProtocole637.information == INFORMATION_TRAITEE)
  {
    return;
  }
  serviceProtocole637.information = INFORMATION_TRAITEE;
  interfaceS0009.information = INFORMATION_DISPONIBLE;
  if (serviceProtocole637.statut != SERVICEPROTOCOLE637_PAS_D_ERREURS)
  {
    interfaceS0009.statut = INTERFACES0009_ERREUR_AU_NIVEAU_DU_PILOTE;
    return;
  }
  interfaceS0009_recupereLesDonneesRecues();
  interfaceS0009.statut = interfaceS0009_valideLaReception();
}

void interfaceS0009_gereLaTransmission(void)
{
  if (serviceProtocole637.requete == REQUETE_ACTIVE)
  {
    return;
  }
  if (interfaceS0009.requete == REQUETE_TRAITEE)
  {
    return;
  }
  interfaceS0009_prepareLaTransmission();  
  serviceProtocole637.requete = REQUETE_ACTIVE;
  interfaceS0009.requete = REQUETE_TRAITEE;
}

//Definitions de variables publiques:
INTERFACES0009 interfaceS0009;

//Definitions de fonctions publiques:
void interfaceS0009_initialise(void)
{
  interfaceS0009.information = INFORMATION_TRAITEE;
  interfaceS0009.requete = REQUETE_TRAITEE;
  serviceBaseDeTemps_execute[INTERFACES0009_PHASE_RECEPTION] =
      interfaceS0009_gereLaReception;
  serviceBaseDeTemps_execute[INTERFACES0009_PHASE_TRANSMISSION] =
      interfaceS0009_gereLaTransmission;
}
