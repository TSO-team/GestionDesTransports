/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2019 STMicroelectronics.
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
//PROGRAMME: 247-637 S-0009
//DESCRIPTION: programme qui va de pair avec S-0008
//HISTORIQUE:
// 2019-10-27, Yves Roy: création
#include "stm32f4xx_hal.h"


/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define CS_I2C_SPI_Pin GPIO_PIN_3
#define CS_I2C_SPI_GPIO_Port GPIOE
#define PC14_OSC32_IN_Pin GPIO_PIN_14
#define PC14_OSC32_IN_GPIO_Port GPIOC
#define PC15_OSC32_OUT_Pin GPIO_PIN_15
#define PC15_OSC32_OUT_GPIO_Port GPIOC
#define PH0_OSC_IN_Pin GPIO_PIN_0
#define PH0_OSC_IN_GPIO_Port GPIOH
#define PH1_OSC_OUT_Pin GPIO_PIN_1
#define PH1_OSC_OUT_GPIO_Port GPIOH
#define OTG_FS_PowerSwitchOn_Pin GPIO_PIN_0
#define OTG_FS_PowerSwitchOn_GPIO_Port GPIOC
#define PDM_OUT_Pin GPIO_PIN_3
#define PDM_OUT_GPIO_Port GPIOC
#define B1_Pin GPIO_PIN_0
#define B1_GPIO_Port GPIOA
#define I2S3_WS_Pin GPIO_PIN_4
#define I2S3_WS_GPIO_Port GPIOA
#define SPI1_SCK_Pin GPIO_PIN_5
#define SPI1_SCK_GPIO_Port GPIOA
#define SPI1_MISO_Pin GPIO_PIN_6
#define SPI1_MISO_GPIO_Port GPIOA
#define SPI1_MOSI_Pin GPIO_PIN_7
#define SPI1_MOSI_GPIO_Port GPIOA
#define RD_Pin GPIO_PIN_0
#define RD_GPIO_Port GPIOB
#define A4_Pin GPIO_PIN_1
#define A4_GPIO_Port GPIOB
#define BOOT1_Pin GPIO_PIN_2
#define BOOT1_GPIO_Port GPIOB
#define D0_Pin GPIO_PIN_8
#define D0_GPIO_Port GPIOE
#define D1_Pin GPIO_PIN_9
#define D1_GPIO_Port GPIOE
#define D2_Pin GPIO_PIN_10
#define D2_GPIO_Port GPIOE
#define D3_Pin GPIO_PIN_11
#define D3_GPIO_Port GPIOE
#define D4_Pin GPIO_PIN_12
#define D4_GPIO_Port GPIOE
#define D5_Pin GPIO_PIN_13
#define D5_GPIO_Port GPIOE
#define D6_Pin GPIO_PIN_14
#define D6_GPIO_Port GPIOE
#define D7_Pin GPIO_PIN_15
#define D7_GPIO_Port GPIOE
#define CLK_IN_Pin GPIO_PIN_10
#define CLK_IN_GPIO_Port GPIOB
#define CS0_Pin GPIO_PIN_11
#define CS0_GPIO_Port GPIOB
#define CS1_Pin GPIO_PIN_12
#define CS1_GPIO_Port GPIOB
#define CS2_Pin GPIO_PIN_13
#define CS2_GPIO_Port GPIOB
#define CS3_Pin GPIO_PIN_14
#define CS3_GPIO_Port GPIOB
#define A0_Pin GPIO_PIN_8
#define A0_GPIO_Port GPIOD
#define A1_Pin GPIO_PIN_9
#define A1_GPIO_Port GPIOD
#define A2_Pin GPIO_PIN_10
#define A2_GPIO_Port GPIOD
#define A3_Pin GPIO_PIN_11
#define A3_GPIO_Port GPIOD
#define LD4_Pin GPIO_PIN_12
#define LD4_GPIO_Port GPIOD
#define LD3_Pin GPIO_PIN_13
#define LD3_GPIO_Port GPIOD
#define LD5_Pin GPIO_PIN_14
#define LD5_GPIO_Port GPIOD
#define LD6_Pin GPIO_PIN_15
#define LD6_GPIO_Port GPIOD
#define I2S3_MCK_Pin GPIO_PIN_7
#define I2S3_MCK_GPIO_Port GPIOC
#define VBUS_FS_Pin GPIO_PIN_9
#define VBUS_FS_GPIO_Port GPIOA
#define OTG_FS_ID_Pin GPIO_PIN_10
#define OTG_FS_ID_GPIO_Port GPIOA
#define OTG_FS_DM_Pin GPIO_PIN_11
#define OTG_FS_DM_GPIO_Port GPIOA
#define OTG_FS_DP_Pin GPIO_PIN_12
#define OTG_FS_DP_GPIO_Port GPIOA
#define SWDIO_Pin GPIO_PIN_13
#define SWDIO_GPIO_Port GPIOA
#define SWCLK_Pin GPIO_PIN_14
#define SWCLK_GPIO_Port GPIOA
#define I2S3_SCK_Pin GPIO_PIN_10
#define I2S3_SCK_GPIO_Port GPIOC
#define I2S3_SD_Pin GPIO_PIN_12
#define I2S3_SD_GPIO_Port GPIOC
#define Audio_RST_Pin GPIO_PIN_4
#define Audio_RST_GPIO_Port GPIOD
#define OTG_FS_OverCurrent_Pin GPIO_PIN_5
#define OTG_FS_OverCurrent_GPIO_Port GPIOD
#define SWO_Pin GPIO_PIN_3
#define SWO_GPIO_Port GPIOB
#define Audio_SCL_Pin GPIO_PIN_6
#define Audio_SCL_GPIO_Port GPIOB
#define INT_KEY_Pin GPIO_PIN_8
#define INT_KEY_GPIO_Port GPIOB
#define INT_KEY_EXTI_IRQn EXTI9_5_IRQn
#define Audio_SDA_Pin GPIO_PIN_9
#define Audio_SDA_GPIO_Port GPIOB
#define MEMS_INT2_Pin GPIO_PIN_1
#define MEMS_INT2_GPIO_Port GPIOE
/* USER CODE BEGIN Private defines */

