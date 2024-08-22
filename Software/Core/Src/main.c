/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
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
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "app_fatfs.h"
#include "usb_device.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <string.h>
#include "ads1299.h"
#include "usbd_cdc_if.h"
#include "ff_gen_drv.h"
#include "sd_diskio.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define BUFFER1 0
#define BUFFER2 1
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
RTC_HandleTypeDef hrtc;

SPI_HandleTypeDef hspi1;
SPI_HandleTypeDef hspi2;
DMA_HandleTypeDef hdma_spi1_tx;
DMA_HandleTypeDef hdma_spi1_rx;

TIM_HandleTypeDef htim1;
TIM_HandleTypeDef htim2;

/* USER CODE BEGIN PV */
uint8_t *dataReading;
int32_t dataProcessed[8];
char adc_data_str_buff1[60000];
char adc_data_str_buff2[60000];
char adc_data_str[200];
uint32_t adc_data_count = 0;
uint8_t WRITEBUFFER = BUFFER1;
uint8_t LOCK1 = 0;
uint8_t FULL1 = 0;
uint8_t LOCK2 = 0;
uint8_t FULL2 = 0;
uint8_t RUN = 0;
uint8_t DEMOUNT = 0;
uint8_t MOUNT = 0;
uint32_t timeMeasure[10];
uint32_t buff_i = 0;

/* SD Card*/
FRESULT res;
FIL myFile;

RTC_TimeTypeDef stime;
RTC_DateTypeDef sdate;

char log_file[32] = "Log.csv";

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
void PeriphCommonClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_DMA_Init(void);
static void MX_SPI1_Init(void);
static void MX_SPI2_Init(void);
static void MX_RTC_Init(void);
static void MX_TIM2_Init(void);
static void MX_TIM1_Init(void);
/* USER CODE BEGIN PFP */

int16_t FS_FILE_Write(char *data);
FRESULT sd_mount(void);
FRESULT sd_unmount(void);
void buttonTask(void);

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

