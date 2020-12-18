// interfaceS0006.c

#include "interfaceS0006.h"

void interfaceS0006_recupereLesDonneesRecues(void);
unsigned char interfaceS0006_valideLaReception(void);
void interfaceS0006_prepareLaTransmission(void);
void interfaceS0006_gereLaReception(void);
void interfaceS0006_gereLaTransmission(void);

void interfaceS0006_recupereLesDonneesRecues(void) {
  /*
  int octet;
  interfaceS0006.octetRecu = serviceProtocoleCom.octetsRecus[0];
  for (index = 0; index < INTERFACES0006_NOMBRE_D_OCTETS_A_RECEVOIR; index++) {
    octet = serviceProtocoleCom.octetsRecus[index *2 + 1];
    interfaceS0006.entiersRecus[index] = octet << 8;
    interfaceS0006.entiersRecus[index] 
        += serviceProtocoleCom.octetsRecus[index * 2 + 2];

    if (octet > 126) { //conversion int 16 bits pour Dallas à int 32 bits pour STM
      interfaceS0006.entiersRecus[index] |= 0xFFFF0000; //on propage le signe
    }
  }
  */

  interfaceS0006.nombreARecevoir = INTERFACES0006_NOMBRE_D_OCTETS_A_RECEVOIR;
  for (unsigned char i = 0; i < INTERFACES0006_NOMBRE_D_OCTETS_A_RECEVOIR; i++) {
    interfaceS0006.octetsRecus[i] = serviceProtocoleCom.octetsRecus[i];
  }
  
  /*
  interfaceS0006.octetRecu = serviceProtocoleCom.octetsRecus[0];
  for (index = 0; index < INTERFACES0006_NOMBRE_D_OCTETS_A_RECEVOIR; index++) {
    octet = serviceProtocoleCom.octetsRecus[index *2 + 1];
    interfaceS0006.entiersRecus[index] = octet << 8;
    interfaceS0006.entiersRecus[index] 
        += serviceProtocoleCom.octetsRecus[index * 2 + 2];

    if (octet > 126) { //conversion int 16 bits pour Dallas à int 32 bits pour STM
      interfaceS0006.entiersRecus[index] |= 0xFFFF0000; //on propage le signe
    }
  }
  */
}

unsigned char interfaceS0006_valideLaReception(void) {
  if ((interfaceS0006.octetRecu != INTERFACES0006_RELACHE) &&
      (interfaceS0006.octetRecu != INTERFACES0006_APPUYE))
    return INTERFACES0006_ERREUR_OCTET_INVALIDE;
  
  if (interfaceS0006.octetsRecus[0] != 1)
    return INTERFACES0006_ERREUR_ENTIER_0_INVALIDE;
  
  if (interfaceS0006.octetsRecus[1] > 0)
    return INTERFACES0006_ERREUR_ENTIER_1_INVALIDE;
  
  if (interfaceS0006.octetsRecus[2] < 0)
    return INTERFACES0006_ERREUR_ENTIER_2_INVALIDE;

  return INTERFACES0006_PAS_D_ERREURS;
}

void interfaceS0006_prepareLaTransmission(void) {
  serviceProtocoleCom.nombreATransmettre = INTERFACES0006_NOMBRE_D_OCTETS_A_TRANSMETTRE;
  for (unsigned char i = 0; i < INTERFACES0006_NOMBRE_D_OCTETS_A_TRANSMETTRE; i++) {
    serviceProtocoleCom.octetsATransmettre[i] = interfaceS0006.octetsATransmettre[i];
  }
}

void interfaceS0006_gereLaReception(void) {
  if (serviceProtocoleCom.information == INFORMATION_TRAITEE) return;
  serviceProtocoleCom.information = INFORMATION_TRAITEE;
  interfaceS0006.information = INFORMATION_DISPONIBLE;

  if (serviceProtocoleCom.statut != SERVICEPROTOCOLECOM_PAS_D_ERREURS) {
    interfaceS0006.statut = INTERFACES0006_ERREUR_AU_NIVEAU_DU_PILOTE;
    return;
  }
  interfaceS0006_recupereLesDonneesRecues();
  interfaceS0006.statut = interfaceS0006_valideLaReception();
}

void interfaceS0006_gereLaTransmission(void) {
  if (serviceProtocoleCom.requete == REQUETE_ACTIVE) return;
  if (interfaceS0006.requete == REQUETE_TRAITEE) return;
  interfaceS0006_prepareLaTransmission();
  serviceProtocoleCom.requete = REQUETE_ACTIVE;
  interfaceS0006.requete = REQUETE_TRAITEE; // On suppose que pas d'erreurs de TX.
 }

INTERFACES0006 interfaceS0006;

void interfaceS0006_initialise(void) {
  interfaceS0006.information = INFORMATION_TRAITEE;
  interfaceS0006.requete = REQUETE_TRAITEE;
  interfaceS0006.statut = INTERFACES0006_PAS_D_ERREURS;
  
  serviceBaseDeTemps_execute[INTERFACES0006_PHASE_RECEPTION] =
      interfaceS0006_gereLaReception;
  serviceBaseDeTemps_execute[INTERFACES0006_PHASE_TRANSMISSION] =
      interfaceS0006_gereLaTransmission;
}
