// interfaceB1.c

#include "interfaceB1.h"

unsigned int compteurAvantLecture;
unsigned int compteurAntiRebond;

void interfaceB1_gere(void) {
  compteurAvantLecture++;
  if (compteurAvantLecture < INTERFACEB1_COMPTE_MAXIMUM_AVANT_LECTURE) return;
  compteurAvantLecture = 0;
  if (piloteIOB1_litLEntree() == INTERFACEB1_VALEUR_LUE_SI_APPUYE) {
    if (compteurAntiRebond == INTERFACEB1_NOMBRE_MINIMUM_DE_LECTURES_PAR_DECISION)
		return;
    compteurAntiRebond++;
    if (compteurAntiRebond < INTERFACEB1_NOMBRE_MINIMUM_DE_LECTURES_PAR_DECISION)
		return;
    interfaceB1.etatDuModule = MODULE_EN_FONCTION;
    interfaceB1.etatDuBouton = INTERFACEB1_APPUYE;
    interfaceB1.information = INFORMATION_DISPONIBLE;       
    return;
  }
  if (compteurAntiRebond == 0) return;
  compteurAntiRebond--;
  if (compteurAntiRebond > 0) return;
  interfaceB1.etatDuModule = MODULE_EN_FONCTION;  
  interfaceB1.etatDuBouton = INTERFACEB1_RELACHE;
  interfaceB1.information = INFORMATION_DISPONIBLE;
}

INTERFACEB1 interfaceB1;

void interfaceB1_initialise(void) {
  interfaceB1.etatDuModule = MODULE_PAS_EN_FONCTION;
  interfaceB1.information = INFORMATION_TRAITEE;
  interfaceB1.etatDuBouton = INTERFACEB1_INCONNU;
  compteurAvantLecture = 0;
  compteurAntiRebond = INTERFACEB1_COMPTE_INITIAL;
  serviceBaseDeTemps_execute[INTERFACEB1_PHASE] = interfaceB1_gere;
}