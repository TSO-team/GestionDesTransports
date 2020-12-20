// piloteIOT3.h

#ifndef PILOTEIOT3_H
#define PILOTEIOT3_H
#include "main.h"
// DEFINITIONS REQUISES PAR LE MODULE:
// Dependances materielles
// (copiez et adaptez ce qui suit dans "main.h")
//#define PILOTEIOT3_PORT  LD4_GPIO_Port
//#define PILOTEIOT3_SORTIE  LD4_Pin

void piloteIOT3_initialise(void);
void piloteIOT3_metLaSortieA(unsigned char Valeur);

#endif