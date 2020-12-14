//interfaceSTM:
//Historique: 
// 2018-10-28, Yves Roy, creation

//INCLUSIONS
#include "main.h"
#ifdef SERVICEPROTOCOLE637_DEBUG
  #include "piloteUART0.h"
#endif
#include "piloteUART0.h"
#include "piloteUART2.h"
#include "serviceBaseDeTemps.h"
#include "serviceProtocole637.h"
#include "interfaceSTM.h"

//Definitions privees
//pas de définitions privees

//Declarations de fonctions privees:
void interfaceSTM_recupereLesDonneesRecues(void);
unsigned char interfaceSTM_valideLaReception(void);
void interfaceSTM_prepareLaTransmission(void);
void interfaceSTM_gereLaReception(void);
void interfaceSTM_gereLaTransmission(void);

//Definitions de variables privees:
unsigned char interfaceSTM_octetsTraites[INTERFACESTM_NOMBRE_D_OCTETS_A_RECEVOIR];

//Definitions de fonctions privees:
void interfaceSTM_recupereLesDonneesRecues(void)
{
unsigned char i;
  for (i = 0; i < INTERFACESTM_NOMBRE_D_OCTETS_A_RECEVOIR; i++)
  {
    interfaceSTM.octetsRecus[i] = serviceProtocole637.octetsRecus[i];
  }
}

unsigned char interfaceSTM_valideLaReception(void)
{
unsigned char i;
  for (i = 0; i < INTERFACESTM_NOMBRE_D_OCTETS_A_RECEVOIR; i++)
  {
    if (interfaceSTM.octetsRecus[i] != i)
    {
      return INTERFACESTM_ERREUR_OCTET_INVALIDE;
    }
  }  
  return INTERFACESTM_PAS_D_ERREURS;
}

void interfaceSTM_prepareLaTransmission(void)
{
unsigned char i;
  for (i = 0; i < INTERFACESTM_NOMBRE_D_OCTETS_A_TRANSMETTRE; i++)
  {
    //interfaceSTM.octetsATransmettre[i] = 0x01;
    serviceProtocole637.octetsATransmettre[i] = interfaceSTM.octetsATransmettre[i];
  }
  serviceProtocole637.nombreATransmettre = INTERFACESTM_NOMBRE_D_OCTETS_A_TRANSMETTRE;
}

void interfaceSTM_gereLaReception(void)
{
  if (serviceProtocole637.information == INFORMATION_TRAITEE)
  {
    return;
  }
  serviceProtocole637.information = INFORMATION_TRAITEE;
  interfaceSTM.information = INFORMATION_DISPONIBLE;
  if (serviceProtocole637.statut != SERVICEPROTOCOLE637_PAS_D_ERREURS)
  {
    interfaceSTM.statut = INTERFACESTM_ERREUR_AU_NIVEAU_DU_PILOTE;
    return;
  }
  interfaceSTM_recupereLesDonneesRecues();
  interfaceSTM.statut = interfaceSTM_valideLaReception();
}

void interfaceSTM_gereLaTransmission(void)
{
  if (serviceProtocole637.requete == REQUETE_ACTIVE)
  {
    return;
  }
  if (interfaceSTM.requete == REQUETE_TRAITEE)
  {
    return;
  }
  interfaceSTM_prepareLaTransmission();  
  serviceProtocole637.requete = REQUETE_ACTIVE;
  interfaceSTM.requete = REQUETE_TRAITEE;
}

//Definitions de variables publiques:
INTERFACESTM interfaceSTM;

//Definitions de fonctions publiques:
void interfaceSTM_initialise(void)
{
  interfaceSTM.information = INFORMATION_TRAITEE;
  interfaceSTM.requete = REQUETE_TRAITEE;
  serviceBaseDeTemps_execute[INTERFACESTM_PHASE_RECEPTION] =
      interfaceSTM_gereLaReception;
  serviceBaseDeTemps_execute[INTERFACESTM_PHASE_TRANSMISSION] =
      interfaceSTM_gereLaTransmission;
}
