//piloteUART2:
//Historique: 
// 2018-09-08, Yves Roy, creation

//INCLUSIONS
#include "main.h"
#include "piloteUART2.h"

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
unsigned char piloteUART2_octetDisponible(void)
{
	Serial2.available();
}

unsigned char piloteUART2_octetTransmis(void)
{
	Serial2.availableForWrite();
}

unsigned char piloteUART2_litUnOctetRecu(void)
{
	return Serial2.read();
}

void piloteUART2_transmet(unsigned char Octet)
{
	Serial2.write (Octet);
}

void piloteUART2_confirmeLaReception(void)
{
	//SCON0_bit.RI_0 = 0;
}

void piloteUART2_confirmeLaFinDeTransmission(void)
{
	//SCON0_bit.TI_0 = 0;
}

void piloteUART2_initialise(void)
{
	Serial2.begin(19200);
	//PCON_bit.SMOD0 = 0;
	//PCON_bit.SMOD_0 = //PILOTETIMER1MODE2_UTILISE_LE_DOUBLEUR_DE_TAUX;
	//SCON0_bit.SM0_FE_0 = 0;
	//SCON0_bit.SM1_0 = 1;
	//SCON0_bit.SM2_0 = 1;
	//SCON0_bit.REN_0 = 1;
	//SCON0_bit.TI_0 = 0;
	//SCON0_bit.RI_0 = 0;
}

