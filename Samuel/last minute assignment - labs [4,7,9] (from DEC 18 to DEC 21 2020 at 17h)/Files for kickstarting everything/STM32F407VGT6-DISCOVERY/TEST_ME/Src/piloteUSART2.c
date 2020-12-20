// piloteUSART2.c

/*
#include "piloteUSART2.h"

extern UART_HandleTypeDef huart2; // Defini par le HAL dans main.c

unsigned char piloteUSART2_octetDisponible(void) {
  return __HAL_UART_GET_FLAG(&huart2, UART_FLAG_RXNE);
}

unsigned char piloteUSART2_octetTransmis(void) {
  return __HAL_UART_GET_FLAG(&huart2, UART_FLAG_TC);
}

unsigned char piloteUSART2_litUnOctetRecu(void) {
  return huart2.Instance->DR;

void piloteUSART2_transmet(unsigned char Octet) {
  huart2.Instance->DR = Octet;
}

void piloteUSART2_confirmeLaReception(void) {
  __HAL_UART_CLEAR_FLAG(&huart2, UART_FLAG_RXNE);  
}

void piloteUSART2_confirmeLaFinDeTransmission(void) {
  __HAL_UART_CLEAR_FLAG(&huart2, UART_FLAG_TC);  
}

void piloteUSART2_initialise(void) {
  __HAL_UART_CLEAR_FLAG(&huart2, UART_FLAG_TC);
  __HAL_UART_CLEAR_FLAG(&huart2, UART_FLAG_RXNE);
}
*/





#include "piloteUSART2.h"

extern UART_HandleTypeDef huart2; // Defini par le hal dans main.

unsigned char piloteUSART2_octetDisponible(void) {
  return __HAL_UART_GET_FLAG(&huart2, UART_FLAG_RXNE);
}

unsigned char piloteUSART2_octetTransmis(void) {
  return __HAL_UART_GET_FLAG(&huart2, UART_FLAG_TC);
}

unsigned char piloteUSART2_litUnOctetRecu(void) {
  return huart2.Instance->DR;
}
void piloteUSART2_transmet(unsigned char Octet) {
  huart2.Instance->DR = Octet;
}

void piloteUSART2_confirmeLaReception(void) {
  __HAL_UART_CLEAR_FLAG(&huart2, UART_FLAG_RXNE);  
}

void piloteUSART2_confirmeLaFinDeTransmission(void) {
  __HAL_UART_CLEAR_FLAG(&huart2, UART_FLAG_TC);  
}

void piloteUSART2_initialise(void) {
  __HAL_UART_CLEAR_FLAG(&huart2, UART_FLAG_TC);
  __HAL_UART_CLEAR_FLAG(&huart2, UART_FLAG_RXNE);
}