/* Configure the peripherals common clocks */
  PeriphCommonClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_DMA_Init();
  MX_SPI1_Init();
  MX_SPI2_Init();
  if (MX_FATFS_Init() != APP_OK) {
    Error_Handler();
  }
  MX_USB_Device_Init();
  MX_RTC_Init();
  MX_TIM2_Init();
  MX_TIM1_Init();
  /* USER CODE BEGIN 2 */
	
	/* Init SD Card*/
	BSP_SD_Init();
	
	/* Enable Timer for LEDs */
	HAL_TIM_OC_Start(&htim1, 1);
	
	/* ADS1299 Initialization */
	ADS1299_Init(&hspi1, SPI1_NCS1_GPIO_Port, SPI1_NCS1_Pin, CLK_SEL_1_GPIO_Port, CLK_SEL_1_Pin, false, 
	N_PWDN_1_GPIO_Port , N_PWDN_1_Pin, N_RESET_1_GPIO_Port, N_RESET_1_Pin);
  
	/* activate conversion */
	HAL_GPIO_WritePin(START_GPIO_Port, START_Pin, GPIO_PIN_SET);
	HAL_Delay(100);
	
	
	
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {		
			/* SD-Card Writing was activated by button push */
			if(MOUNT){
				/* Init Write file */
				/* Mount SD Card */
				res = sd_mount();
				/* Check if mounting was successfull */
				if(res != FR_OK) {
					HAL_GPIO_WritePin(Error_LED_1_GPIO_Port, Error_LED_1_Pin, GPIO_PIN_SET);
				}
				
				/* Open file in append and write mode */
				res = f_open(&myFile, log_file, FA_OPEN_APPEND | FA_WRITE);
				/* Check if file opening was successfull */
				if(res != FR_OK) {
					HAL_GPIO_WritePin(Error_LED_1_GPIO_Port, Error_LED_1_Pin, GPIO_PIN_SET);
					sd_unmount();
				}
				
				/* Mount was successfull, deactivate MOUNT Flag */
				MOUNT = 0;
				
				/* Write header line to file */
				FS_FILE_Write("timestamp;value1;value2;value3;value4;value5;value6;value7;value8\n");
			}
			
			/* SD Card Writing is active */
			if(RUN){
				/*
				 * Write one of the two write buffers to the sd card. One of the two FULL
				 * Flags is set at any time, the other one is false. The full buffer is
				 * written to the sd-card. The other buffer is filled with new measurement
				 * data at the same time by an interrrupt with higher priority (HAL_SPI_TxRxCpltCallback).
				 */
				if(FULL1){
				/* Mark start write */
				HAL_GPIO_WritePin(SPI_Tx_LED_GPIO_Port, SPI_Tx_LED_Pin, GPIO_PIN_SET);
				/* Write SD Card */
				FS_FILE_Write(adc_data_str_buff1);
				/* Empty data buffer */
				strncpy(adc_data_str_buff1, "",1);
				/* Mark buffer as emptied */
				FULL1 = 0;
				/* Mark write finished */
				HAL_GPIO_WritePin(SPI_Tx_LED_GPIO_Port, SPI_Tx_LED_Pin, GPIO_PIN_RESET);
				}
				if(FULL2){
				/* Mark start write */
  			HAL_GPIO_WritePin(SPI_Tx_LED_GPIO_Port,  SPI_Tx_LED_Pin, GPIO_PIN_SET);
				/* Write SD Card */
				FS_FILE_Write(adc_data_str_buff2);
				/* Empty data buffer */
				strncpy(adc_data_str_buff2, "",1);
				/* Mark buffer as emptied */
				FULL2 = 0;
				/* Mark write finished */
				HAL_GPIO_WritePin(SPI_Tx_LED_GPIO_Port, SPI_Tx_LED_Pin, GPIO_PIN_RESET);
				}
			}
			
			/* SD-Card Writing was deactivated by button push */
			if(DEMOUNT){
				/* Close write file */
				res = f_close(&myFile);
				/* Unmount SD Card*/
				res = sd_unmount();
				/* DEMOUNT was successfull, deactivate DEMOUNT Flag */
				DEMOUNT = 0;
			}
		
    /* USER CODE END WHILE */

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

  /** Configure LSE Drive Capability
  */
  HAL_PWR_EnableBkUpAccess();
  __HAL_RCC_LSEDRIVE_CONFIG(RCC_LSEDRIVE_MEDIUMHIGH);

  /** Configure the main internal regulator output voltage
  */
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI|RCC_OSCILLATORTYPE_HSE
                              |RCC_OSCILLATORTYPE_LSE|RCC_OSCILLATORTYPE_MSI;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.LSEState = RCC_LSE_ON;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.MSIState = RCC_MSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.MSICalibrationValue = RCC_MSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.MSIClockRange = RCC_MSIRANGE_6;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_MSI;
  RCC_OscInitStruct.PLL.PLLM = RCC_PLLM_DIV1;
  RCC_OscInitStruct.PLL.PLLN = 32;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLR = RCC_PLLR_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = RCC_PLLQ_DIV2;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure the SYSCLKSource, HCLK, PCLK1 and PCLK2 clocks dividers
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK4|RCC_CLOCKTYPE_HCLK2
                              |RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.AHBCLK2Divider = RCC_SYSCLK_DIV2;
  RCC_ClkInitStruct.AHBCLK4Divider = RCC_SYSCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_3) != HAL_OK)
  {
    Error_Handler();
  }

  /** Enable MSI Auto calibration
  */
  HAL_RCCEx_EnableMSIPLLMode();
}

/**
  * @brief Peripherals Common Clock Configuration
  * @retval None
  */
void PeriphCommonClock_Config(void)
{
  RCC_PeriphCLKInitTypeDef PeriphClkInitStruct = {0};

  /** Initializes the peripherals clock
  */
  PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_SMPS;
  PeriphClkInitStruct.SmpsClockSelection = RCC_SMPSCLKSOURCE_HSI;
  PeriphClkInitStruct.SmpsDivSelection = RCC_SMPSCLKDIV_RANGE1;

  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN Smps */

  /* USER CODE END Smps */
}

