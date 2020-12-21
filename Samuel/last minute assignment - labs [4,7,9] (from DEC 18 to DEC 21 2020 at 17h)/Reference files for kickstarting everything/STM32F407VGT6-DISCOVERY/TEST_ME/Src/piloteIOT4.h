// piloteIOT4.h

#ifndef PILOTEIOT4_H
#define PILOTEIOT4_H
#include "main.h"
// MODULE: piloteIOT1
// DESCRIPTION: pour commander la sortie IOT1

// DEFINITIONS REQUISES PAR LE MODULE:
// Dependances materielles
// (copiez et adaptez ce qui suit dans "main.h")
//#define PILOTEIOT4_PORT  LD5_GPIO_Port
//#define PILOTEIOT4_SORTIE  LD5_Pin

void piloteIOT4_initialise(void);
void piloteIOT4_metLaSortieA(unsigned char Valeur);

#endif
