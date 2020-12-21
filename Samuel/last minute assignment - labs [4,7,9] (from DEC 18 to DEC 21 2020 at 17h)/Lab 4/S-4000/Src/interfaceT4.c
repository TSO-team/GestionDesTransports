// interfaceT4.c
#include "interfaceT4.h"

void interfaceT4_allume(void) {
  piloteIOT4_metLaSortieA(INTERFACET4_VALEUR_POUR_ALLUMER);
}

void interfaceT4_eteint(void) {
  piloteIOT4_metLaSortieA(INTERFACET4_VALEUR_POUR_ETEINDRE);
}

void interfaceT4_initialise(void) {
  piloteIOT4_metLaSortieA(INTERFACET4_VALEUR_POUR_ETEINDRE);
}