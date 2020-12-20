// piloteTimer1Mode2.c

#include "piloteTimer1Mode2.h"

void piloteTimer1Mode2_initialise(void) {
  // Initialise le timer1 en mode 1 pour utiliser le UART0.
  TCON_bit.TR1 = 0; // Arrete le compteur.
  TCON_bit.TF1 = 0; // Efface toutes demandes d'interruptions.
  TMOD_bit.M10 = 0;
  TMOD_bit.M11 = 1;
  TMOD_bit.C_T1 = 0;
  TMOD_bit.GATE1 = 0;
  CKMOD_bit.T1MH = 1;
  CKCON_bit.T1M = 1;

  TL1 = (unsigned char)(PILOTETIMER1MODE2_COMPTE_DE_DEPART);
  TH1 = (unsigned char)(PILOTETIMER1MODE2_COMPTE_DE_DEPART);
  TCON_bit.TR1 = 1; // Lance le compteur.
}



