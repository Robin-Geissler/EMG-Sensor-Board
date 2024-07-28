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
#include "stm32wbxx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

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
#define CLK_SEL_2_Pin GPIO_PIN_13
#define CLK_SEL_2_GPIO_Port GPIOC
#define N_PWDN_2_Pin GPIO_PIN_8
#define N_PWDN_2_GPIO_Port GPIOB
#define SPI2_NCS1_Pin GPIO_PIN_3
#define SPI2_NCS1_GPIO_Port GPIOC
#define N_DRDY_2_Pin GPIO_PIN_1
#define N_DRDY_2_GPIO_Port GPIOA
#define N_DRDY_2_EXTI_IRQn EXTI1_IRQn
#define N_RESET_2_Pin GPIO_PIN_2
#define N_RESET_2_GPIO_Port GPIOA
#define RF_Tx_LED_Pin GPIO_PIN_3
#define RF_Tx_LED_GPIO_Port GPIOA
#define RF_Rx_LED_Pin GPIO_PIN_4
#define RF_Rx_LED_GPIO_Port GPIOA
#define Button_Pin GPIO_PIN_5
#define Button_GPIO_Port GPIOA
#define Button_EXTI_IRQn EXTI9_5_IRQn
#define SPI_Tx_LED_Pin GPIO_PIN_10
#define SPI_Tx_LED_GPIO_Port GPIOB
#define SPI_Rx_LED_Pin GPIO_PIN_11
#define SPI_Rx_LED_GPIO_Port GPIOB
#define Error_LED_1_Pin GPIO_PIN_0
#define Error_LED_1_GPIO_Port GPIOB
#define Error_LED_2_Pin GPIO_PIN_1
#define Error_LED_2_GPIO_Port GPIOB
#define BAT_STAT_Pin GPIO_PIN_12
#define BAT_STAT_GPIO_Port GPIOB
#define USB_Rx_LED_Pin GPIO_PIN_6
#define USB_Rx_LED_GPIO_Port GPIOC
#define USB_Tx_LED_Pin GPIO_PIN_10
#define USB_Tx_LED_GPIO_Port GPIOA
#define CLK_SEL_1_Pin GPIO_PIN_10
#define CLK_SEL_1_GPIO_Port GPIOC
#define N_DRDY_1_Pin GPIO_PIN_11
#define N_DRDY_1_GPIO_Port GPIOC
#define N_DRDY_1_EXTI_IRQn EXTI15_10_IRQn
#define N_RESET_1_Pin GPIO_PIN_12
#define N_RESET_1_GPIO_Port GPIOC
#define N_PWDN_1_Pin GPIO_PIN_0
#define N_PWDN_1_GPIO_Port GPIOD
#define SPI1_NCS1_Pin GPIO_PIN_1
#define SPI1_NCS1_GPIO_Port GPIOD
#define SPI1_NCS2_Pin GPIO_PIN_6
#define SPI1_NCS2_GPIO_Port GPIOB
#define START_Pin GPIO_PIN_7
#define START_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
