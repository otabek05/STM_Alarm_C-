/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
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

#include <string.h>
#include <stdarg.h>
#include <stdbool.h>
#include <ctype.h>
#include "MQTTClient.h"
#include "mqtt_interface.h"
#include "dhcp.h"

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
#define MUX1_Pin GPIO_PIN_4
#define MUX1_GPIO_Port GPIOE
#define MUX2_Pin GPIO_PIN_5
#define MUX2_GPIO_Port GPIOE
#define MUX3_Pin GPIO_PIN_6
#define MUX3_GPIO_Port GPIOE
#define DI1_Pin GPIO_PIN_0
#define DI1_GPIO_Port GPIOC
#define DI2_Pin GPIO_PIN_1
#define DI2_GPIO_Port GPIOC
#define DI3_Pin GPIO_PIN_2
#define DI3_GPIO_Port GPIOC
#define DI4_Pin GPIO_PIN_3
#define DI4_GPIO_Port GPIOC
#define switch5_Pin GPIO_PIN_4
#define switch5_GPIO_Port GPIOA
#define switch6_Pin GPIO_PIN_5
#define switch6_GPIO_Port GPIOA
#define switch7_Pin GPIO_PIN_6
#define switch7_GPIO_Port GPIOA
#define switch8_Pin GPIO_PIN_7
#define switch8_GPIO_Port GPIOA
#define W5500_RESET_Pin GPIO_PIN_5
#define W5500_RESET_GPIO_Port GPIOC
#define NetworkStatus_Pin GPIO_PIN_11
#define NetworkStatus_GPIO_Port GPIOE
#define NetworkStatus_EXTI_IRQn EXTI15_10_IRQn
#define switch1_Pin GPIO_PIN_12
#define switch1_GPIO_Port GPIOE
#define switch2_Pin GPIO_PIN_13
#define switch2_GPIO_Port GPIOE
#define switch3_Pin GPIO_PIN_14
#define switch3_GPIO_Port GPIOE
#define switch4_Pin GPIO_PIN_15
#define switch4_GPIO_Port GPIOE
#define W5500_CS_Pin GPIO_PIN_12
#define W5500_CS_GPIO_Port GPIOB
#define DI5_Pin GPIO_PIN_8
#define DI5_GPIO_Port GPIOD
#define DI6_Pin GPIO_PIN_9
#define DI6_GPIO_Port GPIOD
#define DI7_Pin GPIO_PIN_10
#define DI7_GPIO_Port GPIOD
#define DI8_Pin GPIO_PIN_13
#define DI8_GPIO_Port GPIOD
#define DI9_Pin GPIO_PIN_6
#define DI9_GPIO_Port GPIOC
#define DI10_Pin GPIO_PIN_7
#define DI10_GPIO_Port GPIOC
#define DI11_Pin GPIO_PIN_8
#define DI11_GPIO_Port GPIOC
#define DI12_Pin GPIO_PIN_9
#define DI12_GPIO_Port GPIOC
#define DI13_Pin GPIO_PIN_8
#define DI13_GPIO_Port GPIOA
#define DI14_Pin GPIO_PIN_9
#define DI14_GPIO_Port GPIOA
#define DI15_Pin GPIO_PIN_10
#define DI15_GPIO_Port GPIOA
#define DI16_Pin GPIO_PIN_11
#define DI16_GPIO_Port GPIOA
#define sound_Pin GPIO_PIN_1
#define sound_GPIO_Port GPIOE

/* USER CODE BEGIN Private defines */


/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
