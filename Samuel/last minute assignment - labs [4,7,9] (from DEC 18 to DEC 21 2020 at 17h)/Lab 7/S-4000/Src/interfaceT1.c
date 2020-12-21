// interfaceT1.c
#include "interfaceT1.h"

void interfaceT1_allume(void) {
  piloteIOT1_metLaSortieA(INTERFACET1_VALEUR_POUR_ALLUMER);
}

void interfaceT1_eteint(void) {
  piloteIOT1_metLaSortieA(INTERFACET1_VALEUR_POUR_ETEINDRE);
}

void interfaceT1_initialise(void) {
  piloteIOT1_metLaSortieA(INTERFACET1_VALEUR_POUR_ETEINDRE);
}