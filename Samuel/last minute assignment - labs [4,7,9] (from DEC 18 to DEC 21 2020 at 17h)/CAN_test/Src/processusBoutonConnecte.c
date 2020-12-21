//processusBoutonConnecte:
//Historique: 
// 2018-10-28, Yves Roy, creation

//INCLUSIONS
#include "main.h"
#include "serviceBaseDeTemps.h"
#include "interfaceB1.h"
#include "processusBoutonConnecte.h"
#include "interfaceCAN.h"

//Definitions privees
#define PROCESSUSBOUTONCONNECTE_COMPTE_MAXIMAL_POUR_RECEVOIR (\
    (unsigned int)(PROCESSUSBOUTONCONNECTE_TEMPS_MAXIMAL_POUR_RECEVOIR_EN_MS \
    *FREQUENCE_DE_LA_BASE_DE_TEMPS_EN_HZ / 1000.0))

#define PROCESSUSBOUTONCONNECTE_PAS_D_ERREURS 0
#define PROCESSUSBOUTONCONNECTE_ERREUR 1

//Declarations de fonctions privees:
void processusBoutonConnecte_attendApresLeBouton(void);
void processusBoutonConnecte_attendUneDemande(void);

unsigned char dataOUT[3] = {0x11,0x99,0x01};

void processusBoutonConnecte_attendApresLeBouton(void)
{
  if (interfaceB1.etatDuModule == MODULE_PAS_EN_FONCTION)
  {
    return;
  }
  serviceBaseDeTemps_execute[PROCESSUSBOUTONCONNECTE_PHASE] =
    processusBoutonConnecte_attendUneDemande;
  processusBoutonConnecte_attendUneDemande(); //on sauve une interruption    
}

void processusBoutonConnecte_attendUneDemande(void)
{
  if (interfaceB1.information == INFORMATION_TRAITEE)
  {
    return;
  }
  interfaceB1.information = INFORMATION_TRAITEE;
  if (interfaceB1.etatDuBouton == INTERFACEB1_RELACHE)
  {
    return;
  }
  CAN_Send(0x2, dataOUT, 3);
}

void processusBoutonConnecte_initialise(void)
{
  serviceBaseDeTemps_execute[PROCESSUSBOUTONCONNECTE_PHASE] =
      processusBoutonConnecte_attendApresLeBouton;
}
