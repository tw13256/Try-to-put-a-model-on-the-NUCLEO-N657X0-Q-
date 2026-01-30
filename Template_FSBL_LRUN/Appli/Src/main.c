/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file           : main.c
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2026 STMicroelectronics.
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
#include "app_x-cube-ai.h"
#include <stdio.h>  // <--- 加入這一行
/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
CACHEAXI_HandleTypeDef hcacheaxi;

RAMCFG_HandleTypeDef hramcfg_SRAM3;
RAMCFG_HandleTypeDef hramcfg_SRAM4;
RAMCFG_HandleTypeDef hramcfg_SRAM5;
RAMCFG_HandleTypeDef hramcfg_SRAM6;

UART_HandleTypeDef huart1;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
static void MPU_Config(void);
static void MX_GPIO_Init(void);
static void MX_CACHEAXI_Init(void);
static void MX_RAMCFG_Init(void);
static void MX_USART1_UART_Init(void);
static void SystemIsolation_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE BEGIN PFP */
#if defined(__ICCARM__)
__ATTRIBUTES size_t __write(int, const unsigned char *, size_t);
#endif /* __ICCARM__ */

#if defined(__ICCARM__)
/* New definition from EWARM V9, compatible with EWARM8 */
int iar_fputc(int ch);
#define PUTCHAR_PROTOTYPE int iar_fputc(int ch)
#elif defined ( __CC_ARM ) || defined(__ARMCC_VERSION)
/* ARM Compiler 5/6*/
#define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#elif defined(__GNUC__)
#define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#endif /* __ICCARM__ */

/* USER CODE END 0 */

/**
 * @brief  The application entry point.
 * @retval int
 */
int main(void)
{

	/* USER CODE BEGIN 1 */

	/* USER CODE END 1 */

	/* MPU Configuration--------------------------------------------------------*/
	MPU_Config();

	/* Enable the CPU Cache */

	/* Enable I-Cache---------------------------------------------------------*/
	SCB_EnableICache();

	/* Enable D-Cache---------------------------------------------------------*/
	SCB_EnableDCache();

	/* MCU Configuration--------------------------------------------------------*/
	HAL_Init();
	MX_GPIO_Init();
	HAL_Delay(1);

	/* USER CODE BEGIN Init */

	/* USER CODE END Init */

	/* USER CODE BEGIN SysInit */

	/* USER CODE END SysInit */

	/* Initialize all configured peripherals */
	//  MX_GPIO_Init();
	MX_CACHEAXI_Init();
	MX_RAMCFG_Init();
	MX_USART1_UART_Init();
	MX_X_CUBE_AI_Init();
	SystemIsolation_Config();
	/* USER CODE BEGIN 2 */
	printf("APPLIOK\r\n");  // <--- 修改成這樣

	MX_X_CUBE_AI_Process();

	/* USER CODE END 2 */

	/* Infinite loop */
	/* USER CODE BEGIN WHILE */
	while (1)
	{
		/* USER CODE END WHILE */

		/* USER CODE BEGIN 3 */
	}
	/* USER CODE END 3 */
}

/**
 * @brief CACHEAXI Initialization Function
 * @param None
 * @retval None
 */
static void MX_CACHEAXI_Init(void)
{

	/* USER CODE BEGIN CACHEAXI_Init 0 */

	/* USER CODE END CACHEAXI_Init 0 */

	/* USER CODE BEGIN CACHEAXI_Init 1 */

	/* USER CODE END CACHEAXI_Init 1 */
	hcacheaxi.Instance = CACHEAXI;
	if (HAL_CACHEAXI_Init(&hcacheaxi) != HAL_OK)
	{
		Error_Handler();
	}
	/* USER CODE BEGIN CACHEAXI_Init 2 */

	/* USER CODE END CACHEAXI_Init 2 */

}

/**
 * @brief RAMCFG Initialization Function
 * @param None
 * @retval None
 */
