// processusBoutonConnecte.c

#include "processusBoutonConnecte.h"

#define PROCESSUSBOUTONCONNECTE_COMPTE_MAXIMAL_POUR_RECEVOIR (\
    (unsigned int)(PROCESSUSBOUTONCONNECTE_TEMPS_MAXIMAL_POUR_RECEVOIR_EN_MS \
    *FREQUENCE_DE_LA_BASE_DE_TEMPS_EN_HZ / 1000.0))

void processusBoutonConnecte_changeT2(void);
void processusBoutonConnecte_attendApresLeBouton(void);
void processusBoutonConnecte_attendUneDemande(void);
void processusBoutonConnecte_attendUneReponse(void);

unsigned char processusBoutonConnecte_etatDeT2;
unsigned char processusBoutonConnecte_compteur;

void processusBoutonConnecte_changeT2(void) {
  if (processusBoutonConnecte_etatDeT2 == 0) {
    processusBoutonConnecte_etatDeT2 = 1;
    interfaceT2_allume();
    return;
  }
  processusBoutonConnecte_etatDeT2 = 0;
  interfaceT2_eteint();  
}

void processusBoutonConnecte_prepareLaTransmission(void) {
  for (unsigned char i = 0; i < INTERFACES0006_NOMBRE_D_OCTETS_A_TRANSMETTRE; i++) {
    interfaceS0006.octetsATransmettre[i] = i;
  }
}

void processusBoutonConnecte_attendApresLeBouton(void) {
  if (interfaceB1.etatDuModule == MODULE_PAS_EN_FONCTION) return;
  serviceBaseDeTemps_execute[PROCESSUSBOUTONCONNECTE_PHASE] =
    processusBoutonConnecte_attendUneDemande;
  processusBoutonConnecte_attendUneDemande(); //on sauve une interruption    
}

void processusBoutonConnecte_attendUneDemande(void) {
  if (interfaceB1.information == INFORMATION_TRAITEE) return;
  interfaceB1.information = INFORMATION_TRAITEE;
  if (interfaceB1.etatDuBouton == INTERFACEB1_RELACHE) return;
  processusBoutonConnecte_compteur = 0;
  interfaceT4_eteint();
  processusBoutonConnecte_prepareLaTransmission();
  interfaceS0006.requete = REQUETE_ACTIVE;
  serviceBaseDeTemps_execute[PROCESSUSBOUTONCONNECTE_PHASE] =
    processusBoutonConnecte_attendUneReponse;
}

void processusBoutonConnecte_attendUneReponse(void) {
  processusBoutonConnecte_compteur++;
  if (processusBoutonConnecte_compteur ==
      PROCESSUSBOUTONCONNECTE_COMPTE_MAXIMAL_POUR_RECEVOIR) {
    processusBoutonConnecte_compteur = 0;
    interfaceT4_allume();
    serviceBaseDeTemps_execute[PROCESSUSBOUTONCONNECTE_PHASE] =
        processusBoutonConnecte_attendUneDemande;
    return;
  }
  if (interfaceS0006.information == INFORMATION_TRAITEE) return;
  interfaceS0006.information = INFORMATION_TRAITEE;
  serviceBaseDeTemps_execute[PROCESSUSBOUTONCONNECTE_PHASE] =
    processusBoutonConnecte_attendUneDemande;
 
  processusBoutonConnecte_changeT2();
  if (interfaceS0006.statut != INTERFACES0006_PAS_D_ERREURS) {
    interfaceT4_allume();
    return;
  }
  if (interfaceS0006.octetRecu == INTERFACES0006_RELACHE) {
    interfaceT3_eteint();
    return;
  }
  interfaceT3_allume();
}

void processusBoutonConnecte_initialise(void) {
  processusBoutonConnecte_compteur = 0;
  processusBoutonConnecte_etatDeT2 = 0;
  interfaceT2_eteint();
  interfaceT3_eteint();
  interfaceT4_eteint();
  serviceBaseDeTemps_execute[PROCESSUSBOUTONCONNECTE_PHASE] =
      processusBoutonConnecte_attendApresLeBouton;
}