/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "can.h"
#include "i2c.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <stdio.h>
#include "../Inc/serviceCAN.h"
#include "../Inc/piloteIOT1.h"
#include "../Inc/piloteIOT2.h"
#include "../Inc/piloteIOT3.h"
#include "../Inc/piloteIOT4.h"
#include "../Inc/interfaceT1.h"
#include "../Inc/interfaceT2.h"
#include "../Inc/interfaceT3.h"
#include "../Inc/interfaceT4.h"
#include "../Inc/interfaceCAN.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define MESSAGE_SIZE 5
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
unsigned char dataIN[16] = {'\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0',
                            '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0'};
unsigned char TabOutput[16] = {'\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0',
                               '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0'};
unsigned char dataOUT[16] = {'\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0',
                             '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0'};
unsigned int CallerID, CallerIDOut, Temp;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */
void main_initialiseAvantLeHAL(void);
void main_initialiseApresLeHAL(void);
unsigned char hex2ascii(unsigned char hex);
unsigned char *buffer_hex2ascii(unsigned char *buffer, unsigned char buffer_size);
void (*serviceBaseDeTemps_execute[SERVICEBASEDETEMPS_NOMBRE_DE_PHASES])(void);
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
struct service_CAN_buffer CAN_buffer;
void main_initialiseAvantLeHAL(void) {
  piloteIOT1_initialise();
  piloteIOT2_initialise();
  piloteIOT3_initialise();
  piloteIOT4_initialise();
  interfaceT1_initialise();
  interfaceT2_initialise();
  interfaceT3_initialise();
  interfaceT4_initialise();
}

void main_initialiseApresLeHAL(void) {
  Init_interfaceCAN();
}

void neFaitRien(void) {}
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */
	unsigned char message[MESSAGE_SIZE] = {'A', 'l', 'l', 'o', '\0'};
  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_USART2_UART_Init();
  MX_TIM6_Init();
  MX_CAN1_Init();
  MX_I2C1_Init();
  /* USER CODE BEGIN 2 */
  main_initialiseAvantLeHAL();
  //HAL_GPIO_WritePin(GPIOB, CS0_Pin, GPIO_PIN_RESET); // Verify Cube for reason.
  main_initialiseApresLeHAL();
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1) {
    /* USER CODE END WHILE */
	switch (getchar()) {
	  case 'S':
	  case 's':
	    *TabOutput = message;
	    Temp = TabOutput[0] * 100;
	    Temp += TabOutput[1] * 10;
	    Temp += TabOutput[2];
	    CallerIDOut = Temp;
	    Temp = TabOutput[3]<<4;
	    Temp += TabOutput[4];
	    dataOUT[0] = Temp;
	    Temp = TabOutput[5]<<4;
	    Temp += TabOutput[6];
	    dataOUT[1] = Temp;
	    Temp = TabOutput[7]<<4;
	    Temp += TabOutput[8];
	    dataOUT[2] = Temp;
	    Temp = TabOutput[9]<<4;
	    Temp += TabOutput[10];
	    dataOUT[3] = Temp;
	    CAN_Send(CallerIDOut, dataOUT, 3);
	    break;
	}
	#ifdef DEBUG
	  printf("\nSending CAN message: %s\n", TabOutput);
    #endif
    if (CAN_RX() == 1) {
	  if (CAN_Read(dataIN, &CallerID) == 1) {
	    switch (CallerID) {
	      case ADDRESS_1:
	        CAN_buffer.byte[0] = dataIN[0];
	        CAN_buffer.byte[1] = dataIN[1];
	        CAN_buffer.byte[2] = dataIN[2];
	        CAN_buffer.byte[3] = dataIN[3];
	        printf("\nReceived message from ADDRESS_1: \n", buffer_hex2ascii(CAN_buffer.byte, MESSAGE_SIZE));
	        break;
	      case ADDRESS_2:
	        CAN_buffer.byte[0] = dataIN[0];
	        CAN_buffer.byte[1] = dataIN[1];
	        CAN_buffer.byte[2] = dataIN[2];
	        CAN_buffer.byte[3] = dataIN[3];
	        printf("\nReceived message from ADDRESS_2: \n", buffer_hex2ascii(CAN_buffer.byte, MESSAGE_SIZE));
	        break;
	    }
	  }
    }
    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);
  /** Initializes the CPU, AHB and APB busses clocks
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 4;
  RCC_OscInitStruct.PLL.PLLN = 168;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 7;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB busses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */
unsigned char hex2ascii(unsigned char hex) {
    return hex + (hex > 9 ? 0x37 : 0x30);
}

unsigned char *buffer_hex2ascii(unsigned char *buffer, unsigned char buffer_size) {
    for (unsigned char i = 0; i < buffer_size; i++)
        buffer[i] = hex2ascii(buffer[i]);
    return buffer;
}
/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */

  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
