// processusClignotant.c
#include "processusClignotant.h"

unsigned int processusClignotant_compteur;

void processusClignotant_eteintUnPeu(void) {
  processusClignotant_compteur++;
  if (processusClignotant_compteur < PROCESSUSCLIGNOTANT_COMPTE_COURT_ETEINT) return;
  processusClignotant_compteur = 0;
  interfaceT1_allume();
  serviceBaseDeTemps_execute[PROCESSUSCLIGNOTANT_PHASE] =
      processusClignotant_allumeUnPeu;
}

void processusClignotant_allumeUnPeu(void) {
  processusClignotant_compteur++;
  if (processusClignotant_compteur < PROCESSUSCLIGNOTANT_COMPTE_COURT_ALLUME) return;
  processusClignotant_compteur = 0;
  interfaceT1_eteint();
  serviceBaseDeTemps_execute[PROCESSUSCLIGNOTANT_PHASE] =
      processusClignotant_eteintLongtemps;  
}

void processusClignotant_eteintLongtemps(void) {
  processusClignotant_compteur++;
  if (processusClignotant_compteur < PROCESSUSCLIGNOTANT_COMPTE_LONG_ETEINT) return;
  processusClignotant_compteur = 0;
  interfaceT1_allume();
  serviceBaseDeTemps_execute[PROCESSUSCLIGNOTANT_PHASE] =
      processusClignotant_allumeLongtemps;
}

void processusClignotant_allumeLongtemps(void) {
  processusClignotant_compteur++;
  if (processusClignotant_compteur < PROCESSUSCLIGNOTANT_COMPTE_LONG_ALLUME) return;
  processusClignotant_compteur = 0;
  interfaceT1_eteint();
  serviceBaseDeTemps_execute[PROCESSUSCLIGNOTANT_PHASE] =
      processusClignotant_eteintUnPeu;  
}

void processusClignotant_initialise(void) {
  processusClignotant_compteur = 0;
  interfaceT1_eteint();
  serviceBaseDeTemps_execute[PROCESSUSCLIGNOTANT_PHASE] =
      processusClignotant_eteintUnPeu;
}
