//piloteUART0:
//Historique: 
// 2018-09-08, Yves Roy, creation

//INCLUSIONS
#include "main.h"
#include "piloteUART0.h"

//Definitions privees
//pas de definitions privees

//Declarations de fonctions privees:
//pas de fonctions privees

//Definitions de variables privees:
//pas de variables privees

//Definitions de fonctions privees:
//pas de fonctions privees

//Definitions de variables publiques:
// pas de variables publiques

//Definitions de fonctions publiques:
// pas de definitions publiques

//Fonctions publiques:
unsigned char piloteUART0_octetDisponible(void)
{
  return SCON0_bit.RI_0;
}

unsigned char piloteUART0_octetTransmis(void)
{
  return SCON0_bit.TI_0;
}

unsigned char piloteUART0_litUnOctetRecu(void)
{
  return SBUF0;
}
void piloteUART0_transmet(unsigned char Octet)
{
  SBUF0 = Octet;
}

void piloteUART0_confirmeLaReception(void)
{
  SCON0_bit.RI_0 = 0;
}

void piloteUART0_confirmeLaFinDeTransmission(void)
{
  SCON0_bit.TI_0 = 0;  
}

void piloteUART0_initialise(void)
{
  PCON_bit.SMOD0 = 0;
  PCON_bit.SMOD_0 = PILOTETIMER1MODE2_UTILISE_LE_DOUBLEUR_DE_TAUX;
  SCON0_bit.SM0_FE_0 = 0;
  SCON0_bit.SM1_0 = 1;
  SCON0_bit.SM2_0 = 1;
  SCON0_bit.REN_0 = 1;
  SCON0_bit.TI_0 = 0;
  SCON0_bit.RI_0 = 0;
}



