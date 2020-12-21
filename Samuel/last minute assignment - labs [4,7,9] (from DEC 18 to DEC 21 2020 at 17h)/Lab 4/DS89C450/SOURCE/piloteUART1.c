//piloteUART1:
//Historique: 
// 2018-09-08, Yves Roy, creation

//INCLUSIONS
#include "main.h"
#include "piloteUART1.h"

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
unsigned char piloteUART1_octetDisponible(void)
{
  return SCON1_bit.RI_1;
}

unsigned char piloteUART1_octetTransmis(void)
{
  return SCON1_bit.TI_1;
}

unsigned char piloteUART1_litUnOctetRecu(void)
{
  return SBUF1;
}
void piloteUART1_transmet(unsigned char Octet)
{
  SBUF1 = Octet;
}

void piloteUART1_confirmeLaReception(void)
{
  SCON1_bit.RI_1 = 0;
}

void piloteUART1_confirmeLaFinDeTransmission(void)
{
  SCON1_bit.TI_1 = 0;  
}

void piloteUART1_initialise(void)
{
  P1_bit.P12_RXD1 = 1;
  PCON_bit.SMOD0 = 0;
  WDCON_bit.SMOD_1 = PILOTETIMER1MODE2_UTILISE_LE_DOUBLEUR_DE_TAUX;
  SCON1_bit.SM0_FE_1 = 0;
  SCON1_bit.SM1_1 = 1;
  SCON1_bit.SM2_1 = 1;
  SCON1_bit.REN_1 = 1;
  SCON1_bit.TI_1 = 0;
  SCON1_bit.RI_1 = 0;
}