//DEFINITIONS REQUISES PAR LE PROGRAMME:
//Dépendances matérielles:
#define FREQUENCE_D_OSCILLATEUR_EN_KHZ  84000.0
#define PILOTEIOT1_PORT  LD6_GPIO_Port
#define PILOTEIOT1_SORTIE  LD6_Pin
#define PILOTEIOT2_PORT  LD6_GPIO_Port
#define PILOTEIOT2_SORTIE  LD3_Pin
#define PILOTEIOT3_PORT LD4_GPIO_Port
#define PILOTEIOT3_SORTIE  LD4_Pin
#define PILOTEIOT4_PORT LD5_GPIO_Port
#define PILOTEIOT4_SORTIE  LD5_Pin
#define INTERFACEB1_DELAI_ANTI_REBOND_EN_MS  15
#define INTERFACET1_VALEUR_POUR_ALLUMER  1
#define INTERFACET1_VALEUR_POUR_ETEINDRE 0
#define INTERFACET2_VALEUR_POUR_ALLUMER  1
#define INTERFACET2_VALEUR_POUR_ETEINDRE 0
#define INTERFACET3_VALEUR_POUR_ALLUMER  1
#define INTERFACET3_VALEUR_POUR_ETEINDRE 0
#define INTERFACET4_VALEUR_POUR_ALLUMER  1
#define INTERFACET4_VALEUR_POUR_ETEINDRE 0

#define ADRS_COM        1
#define ADRS_TRI        2
#define ADRS_TRUCK      3
#define ADRS_PESE       4


//INFORMATION PUBLIQUE:
//Definitions publiques:
#define INFORMATION_DISPONIBLE  1
#define INFORMATION_TRAITEE  0
#define REQUETE_ACTIVE  1
#define REQUETE_TRAITEE 0
#define MODULE_EN_FONCTION 1
#define MODULE_PAS_EN_FONCTION 0

//Fonctions publiques:
void neFaitRien(void);

//Variables publiques:
//copiez et adaptes les lignes qui suivent dans les fichiers .h des modules
//qui utilisent ces variables qui sont definies par htim6
//extern TIM_HandleTypeDef htim6;
//extern UART_HandleTypeDef huart2;

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
