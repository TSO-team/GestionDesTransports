//piloteTicker:
//Historique: 
// 2020-11-13, Yves Roy, creation

//INCLUSIONS
#include "main.h"
#include <Ticker.h>
#include "piloteTicker.h"

//Definitions privees
//pas de definitions privees

//Declarations de fonctions privees
//pas de fonctions privees

//Definitions de variables privees
Ticker piloteTicker_ticker;

//Definitions de fonctions privees
void piloteTicker_gereLeTicker(void)
{
  piloteTicker_execute();  
}

//Definitions de variables publiques
void (*piloteTicker_execute)(void);

//Definitions de fonctions publiques:
void piloteTicker_lanceLeTickerALaTouteFinDeSetup(void)
{
  piloteTicker_ticker.attach_ms(PILOTETICKER_PERIODE_EN_MS, piloteTicker_gereLeTicker);
}
void piloteTicker_initialise(void)
{  
  piloteTicker_execute = neFaitRien;
}
