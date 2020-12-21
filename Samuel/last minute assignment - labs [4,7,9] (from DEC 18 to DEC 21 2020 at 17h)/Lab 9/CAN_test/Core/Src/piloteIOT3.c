//piloteIOT3:
//Historique: 
// 2018-09-30, Yves Roy, creation

//INCLUSIONS
#include <piloteIOT3.h>
#include "../Inc/main.h"

//Definitions privees
//pas de d�finitions privees

//Declarations de fonctions privees:
//pas de fonction privees

//Definitions de variables privees:
//pas de variables privees

//Definitions de fonctions privees:
//pas de fonctions privees

//Definitions de variables publiques:
// pas de variables publiques

//Definitions de fonctions publiques:
void piloteIOT3_metLaSortieA(unsigned char Valeur) {
    HAL_GPIO_WritePin(PILOTEIOT3_PORT, PILOTEIOT3_SORTIE, (GPIO_PinState)Valeur);  
}

void piloteIOT3_initialise(void) {
    HAL_GPIO_WritePin(PILOTEIOT3_PORT, PILOTEIOT3_SORTIE, GPIO_PIN_RESET);  
}