/**
  * @brief RTC Initialization Function
  * @param None
  * @retval None
  */
static void MX_RTC_Init(void)
{

  /* USER CODE BEGIN RTC_Init 0 */

  /* USER CODE END RTC_Init 0 */

  RTC_TimeTypeDef sTime = {0};
  RTC_DateTypeDef sDate = {0};

  /* USER CODE BEGIN RTC_Init 1 */

  /* USER CODE END RTC_Init 1 */

  /** Initialize RTC Only
  */
  hrtc.Instance = RTC;
  hrtc.Init.HourFormat = RTC_HOURFORMAT_24;
  hrtc.Init.AsynchPrediv = 31;
  hrtc.Init.SynchPrediv = 1023;
  hrtc.Init.OutPut = RTC_OUTPUT_DISABLE;
  hrtc.Init.OutPutPolarity = RTC_OUTPUT_POLARITY_HIGH;
  hrtc.Init.OutPutType = RTC_OUTPUT_TYPE_OPENDRAIN;
  hrtc.Init.OutPutRemap = RTC_OUTPUT_REMAP_NONE;
  if (HAL_RTC_Init(&hrtc) != HAL_OK)
  {
    Error_Handler();
  }

  /* USER CODE BEGIN Check_RTC_BKUP */
	
  /* USER CODE END Check_RTC_BKUP */

  /** Initialize RTC and set the Time and Date
  */
  sTime.Hours = 0x0;
  sTime.Minutes = 0x0;
  sTime.Seconds = 0x0;
  sTime.SubSeconds = 0x0;
  sTime.DayLightSaving = RTC_DAYLIGHTSAVING_NONE;
  sTime.StoreOperation = RTC_STOREOPERATION_RESET;
  if (HAL_RTC_SetTime(&hrtc, &sTime, RTC_FORMAT_BCD) != HAL_OK)
  {
    Error_Handler();
  }
  sDate.WeekDay = RTC_WEEKDAY_MONDAY;
  sDate.Month = RTC_MONTH_JANUARY;
  sDate.Date = 0x1;
  sDate.Year = 0x0;

  if (HAL_RTC_SetDate(&hrtc, &sDate, RTC_FORMAT_BCD) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN RTC_Init 2 */
	
  /* USER CODE END RTC_Init 2 */

}

/**
  * @brief SPI1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_SPI1_Init(void)
{

  /* USER CODE BEGIN SPI1_Init 0 */

  /* USER CODE END SPI1_Init 0 */

  /* USER CODE BEGIN SPI1_Init 1 */

  /* USER CODE END SPI1_Init 1 */
  /* SPI1 parameter configuration*/
  hspi1.Instance = SPI1;
  hspi1.Init.Mode = SPI_MODE_MASTER;
  hspi1.Init.Direction = SPI_DIRECTION_2LINES;
  hspi1.Init.DataSize = SPI_DATASIZE_8BIT;
  hspi1.Init.CLKPolarity = SPI_POLARITY_LOW;
  hspi1.Init.CLKPhase = SPI_PHASE_2EDGE;
  hspi1.Init.NSS = SPI_NSS_SOFT;
  hspi1.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_16;
  hspi1.Init.FirstBit = SPI_FIRSTBIT_MSB;
  hspi1.Init.TIMode = SPI_TIMODE_DISABLE;
  hspi1.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
  hspi1.Init.CRCPolynomial = 7;
  hspi1.Init.CRCLength = SPI_CRC_LENGTH_DATASIZE;
  hspi1.Init.NSSPMode = SPI_NSS_PULSE_DISABLE;
  if (HAL_SPI_Init(&hspi1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN SPI1_Init 2 */

  /* USER CODE END SPI1_Init 2 */

}

/**
  * @brief SPI2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_SPI2_Init(void)
{

  /* USER CODE BEGIN SPI2_Init 0 */

  /* USER CODE END SPI2_Init 0 */

  /* USER CODE BEGIN SPI2_Init 1 */

  /* USER CODE END SPI2_Init 1 */
  /* SPI2 parameter configuration*/
  hspi2.Instance = SPI2;
  hspi2.Init.Mode = SPI_MODE_MASTER;
  hspi2.Init.Direction = SPI_DIRECTION_2LINES;
  hspi2.Init.DataSize = SPI_DATASIZE_8BIT;
  hspi2.Init.CLKPolarity = SPI_POLARITY_LOW;
  hspi2.Init.CLKPhase = SPI_PHASE_1EDGE;
  hspi2.Init.NSS = SPI_NSS_SOFT;
  hspi2.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_4;
  hspi2.Init.FirstBit = SPI_FIRSTBIT_MSB;
  hspi2.Init.TIMode = SPI_TIMODE_DISABLE;
  hspi2.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
  hspi2.Init.CRCPolynomial = 7;
  hspi2.Init.CRCLength = SPI_CRC_LENGTH_DATASIZE;
  hspi2.Init.NSSPMode = SPI_NSS_PULSE_DISABLE;
  if (HAL_SPI_Init(&hspi2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN SPI2_Init 2 */

  /* USER CODE END SPI2_Init 2 */

}

/**
  * @brief TIM1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM1_Init(void)
{

  /* USER CODE BEGIN TIM1_Init 0 */

  /* USER CODE END TIM1_Init 0 */

  TIM_MasterConfigTypeDef sMasterConfig = {0};
  TIM_OC_InitTypeDef sConfigOC = {0};
  TIM_BreakDeadTimeConfigTypeDef sBreakDeadTimeConfig = {0};

  /* USER CODE BEGIN TIM1_Init 1 */

  /* USER CODE END TIM1_Init 1 */
  htim1.Instance = TIM1;
  htim1.Init.Prescaler = 32000;
  htim1.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim1.Init.Period = 999;
  htim1.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim1.Init.RepetitionCounter = 0;
  htim1.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_OC_Init(&htim1) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterOutputTrigger2 = TIM_TRGO2_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim1, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sConfigOC.OCMode = TIM_OCMODE_TIMING;
  sConfigOC.Pulse = 999;
  sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
  sConfigOC.OCNPolarity = TIM_OCNPOLARITY_HIGH;
  sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
  sConfigOC.OCIdleState = TIM_OCIDLESTATE_RESET;
  sConfigOC.OCNIdleState = TIM_OCNIDLESTATE_RESET;
  if (HAL_TIM_OC_ConfigChannel(&htim1, &sConfigOC, TIM_CHANNEL_1) != HAL_OK)
  {
    Error_Handler();
  }
  sBreakDeadTimeConfig.OffStateRunMode = TIM_OSSR_DISABLE;
  sBreakDeadTimeConfig.OffStateIDLEMode = TIM_OSSI_DISABLE;
  sBreakDeadTimeConfig.LockLevel = TIM_LOCKLEVEL_OFF;
  sBreakDeadTimeConfig.DeadTime = 0;
  sBreakDeadTimeConfig.BreakState = TIM_BREAK_DISABLE;
  sBreakDeadTimeConfig.BreakPolarity = TIM_BREAKPOLARITY_HIGH;
  sBreakDeadTimeConfig.BreakFilter = 0;
  sBreakDeadTimeConfig.BreakAFMode = TIM_BREAK_AFMODE_INPUT;
  sBreakDeadTimeConfig.Break2State = TIM_BREAK2_DISABLE;
  sBreakDeadTimeConfig.Break2Polarity = TIM_BREAK2POLARITY_HIGH;
  sBreakDeadTimeConfig.Break2Filter = 0;
  sBreakDeadTimeConfig.Break2AFMode = TIM_BREAK_AFMODE_INPUT;
  sBreakDeadTimeConfig.AutomaticOutput = TIM_AUTOMATICOUTPUT_DISABLE;
  if (HAL_TIMEx_ConfigBreakDeadTime(&htim1, &sBreakDeadTimeConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM1_Init 2 */

  /* USER CODE END TIM1_Init 2 */

}

/**
  * @brief TIM2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM2_Init(void)
{

  /* USER CODE BEGIN TIM2_Init 0 */

  /* USER CODE END TIM2_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_SlaveConfigTypeDef sSlaveConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};

  /* USER CODE BEGIN TIM2_Init 1 */

  /* USER CODE END TIM2_Init 1 */
  htim2.Instance = TIM2;
  htim2.Init.Prescaler = 32000;
  htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim2.Init.Period = 999;
  htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_ENABLE;
  if (HAL_TIM_Base_Init(&htim2) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim2, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sSlaveConfig.SlaveMode = TIM_SLAVEMODE_DISABLE;
  sSlaveConfig.InputTrigger = TIM_TS_ITR0;
  if (HAL_TIM_SlaveConfigSynchro(&htim2, &sSlaveConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_OC1;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim2, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM2_Init 2 */

  /* USER CODE END TIM2_Init 2 */

}

/**
  * Enable DMA controller clock
  */
static void MX_DMA_Init(void)
{

  /* DMA controller clock enable */
  __HAL_RCC_DMAMUX1_CLK_ENABLE();
  __HAL_RCC_DMA1_CLK_ENABLE();

  /* DMA interrupt init */
  /* DMA1_Channel1_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(DMA1_Channel1_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(DMA1_Channel1_IRQn);
  /* DMA1_Channel2_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(DMA1_Channel2_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(DMA1_Channel2_IRQn);
  /* DMAMUX1_OVR_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(DMAMUX1_OVR_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(DMAMUX1_OVR_IRQn);

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
/* USER CODE BEGIN MX_GPIO_Init_1 */
/* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOC, CLK_SEL_2_Pin|USB_Rx_LED_Pin|CLK_SEL_1_Pin|N_RESET_1_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, N_PWDN_2_Pin|SPI_Tx_LED_Pin|SPI_Rx_LED_Pin|Error_LED_1_Pin
                          |Error_LED_2_Pin|SPI1_NCS2_Pin|START_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(SPI2_NCS1_GPIO_Port, SPI2_NCS1_Pin, GPIO_PIN_SET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, N_RESET_2_Pin|RF_Tx_LED_Pin|RF_Rx_LED_Pin|USB_Tx_LED_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOD, N_PWDN_1_Pin|SPI1_NCS1_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pins : CLK_SEL_2_Pin USB_Rx_LED_Pin CLK_SEL_1_Pin N_RESET_1_Pin */
  GPIO_InitStruct.Pin = CLK_SEL_2_Pin|USB_Rx_LED_Pin|CLK_SEL_1_Pin|N_RESET_1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pins : N_PWDN_2_Pin SPI_Tx_LED_Pin SPI_Rx_LED_Pin Error_LED_1_Pin
                           Error_LED_2_Pin SPI1_NCS2_Pin START_Pin */
  GPIO_InitStruct.Pin = N_PWDN_2_Pin|SPI_Tx_LED_Pin|SPI_Rx_LED_Pin|Error_LED_1_Pin
                          |Error_LED_2_Pin|SPI1_NCS2_Pin|START_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pin : SPI2_NCS1_Pin */
  GPIO_InitStruct.Pin = SPI2_NCS1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(SPI2_NCS1_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : N_DRDY_2_Pin */
  GPIO_InitStruct.Pin = N_DRDY_2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(N_DRDY_2_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : N_RESET_2_Pin RF_Tx_LED_Pin RF_Rx_LED_Pin USB_Tx_LED_Pin */
  GPIO_InitStruct.Pin = N_RESET_2_Pin|RF_Tx_LED_Pin|RF_Rx_LED_Pin|USB_Tx_LED_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pin : Button_Pin */
  GPIO_InitStruct.Pin = Button_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
  HAL_GPIO_Init(Button_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : BAT_STAT_Pin */
  GPIO_InitStruct.Pin = BAT_STAT_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(BAT_STAT_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : N_DRDY_1_Pin */
  GPIO_InitStruct.Pin = N_DRDY_1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(N_DRDY_1_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : N_PWDN_1_Pin SPI1_NCS1_Pin */
  GPIO_InitStruct.Pin = N_PWDN_1_Pin|SPI1_NCS1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

  /* EXTI interrupt init*/
  HAL_NVIC_SetPriority(EXTI1_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI1_IRQn);

  HAL_NVIC_SetPriority(EXTI9_5_IRQn, 15, 0);
  HAL_NVIC_EnableIRQ(EXTI9_5_IRQn);

  HAL_NVIC_SetPriority(EXTI15_10_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI15_10_IRQn);

/* USER CODE BEGIN MX_GPIO_Init_2 */
/* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */

/*
 * SPI TxCplt Callback
 */
void HAL_SPI_TxCpltCallback(SPI_HandleTypeDef *hspi){
		
	if(hspi == &hspi1){
		HAL_GPIO_WritePin(SPI1_NCS1_GPIO_Port, SPI1_NCS1_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(SPI1_NCS2_GPIO_Port, SPI1_NCS2_Pin, GPIO_PIN_SET);
	}
	if(hspi == &hspi2){
//		HAL_GPIO_WritePin(SPI2_NCS1_GPIO_Port, SPI2_NCS1_Pin, GPIO_PIN_SET);
	}
	// timing requirements
//	HAL_Delay(50);
}


/*
 * SPI TxRxCplt Callback
 */
void HAL_SPI_TxRxCpltCallback(SPI_HandleTypeDef *hspi){
	/* Measurement data was read*/	
	if(hspi == &hspi1){
			
		/* Deactivat SPI CS Pins */	
		HAL_GPIO_WritePin(SPI1_NCS1_GPIO_Port, SPI1_NCS1_Pin, GPIO_PIN_SET); // Pin 1
//	HAL_GPIO_WritePin(SPI1_NCS2_GPIO_Port, SPI1_NCS2_Pin, GPIO_PIN_SET); // Pin 2
			
		/* Convert ADS1299 data format to uint32_t */
		ADS1299_Convert_Data(dataReading,dataProcessed);
		/* Send measurement data over USB interface for live plotting */
		CDC_Transmit_FS((uint8_t*)dataProcessed,32);

		/* If active running is deactivated data is not saved */
		if(!RUN){
			return;
		}
		
		/* Create a timestamp */
		HAL_RTC_GetTime(&hrtc, &stime, RTC_FORMAT_BCD);
		HAL_RTC_GetDate(&hrtc, &sdate,RTC_FORMAT_BCD);
		
		
		/* Write into Buffer. Write either Buffer 1 or Buffer 2*/	
		/* Write to Buffer 1 */
		if(WRITEBUFFER == BUFFER1){
			/* Create formatstring in CSV data format */
			sprintf(adc_data_str_buff1 + buff_i,"%x-%x-%x-%03d;%d;%d;%d;%d;%d;%d;%d;%d \n", stime.Hours, stime.Minutes, stime.Seconds, 999 - (stime.SubSeconds * 1000 / 1024), dataProcessed[0],dataProcessed[1],dataProcessed[2],dataProcessed[3],dataProcessed[4],dataProcessed[5],dataProcessed[6],dataProcessed[7]);
			
			do{
				buff_i++;
			}while(adc_data_str_buff1[buff_i] != NULL);
		}
		
		
		/* Write to Buffer 2 */
		if(WRITEBUFFER == BUFFER2){
			sprintf(adc_data_str_buff2 + buff_i,"%x-%x-%x-%03d;%d;%d;%d;%d;%d;%d;%d;%d \n", stime.Hours, stime.Minutes, stime.Seconds, 999 - (stime.SubSeconds * 1000 / 1024), dataProcessed[0],dataProcessed[1],dataProcessed[2],dataProcessed[3],dataProcessed[4],dataProcessed[5],dataProcessed[6],dataProcessed[7]);
			/* set buff_i to the end of the buffer */
			do{
				buff_i++;
			}while(adc_data_str_buff2[buff_i] != NULL);
		}
		
		/* increase data counter */
		adc_data_count++;
		

		/* if a buffer is full (300 values) switch the buffer*/
		if(adc_data_count >= 300){
			/* Mark current buffer as FULL*/
			if(WRITEBUFFER == BUFFER1){
				FULL1 = 1;
			}
			if(WRITEBUFFER == BUFFER2){
				FULL2 = 1;
			}
			
			/* Set new WRITEBUFFER*/
			if(!FULL1){
					WRITEBUFFER = BUFFER1;
			}
			else if(!FULL2){
					WRITEBUFFER = BUFFER2;
			}else{
					/* Error if Both Buffers are occupied -> timing Issue*/
					HAL_GPIO_WritePin(Error_LED_1_GPIO_Port, Error_LED_1_Pin, GPIO_PIN_SET);
			}
			/* Reset buffer end point */
			buff_i = 0;
			/* Reset data counter */
			adc_data_count = 0;
		}
	}
	
	/* SPI 2 was Read */
	if(hspi == &hspi2){
			/*Implement here what should happen after spi2 read*/
	}
}


/*
 * SPI EXTI Callback
 */
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin){
		switch(GPIO_Pin){
			case N_DRDY_1_Pin:
//				ADS1299_WriteRegister(GPIO, 0xF0);	
				dataReading = ADS1299_RDATA();	
			
				
//				CDC_Transmit_FS((uint8_t*)"hi", 2);
				
//				ADS1299_WriteRegister(GPIO, 0x00);
				break;
			case N_DRDY_2_Pin:
				ADS1299_WriteRegister(GPIO, 0xF0);
				break;
			case Button_Pin:
				 buttonTask();
				break;
			default:
				break;
		}
}

void HAL_TIM_OC_DelayElapsedCallback(TIM_HandleTypeDef *htim){ 
	HAL_GPIO_TogglePin(SPI_Rx_LED_GPIO_Port, SPI_Rx_LED_Pin);
}



/**
* @brief  write data to the file
* @param  filename
* @param  data
* @return status int16_t: bytes_written < 0, FRESULT >=0
*/
int16_t FS_FILE_Write(char *data) {
	FRESULT res;
	
	uint16_t bytes_written;
 
	// 2. write data to file
	// res = f_write(&myFile, data, strlen(data), (void *)&bytes_written);
	bytes_written = f_puts(data, &myFile);
	
	// 5. return status: bytes_written < 0, FRESULT >=0
	return -1 * bytes_written;
}
 
 
/**
* @brief  mount uSD card
* @return FRESULT
*/
FRESULT sd_mount(void) {
	FRESULT res = f_mount(&SDFatFs, SDPath, 1);
	//HAL_Delay(10);
	return res;
}
 
 
/**
* @brief  unmount uSD card
* @return FRESULT
*/
FRESULT sd_unmount(void) {
	return f_mount(0, SDPath, 0);
}

void buttonTask(void){
	
	/* Software debounce*/
	HAL_Delay(10);
	if(!HAL_GPIO_ReadPin(Button_GPIO_Port,  Button_Pin)) return;
	
	/* if not running start run*/
	if(!RUN){
		/* initialize a run*/
		MOUNT = 1;
		RUN = 1;
		
		/* reset time*/
		stime.Hours = 0;
		stime.Minutes = 0;
		stime.Seconds = 0;
		stime.SubSeconds = 0;
		HAL_RTC_SetTime(&hrtc, &stime, RTC_FORMAT_BCD);
		
		/* re-init writing variables*/
		WRITEBUFFER = BUFFER1;
		buff_i = 0;
		adc_data_count = 0;
		
		/* mark running*/
		HAL_GPIO_WritePin(SPI_Rx_LED_GPIO_Port, SPI_Rx_LED_Pin, GPIO_PIN_SET);
		
		return;
	}
	
	
	/* If running, stop run*/
	if(RUN){
		RUN = 0;
		DEMOUNT = 1;
		
		/* RESET Error*/
  	HAL_GPIO_WritePin(Error_LED_1_GPIO_Port, Error_LED_1_Pin, GPIO_PIN_RESET);
		
		/* Mark Not Running*/
		HAL_GPIO_WritePin(SPI_Rx_LED_GPIO_Port, SPI_Rx_LED_Pin, GPIO_PIN_RESET);
		return;
	}
	
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
  __disable_irq();
  while (1)
  {
  }
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
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
