//247-637 S0006:
//Historique: 
// 2019-10-27, Yves Roy, creation

//INCLUSIONS
#include "main.h"
#include "piloteIOT1.h"
#include "piloteIOB1.h"
#include "piloteTimer2AutoReload.h"
#include "piloteTimer1Mode2.h"
#include "piloteUART0.h"
#include "piloteUART1.h"
#include "serviceBaseDeTemps.h"
#include "serviceProtocole637.h"
#include "interfaceB1.h"
#include "interfaceS0009.h"
#include "interfaceT1.h"
#include "processusBoutonConnecte.h"
#include "processusClignotant.h"

//Definitions privees
//pas de définitions privees

//Declarations de fonctions privees:
void main_initialise(void)
{
  piloteIOT1_initialise();
  piloteIOB1_initialise();
  piloteTimer2AutoReload_initialise();
  piloteTimer1Mode2_initialise();
  piloteUART0_initialise();
  piloteUART1_initialise();
  serviceBaseDeTemps_initialise();
  serviceProtocole637_initialise();
  interfaceB1_initialise();
  interfaceS0009_initialise();
  interfaceT1_initialise();
  processusBoutonConnecte_initialise();
  processusClignotant_initialise();
}

//Definitions de variables privees:
//pas de variables privees

//Definitions de fonctions privees:
//pas de fonctions privees

//Definitions de variables publiques:
//pas de variables publiques

//Definitions de fonctions publiques:
void neFaitRien(void)
{
}

void main(void)
{
  IE_bit.EA = 0; //empêche les interruptions (déjà interdites au reset)

  main_initialise();

  IE_bit.EA = 1; //permet les interruptions
  
  while (1)
  {
//    for (volatile unsigned int toto = 0; toto < 150; toto++)
//    {
//    }
//    piloteTimer2AutoReload_execute();
//    serviceBaseDeTemps_gere();
  }
}
