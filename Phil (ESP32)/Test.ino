//Programme: testeServiceBaseDeTemps
//Historique:
// 2020-11-13, Yves Roy, creation

//INCLUSIONS
#include "main.h"
#include "piloteTicker.h"
#include "piloteUART0.h"
//#include "piloteUART2.h"
#include "serviceProtocole637.h"
#include "serviceBaseDeTemps.h"
#include "interfaceSTM.h"

//Definitions privees
#define MAIN_DEL 13
#define MAIN_DEMI_PERIODE_EN_MS 100
#define MAIN_ALLUME 1
#define MAIN_ETEINT 0

//Declarations de fonctions privees:
void main_teste(void);
void main_initialise(void);

//Definitions de variables privees:
unsigned int main_compteur;


//Definitions de fonctions privees:
void main_teste(void)
{
  main_compteur++;
  if (main_compteur < MAIN_DEMI_PERIODE_EN_MS)
  {
    return;
  }
  main_compteur = 0;
  digitalWrite(MAIN_DEL, !digitalRead(MAIN_DEL));
}

void main_initialise(void)
{
  piloteTicker_initialise();
  piloteUART0_initialise();
  piloteUART2_initialise();
  serviceBaseDeTemps_initialise();
  serviceProtocole637_initialise();
  interfaceSTM_initialise();
}

//Definitions de variables publiques:
//pas de variables publiques

//Definitions de fonctions publiques:
void neFaitRien(void)
{
}

void setup()
{
  main_initialise();
  main_compteur = 0;
  digitalWrite(MAIN_DEL, MAIN_ETEINT);
  pinMode(MAIN_DEL, OUTPUT);
  

  serviceBaseDeTemps_execute[MAIN_TEST_PHASE] = neFaitRien;
  piloteTicker_lanceLeTickerALaTouteFinDeSetup();


 /* piloteUART0_transmet('%');
  piloteUART2_transmet('%');
  piloteUART2_transmet('%');
  piloteUART2_transmet('%');
  piloteUART2_transmet('%');
  piloteUART2_transmet('%');
  piloteUART2_transmet('%');*/
}

void loop()
{
    if (serviceProtocole637.requete == REQUETE_TRAITEE)
    {
        serviceProtocole637.requete = REQUETE_ACTIVE;
        delay(200);
    }
    //piloteUART0_transmet(i);
 
    //i = i + 0x01;
}
