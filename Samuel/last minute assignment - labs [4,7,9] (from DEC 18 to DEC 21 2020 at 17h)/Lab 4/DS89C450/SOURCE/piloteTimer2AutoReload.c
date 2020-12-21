//piloteTimer2AutoReload:
//Historique: 
// 2018-09-08, Yves Roy, creation

//INCLUSIONS
#include "main.h"
#include "piloteTimer2AutoReload.h"

//Definitions privees
#define PILOTETIMER2AUTORELOAD_COMPTE_DE_DEPART  (\
  (unsigned int)(65536.0-(MAIN_FREQUENCE_D_OSCILLATEUR_EN_KHZ \
  /FREQUENCE_DE_LA_BASE_DE_TEMPS_EN_HZ * 1000.0)))

//Declarations de fonctions privees:
__interrupt void PiloteTimer2Autoreload_interruption(void);

//Definitions de variables privees:
//pas de variables privees

//Definitions de fonctions privees:
//pas de fonctions privees

//Definitions de variables publiques:
void (*piloteTimer2AutoReload_execute)(void);

//Definitions de fonctions publiques:
#pragma vector = 0x2B //yr 5
__interrupt void PiloteTimer2Autoreload_interruption(void) //définition
{
  piloteTimer2AutoReload_execute();
  T2CON_bit.TF2 = 0;
}

void piloteTimer2AutoReload_initialise(void)
{
  IE_bit.ET2 = 0; //empêche les interruptions par timer2  
  T2CON_bit.TR2 = 0; // arrête le timer2
  T2CON_bit.TF2 = 0;
  T2CON_bit.EXF2 = 0;
  T2CON_bit.RCLK = 0;
  T2CON_bit.TCLK = 0;
  T2CON_bit.EXEN2 = 0;
  T2CON_bit.TR2 = 0;
  T2CON_bit.C_T2 = 0;
  T2CON_bit.CP_RL2 = 0;
  T2MOD_bit.DCEN = 0;
  T2MOD_bit.T2OE = 0;
  CKCON_bit.T2M = 1;
  CKMOD_bit.T2MH = 1; 
  RCAP2L = (unsigned char)(PILOTETIMER2AUTORELOAD_COMPTE_DE_DEPART & 0xFF);
  RCAP2H = (unsigned char)(PILOTETIMER2AUTORELOAD_COMPTE_DE_DEPART >> 8);

  piloteTimer2AutoReload_execute = neFaitRien;  
  
  IE_bit.ET2 = 1; //permet les interruptions par timer2
  T2CON_bit.TR2 = 1; //lance le compteur Timer2

}



