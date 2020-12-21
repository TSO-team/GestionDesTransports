// piloteIOT2.h

#ifndef PILOTEIOT2_H
#define PILOTEIOT2_H
#include "main.h"
// DEFINITIONS REQUISES PAR LE MODULE:
// Dependances materielles
// (copiez et adaptez ce qui suit dans "main.h")
//#define PILOTEIOT2_PORT  LD3_GPIO_Port
//#define PILOTEIOT2_SORTIE  LD3_Pin

void piloteIOT2_initialise(void);
void piloteIOT2_metLaSortieA(unsigned char Valeur);

#endif