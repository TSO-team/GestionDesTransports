// main.h

// Notes sur l'utilisation des timers.
// https://www.st.com/content/ccc/resource/technical/document/application_note/group0/91/01/84/3f/7c/67/41/3f/DM00236305/files/DM00236305.pdf/jcr:content/translations/en.DM00236305.pdf
// https://stm32f4-discovery.net/2014/05/stm32f4-stm32f429-discovery-pwm-tutorial/
// timer 6 sur APB1
// timer_tick_frequency = Timer_default_frequency / (prescaller_set + 1) 
// default_frequency = 84MHz compte tenu des options choisies avec le "cube"
// TIM_Period = timer_tick_frequency / TIM_frequency - 1
// il faut s'assurer que le compte pour la periode est plus petit que 65536

//usart2
//tx pa2
//rx pa3

#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

#include "stm32f4xx_hal.h"

#define SERVICEBASEDETEMPS_NOMBRE_DE_PHASES 5
#define SERVICEPROTOCOLECOM_PHASE_RECEPTION 2
#define SERVICEPROTOCOLECOM_PHASE_TRANSMISSION 3
#define SERVICEPROTOCOLECOM_FREQUENCE_MAXIMALE_DES_TRANSMISSIONS_EN_HZ 500.0
#define SERVICEPROTOCOLECOM_NOMBRE_DE_DONNEES_MAXIMUM  16
#define SERVICEPROTOCOLECOM_DEBUT_DE_TRAME '$'
#define SERVICEPROTOCOLECOM_INSERTION 0x00
#define SERVICEPROTOCOLECOM_TEMPS_D_ATTENTE_MAXIMAL_EN_MS 4
#define SERVICEPROTOCOLECOM_FREQUENCE_MAXIMALE_DES_LECTURES_EN_HZ 2000.00

#define PROCESSUSBOUTONCONNECTE_TEMPS_MAXIMAL_POUR_RECEVOIR_EN_MS 100
#define PROCESSUSBOUTONCONNECTE_PHASE 1

#define PROCESSUSCLIGNOTANT_PHASE 0
#define PROCESSUSCLIGNOTANT_TEMPS_COURT_ETEINT_EN_MS 500
#define PROCESSUSCLIGNOTANT_TEMPS_COURT_ALLUME_EN_MS 500
#define PROCESSUSCLIGNOTANT_TEMPS_LONG_ETEINT_EN_MS 500
#define PROCESSUSCLIGNOTANT_TEMPS_LONG_ALLUME_EN_MS 500
#define PROCESSUSCLIGNOTANT_COMPTE_COURT_ETEINT (\
  PROCESSUSCLIGNOTANT_TEMPS_COURT_ETEINT_EN_MS * FREQUENCE_DE_LA_BASE_DE_TEMPS_EN_HZ \
  / 1000.0)
#define PROCESSUSCLIGNOTANT_COMPTE_COURT_ALLUME (\
  PROCESSUSCLIGNOTANT_TEMPS_COURT_ALLUME_EN_MS * FREQUENCE_DE_LA_BASE_DE_TEMPS_EN_HZ \
  / 1000.0)
#define PROCESSUSCLIGNOTANT_COMPTE_LONG_ETEINT (\
  PROCESSUSCLIGNOTANT_TEMPS_LONG_ETEINT_EN_MS * FREQUENCE_DE_LA_BASE_DE_TEMPS_EN_HZ \
  / 1000.0)
#define PROCESSUSCLIGNOTANT_COMPTE_LONG_ALLUME (\
  PROCESSUSCLIGNOTANT_TEMPS_LONG_ALLUME_EN_MS * FREQUENCE_DE_LA_BASE_DE_TEMPS_EN_HZ \
  / 1000.0)

#define PILOTEIOB1_PORT B1_GPIO_Port
#define PILOTEIOB1_ENTREE B1_Pin

#define INTERFACET1_VALEUR_POUR_ALLUMER 1   
#define INTERFACET1_VALEUR_POUR_ETEINDRE 0
#define INTERFACET2_VALEUR_POUR_ALLUMER 1
#define INTERFACET2_VALEUR_POUR_ETEINDRE 0
#define INTERFACET3_VALEUR_POUR_ALLUMER 1
#define INTERFACET3_VALEUR_POUR_ETEINDRE 0
#define INTERFACET4_VALEUR_POUR_ALLUMER 1
#define INTERFACET4_VALEUR_POUR_ETEINDRE 0