static void MX_RAMCFG_Init(void)
{

	/* USER CODE BEGIN RAMCFG_Init 0 */

	/* USER CODE END RAMCFG_Init 0 */

	/* USER CODE BEGIN RAMCFG_Init 1 */

	/* USER CODE END RAMCFG_Init 1 */

	/** Initialize RAMCFG SRAM3
	 */
	hramcfg_SRAM3.Instance = RAMCFG_SRAM3_AXI;
	if (HAL_RAMCFG_Init(&hramcfg_SRAM3) != HAL_OK)
	{
		Error_Handler();
	}

	/** Initialize RAMCFG SRAM4
	 */
	hramcfg_SRAM4.Instance = RAMCFG_SRAM4_AXI;
	if (HAL_RAMCFG_Init(&hramcfg_SRAM4) != HAL_OK)
	{
		Error_Handler();
	}
	/** Initialize RAMCFG SRAM5
	 */
	hramcfg_SRAM5.Instance = RAMCFG_SRAM5_AXI;
	if (HAL_RAMCFG_Init(&hramcfg_SRAM5) != HAL_OK)
	{
		Error_Handler();
	}
	/** Initialize RAMCFG SRAM6
	 */
	hramcfg_SRAM6.Instance = RAMCFG_SRAM6_AXI;
	if (HAL_RAMCFG_Init(&hramcfg_SRAM6) != HAL_OK)
	{
		Error_Handler();
	}
	/* USER CODE BEGIN RAMCFG_Init 2 */

	/* USER CODE END RAMCFG_Init 2 */

}

/**
 * @brief RIF Initialization Function
 * @param None
 * @retval None
 */
static void SystemIsolation_Config(void)
{

	/* USER CODE BEGIN RIF_Init 0 */

	/* USER CODE END RIF_Init 0 */

	/* set all required IPs as secure privileged */
	__HAL_RCC_RIFSC_CLK_ENABLE();

	/* RIF-Aware IPs Config */
	//  RIMC_MasterConfig_t RIMC_master = {0};
	//  RIMC_master.MasterCID = RIF_CID_0;
	//  RIMC_master.SecPriv = RIF_ATTRIBUTE_SEC | RIF_ATTRIBUTE_NPRIV;
	//  HAL_RIF_RIMC_ConfigMasterAttributes(RIF_MASTER_INDEX_ETH1, &RIMC_master);

	//安全

	  HAL_RIF_RISC_SetSlaveSecureAttributes(RIF_RISC_PERIPH_INDEX_NPU, RIF_ATTRIBUTE_PRIV | RIF_ATTRIBUTE_SEC);

	/* 1. 設定 NPU Master Attributes (發起讀寫的權限) */

	// 應用到 NPU (主 Port)

	/* 1. 設定 NPU Master Attributes (發起讀寫的權限) */


	//非安全


	//  HAL_RIF_RISC_SetSlaveSecureAttributes(RIF_RISC_PERIPH_INDEX_NPU, RIF_ATTRIBUTE_NSEC | RIF_ATTRIBUTE_NPRIV);

	//被建議不要加****

	/* set up GPIO configuration */
	HAL_GPIO_ConfigPinAttributes(GPIOA,GPIO_PIN_3,GPIO_PIN_SEC|GPIO_PIN_NPRIV);
	HAL_GPIO_ConfigPinAttributes(GPIOE,GPIO_PIN_4,GPIO_PIN_SEC|GPIO_PIN_NPRIV);
	HAL_GPIO_ConfigPinAttributes(GPIOE,GPIO_PIN_5,GPIO_PIN_SEC|GPIO_PIN_NPRIV);
	HAL_GPIO_ConfigPinAttributes(GPIOE,GPIO_PIN_6,GPIO_PIN_SEC|GPIO_PIN_NPRIV);
	HAL_GPIO_ConfigPinAttributes(GPIOG,GPIO_PIN_8,GPIO_PIN_SEC|GPIO_PIN_NPRIV);

	/* USER CODE BEGIN RIF_Init 1 */
//	printf("RIF Configured: NPU (CID_1, Sec+Priv), SRAM5~6 (Sec+Priv), XSPI2 (Sec+Priv)\r\n");
	/* USER CODE END RIF_Init 1 */
	/* USER CODE BEGIN RIF_Init 2 */

	/* USER CODE END RIF_Init 2 */

}

/**
 * @brief USART1 Initialization Function
 * @param None
 * @retval None
 */
