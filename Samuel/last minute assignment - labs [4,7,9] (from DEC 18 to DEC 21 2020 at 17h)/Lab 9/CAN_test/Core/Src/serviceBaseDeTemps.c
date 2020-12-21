//serviceBaseDeTemps:
//Historique: 
// 2018-09-30, Yves Roy, creation

//INCLUSIONS
#include <piloteTimer6Up.h>
#include <serviceBaseDeTemps.h>
#include "../Inc/main.h"

#define SERVICEBASEDETEMPS_NOMBRE_DE_PHASES 7

//Definitions privees
//pas de definitions privees

//Declarations de fonctions privees:
void serviceBaseDeTemps_gere(void);

//Definitions de variables privees:
//pas de variables privees

//Definitions de fonctions privees:
void serviceBaseDeTemps_gere(void) {
    for (unsigned char i = 0; i < SERVICEBASEDETEMPS_NOMBRE_DE_PHASES; i++)
        serviceBaseDeTemps_execute[i]();
}

//Definitions de variables publiques:
void (*serviceBaseDeTemps_execute[SERVICEBASEDETEMPS_NOMBRE_DE_PHASES])(void);

//Definitions de fonctions publiques:
void serviceBaseDeTemps_initialise(void) {
    for (unsigned char i = 0; i < SERVICEBASEDETEMPS_NOMBRE_DE_PHASES; i++)
        serviceBaseDeTemps_execute[i] = neFaitRien;
    piloteTimer6Up_execute = serviceBaseDeTemps_gere;
}
