//serviceBaseDeTemps:
//Historique: 
// 2018-12-14, Yves Roy, creation

//INCLUSIONS
#include "main.h"
#include "piloteTicker.h"
#include "serviceBaseDeTemps.h"

//Definitions privees
//pas de definitions privees

//Declarations de fonctions privees:
void serviceBaseDeTemps_neFaitRien(void);
void serviceBaseDeTemps_gere(void);

//Definitions de variables privees:
//pas de variables privees

//Definitions de fonctions privees:
void serviceBaseDeTemps_neFaitRien(void)
{
}

void serviceBaseDeTemps_gere(void)
{
unsigned char i;
  for (i = 0; i < SERVICEBASEDETEMPS_NOMBRE_DE_PHASES; i++)
  {
    serviceBaseDeTemps_execute[i]();
  }
}
    
//Definitions de variables publiques:
void (*serviceBaseDeTemps_execute[SERVICEBASEDETEMPS_NOMBRE_DE_PHASES])(void);

//Definitions de fonctions publiques:
void serviceBaseDeTemps_initialise(void)
{
unsigned char i;
  for (i = 0; i < SERVICEBASEDETEMPS_NOMBRE_DE_PHASES; i++)
  {
    serviceBaseDeTemps_execute[i] = serviceBaseDeTemps_neFaitRien;
  }
  piloteTicker_execute = serviceBaseDeTemps_gere;
}