#define INTERFACEB1_PHASE 4
#define INTERFACEB1_VALEUR_LUE_SI_APPUYE  1   
#define INTERFACEB1_VALEUR_LUE_SI_RELACHE 0
#define INTERFACEB1_FREQUENCE_DES_LECTURES_EN_HZ  100
#define INTERFACEB1_NOMBRE_MINIMUM_DE_LECTURES_PAR_DECISION 10

#define INTERFACES0006_PHASE_RECEPTION 0
#define INTERFACES0006_PHASE_TRANSMISSION 1
#define INTERFACES0006_OCTET_A_TRANSMETTRE 0x5A
#define INTERFACES0006_NOMBRE_D_ENTIERS_A_RECEVOIR 3

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "interfaceT1.h"
#include "serviceBaseDeTemps.h"
#include "processusClignotant.h"
#include "piloteTimer6Up.h"
#include "piloteIOT1.h"
#include "piloteIOT2.h"
#include "piloteIOT3.h"
#include "piloteIOT4.h"
#include "piloteIOB1.h"

#include "piloteUSART2.h"
#include "serviceProtocoleCom.h"
#include "interfaceB1.h"
#include "interfaceT1.h"
#include "interfaceT2.h"
#include "interfaceT3.h"
#include "interfaceT4.h"
#include "interfaceS0006.h"
#include "processusBoutonConnecte.h"

#define FREQUENCE_D_OSCILLATEUR_EN_KHZ 84000.0

#define PILOTETIMER1MODE2_TAUX_DE_BITS 19200.0
#define PILOTETIMER1MODE2_UTILISE_LE_DOUBLEUR_DE_TAUX 1

#define PILOTEIOT1_PORT LD6_GPIO_Port
#define PILOTEIOT1_SORTIE LD6_Pin

#define PILOTEIOT2_PORT  LD3_GPIO_Port
#define PILOTEIOT2_SORTIE  LD3_Pin

#define PILOTEIOT3_PORT  LD4_GPIO_Port
#define PILOTEIOT3_SORTIE  LD4_Pin

#define PILOTEIOT4_PORT  LD5_GPIO_Port
#define PILOTEIOT4_SORTIE  LD5_Pin

#define INTERFACET1_VALEUR_POUR_ALLUMER 1
#define INTERFACET1_VALEUR_POUR_ETEINDRE 0

#define INFORMATION_DISPONIBLE  1
#define INFORMATION_TRAITEE  0
#define REQUETE_ACTIVE  1
#define REQUETE_TRAITEE 0
#define MODULE_EN_FONCTION 1
#define MODULE_PAS_EN_FONCTION 0

#define FREQUENCE_DE_LA_BASE_DE_TEMPS_EN_HZ 2000.0
#define PILOTETIMER6UP_COMPTE_MAXIMAL  (\
  (unsigned int)((FREQUENCE_D_OSCILLATEUR_EN_KHZ \
  /FREQUENCE_DE_LA_BASE_DE_TEMPS_EN_HZ * 1000.0) - 1.0))

#define PROCESSUSCLIGNOTANT_TEMPS_COURT_ETEINT_EN_MS  500
#define PROCESSUSCLIGNOTANT_TEMPS_COURT_ALLUME_EN_MS  500
#define PROCESSUSCLIGNOTANT_TEMPS_LONG_ETEINT_EN_MS  500
#define PROCESSUSCLIGNOTANT_TEMPS_LONG_ALLUME_EN_MS  500

void main_initialise(void);
void neFaitRien(void);

//Variables publiques:
//copiez et adaptes les lignes qui suivent dans les fichiers .h des modules
//qui utilisent ces variables qui sont definies par htim6
//extern TIM_HandleTypeDef htim6;
//extern UART_HandleTypeDef huart2;

void Error_Handler(void);

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
#define BOOT1_Pin GPIO_PIN_2
#define BOOT1_GPIO_Port GPIOB
#define CLK_IN_Pin GPIO_PIN_10
#define CLK_IN_GPIO_Port GPIOB
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
#define Audio_SDA_Pin GPIO_PIN_9
#define Audio_SDA_GPIO_Port GPIOB
#define MEMS_INT2_Pin GPIO_PIN_1
#define MEMS_INT2_GPIO_Port GPIOE

#ifdef __cplusplus
}
#endif

#endif