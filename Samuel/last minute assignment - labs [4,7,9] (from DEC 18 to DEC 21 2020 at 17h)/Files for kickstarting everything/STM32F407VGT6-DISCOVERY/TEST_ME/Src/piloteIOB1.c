// piloteIOB1.c
#include "piloteIOB1.h"

unsigned char piloteIOB1_litLEntree(void) {
  return HAL_GPIO_ReadPin(PILOTEIOB1_PORT, PILOTEIOB1_ENTREE);
}
