// piloteUSART2.h

#ifndef PILOTEUSART2_H
#define PILOTEUSART2_H

#include "main.h"

#define PILOTEUSART2_DISPONIBLE  1
#define PILOTEUSART2_PAS_DISPONIBLE 0
#define PILOTEUSART2_TRANSMIS 0
#define PILOTEUSART2_PAS_TRANSMIS 1

void piloteUSART2_initialise(void);
unsigned char piloteUSART2_octetDisponible(void);
unsigned char piloteUSART2_octetTransmis(void);
unsigned char piloteUSART2_litUnOctetRecu(void);
void piloteUSART2_confirmeLaReception(void);
void piloteUSART2_confirmeLaFinDeTransmission(void);
void piloteUSART2_transmet(unsigned char);

#endif