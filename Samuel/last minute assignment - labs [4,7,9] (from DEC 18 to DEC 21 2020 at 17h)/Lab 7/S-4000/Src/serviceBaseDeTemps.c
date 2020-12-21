// serviceBaseDeTemps.c
#include "serviceBaseDeTemps.h"

void serviceBaseDeTemps_gere(void) {
  for (unsigned char i = 0; i < SERVICEBASEDETEMPS_NOMBRE_DE_PHASES; i++) {
    serviceBaseDeTemps_execute[i]();
  }
}

void serviceBaseDeTemps_initialise(void) {
  for (unsigned char i = 0; i < SERVICEBASEDETEMPS_NOMBRE_DE_PHASES; i++) {
    serviceBaseDeTemps_execute[i] = neFaitRien;
  } piloteTimer6Up_execute = serviceBaseDeTemps_gere;
}