static void MX_USART1_UART_Init(void)
{

	/* USER CODE BEGIN USART1_Init 0 */

	/* USER CODE END USART1_Init 0 */

	/* USER CODE BEGIN USART1_Init 1 */

	/* USER CODE END USART1_Init 1 */
	huart1.Instance = USART1;
	huart1.Init.BaudRate = 115200;
	huart1.Init.WordLength = UART_WORDLENGTH_8B;
	huart1.Init.StopBits = UART_STOPBITS_1;
	huart1.Init.Parity = UART_PARITY_NONE;
	huart1.Init.Mode = UART_MODE_TX_RX;
	huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
	huart1.Init.OverSampling = UART_OVERSAMPLING_16;
	huart1.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
	huart1.Init.ClockPrescaler = UART_PRESCALER_DIV1;
	huart1.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
	if (HAL_UART_Init(&huart1) != HAL_OK)
	{
		Error_Handler();
	}
	if (HAL_UARTEx_SetTxFifoThreshold(&huart1, UART_TXFIFO_THRESHOLD_1_8) != HAL_OK)
	{
		Error_Handler();
	}
	if (HAL_UARTEx_SetRxFifoThreshold(&huart1, UART_RXFIFO_THRESHOLD_1_8) != HAL_OK)
	{
		Error_Handler();
	}
	if (HAL_UARTEx_DisableFifoMode(&huart1) != HAL_OK)
	{
		Error_Handler();
	}
	/* USER CODE BEGIN USART1_Init 2 */

	/* USER CODE END USART1_Init 2 */

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
	__HAL_RCC_GPIOE_CLK_ENABLE();
	__HAL_RCC_GPIOA_CLK_ENABLE();

	/*Configure GPIO pin Output Level */
	HAL_GPIO_WritePin(SOFT_SDA_GPIO_Port, SOFT_SDA_Pin, GPIO_PIN_SET);

	/*Configure GPIO pin Output Level */
	HAL_GPIO_WritePin(SOFT_SCL_GPIO_Port, SOFT_SCL_Pin, GPIO_PIN_SET);

	/*Configure GPIO pin : SOFT_SDA_Pin */
	GPIO_InitStruct.Pin = SOFT_SDA_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_OD;
	GPIO_InitStruct.Pull = GPIO_PULLUP;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	HAL_GPIO_Init(SOFT_SDA_GPIO_Port, &GPIO_InitStruct);

	/*Configure GPIO pin : SOFT_SCL_Pin */
	GPIO_InitStruct.Pin = SOFT_SCL_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_OD;
	GPIO_InitStruct.Pull = GPIO_PULLUP;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	HAL_GPIO_Init(SOFT_SCL_GPIO_Port, &GPIO_InitStruct);

	/* USER CODE BEGIN MX_GPIO_Init_2 */

	/* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */
/* USER CODE BEGIN 4 */
PUTCHAR_PROTOTYPE
{
	/* Place your implementation of fputc here */
	/* e.g. write a character to the USART1 and Loop until the end of transmission */
	HAL_UART_Transmit(&huart1, (uint8_t *)&ch, 1, 0xFFFF);

	return ch;
}

#if defined(__ICCARM__)
size_t __write(int file, unsigned char const *ptr, size_t len)
{
	size_t idx;
	unsigned char const *pdata = ptr;

	for (idx = 0; idx < len; idx++)
	{
		iar_fputc((int)*pdata);
		pdata++;
	}
	return len;
}
#endif /* __ICCARM__ */
/* USER CODE END 4 */

/* MPU Configuration */

void MPU_Config(void)
{
	MPU_Region_InitTypeDef MPU_InitStruct = {0};
	MPU_Attributes_InitTypeDef MPU_AttributesInit = {0};
	uint32_t primask_bit = __get_PRIMASK();
	__disable_irq();

	/* Disables the MPU */
	HAL_MPU_Disable();

	/** Initializes and configures the Region 0 and the memory to be protected
	 */
	MPU_InitStruct.Enable = MPU_REGION_ENABLE;
	MPU_InitStruct.Number = MPU_REGION_NUMBER0;
	MPU_InitStruct.BaseAddress = __NON_CACHEABLE_SECTION_BEGIN;
	MPU_InitStruct.LimitAddress = __NON_CACHEABLE_SECTION_END;
	MPU_InitStruct.AttributesIndex = MPU_ATTRIBUTES_NUMBER0;
	MPU_InitStruct.AccessPermission = MPU_REGION_ALL_RW;
	MPU_InitStruct.DisableExec = MPU_INSTRUCTION_ACCESS_ENABLE;
	MPU_InitStruct.DisablePrivExec = MPU_PRIV_INSTRUCTION_ACCESS_ENABLE;
	MPU_InitStruct.IsShareable = MPU_ACCESS_NOT_SHAREABLE;

	HAL_MPU_ConfigRegion(&MPU_InitStruct);

	/** Initializes and configures the Attribute 0 and the memory to be protected
	 */
	MPU_AttributesInit.Number = MPU_ATTRIBUTES_NUMBER0;
	MPU_AttributesInit.Attributes = INNER_OUTER(MPU_NOT_CACHEABLE);

	HAL_MPU_ConfigMemoryAttributes(&MPU_AttributesInit);
	/* Enables the MPU */
	HAL_MPU_Enable(MPU_HFNMI_PRIVDEF);

	/* Exit critical section to lock the system and avoid any issue around MPU mechanism */
	__set_PRIMASK(primask_bit);

}

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
#ifdef USE_FULL_ASSERT
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
