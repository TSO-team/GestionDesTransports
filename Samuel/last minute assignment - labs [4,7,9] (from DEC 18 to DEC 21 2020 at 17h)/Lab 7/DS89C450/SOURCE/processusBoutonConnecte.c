//processusBoutonConnecte:
//Historique: 
// 2019-10-27, Yves Roy, creation

//INCLUSIONS
#include "main.h"
#include "serviceBaseDeTemps.h"
#include "interfaceB1.h"
#include "interfaceS0009.h"
#include "processusBoutonConnecte.h"

//Definitions privees
#define PROCESSUSBOUTONCONNECTE_NOMBRE_D_OCTETS_A_RECEVOIR INTERFACES0009_NOMBRE_D_OCTETS_A_RECEVOIR
#define PROCESSUSBOUTONCONNECTE_NOMBRE_D_OCTETS_A_TRAITER PROCESSUSBOUTONCONNECTE_NOMBRE_D_OCTETS_A_RECEVOIR
#define PROCESSUSBOUTONCONNECTE_NOMBRE_D_OCTETS_A_TRANSMETTRE PROCESSUSBOUTONCONNECTE_NOMBRE_D_OCTETS_A_TRAITER


//Declarations de fonctions privees:
void processusBoutonConnecte_recupereLesValeursRecues(void);
void processusBoutonConnecte_traiteUneDemande(void);
void processusBoutonConnecte_prepareLaTransmission(void);
void processusBoutonConnecte_attendApresInterfaceB1(void);
void processusBoutonConnecte_gere(void);

//Definitions de variables privees:
unsigned char processusBoutonConnecte_octetsTraites[PROCESSUSBOUTONCONNECTE_NOMBRE_D_OCTETS_A_TRAITER];
unsigned char processusBoutonConnecte_reponse;

//Definitions de fonctions privees:
void processusBoutonConnecte_recupereLesValeursRecues(void)
{
  unsigned char i;
  for (i = 0; i < PROCESSUSBOUTONCONNECTE_NOMBRE_D_OCTETS_A_RECEVOIR; i++)
  {
    processusBoutonConnecte_octetsTraites[i] = interfaceS0009.octetsRecus[i];
  }
}

void processusBoutonConnecte_traiteUneDemande(void)
{
unsigned char i;
  for (i = 0; i < PROCESSUSBOUTONCONNECTE_NOMBRE_D_OCTETS_A_TRAITER; i++)
  {
    processusBoutonConnecte_octetsTraites[i] *= 2;
  }
}

void processusBoutonConnecte_prepareLaTransmission(void)
{
unsigned char i;
  for (i = 0; i < PROCESSUSBOUTONCONNECTE_NOMBRE_D_OCTETS_A_TRANSMETTRE; i++)
  {
    interfaceS0009.octetsATransmettre[i] = processusBoutonConnecte_octetsTraites[i];
  }
}

void processusBoutonConnecte_attendApresInterfaceB1(void)
{
  if (interfaceB1.etatDuModule == MODULE_PAS_EN_FONCTION)
  {
    return;
  }
  processusBoutonConnecte.etatDuModule = MODULE_EN_FONCTION;  
  serviceBaseDeTemps_execute[PROCESSUSBOUTONCONNECTE_PHASE] =
      processusBoutonConnecte_gere;
}

void processusBoutonConnecte_gere(void)
{  
  if (interfaceS0009.information == INFORMATION_TRAITEE)
  {
    return;
  }
  interfaceS0009.information = INFORMATION_TRAITEE;
  processusBoutonConnecte_recupereLesValeursRecues();
  processusBoutonConnecte_traiteUneDemande();
  processusBoutonConnecte_prepareLaTransmission();
  interfaceS0009.requete = REQUETE_ACTIVE;
}

//Definitions de variables publiques:
PROCESSUSBOUTONCONNECTE processusBoutonConnecte;

//Definitions de fonctions publiques:
void processusBoutonConnecte_initialise(void)
{
  processusBoutonConnecte.etatDuModule = MODULE_PAS_EN_FONCTION;
  serviceBaseDeTemps_execute[PROCESSUSBOUTONCONNECTE_PHASE] =
      processusBoutonConnecte_attendApresInterfaceB1;
}
