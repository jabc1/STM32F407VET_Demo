#include "time.h"
#include "Sys.h"
#include "gpio.h"
#include "uart.h"
/*!
 * @file time.c
 * @brief 主要实现定时器初始化
 * @author jason
 * @date 2018-10-18
 * @version ver1.0
 */
/*
	Tout = （（arr+1）*（psc+1））/Tclk ;
其中：
	Tclk：定时器的输入时钟频率（单位MHZ）
	Tout：定时器溢出时间（单位为us）

	.TIM_Period = arr；   eg；5000
	.TIM_Prescaler = psc；eg：168
	
eg	Tout = （（5000）×（168））/ 84 = 10000us = 10ms
*/
TIM_HandleTypeDef htim3;

/* TIM3 init function */
void MX_TIM3_Init(void)
{
  TIM_ClockConfigTypeDef sClockSourceConfig;
  TIM_MasterConfigTypeDef sMasterConfig;

  htim3.Instance = TIM3;
  htim3.Init.Prescaler = 1680-1;
  htim3.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim3.Init.Period = 10000-1;
  htim3.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  if (HAL_TIM_Base_Init(&htim3) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim3, &sClockSourceConfig) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim3, &sMasterConfig) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }
	HAL_TIM_Base_Start_IT(&htim3);
}

void HAL_TIM_Base_MspInit(TIM_HandleTypeDef* tim_baseHandle)
{

  if(tim_baseHandle->Instance==TIM3)
  {
  /* USER CODE BEGIN TIM3_MspInit 0 */

  /* USER CODE END TIM3_MspInit 0 */
    /* TIM3 clock enable */
    __HAL_RCC_TIM3_CLK_ENABLE();
  /* USER CODE BEGIN TIM3_MspInit 1 */

  /* USER CODE END TIM3_MspInit 1 */
  }
}

void HAL_TIM_Base_MspDeInit(TIM_HandleTypeDef* tim_baseHandle)
{

  if(tim_baseHandle->Instance==TIM3)
  {
  /* USER CODE BEGIN TIM3_MspDeInit 0 */

  /* USER CODE END TIM3_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_TIM3_CLK_DISABLE();

    /* TIM3 interrupt Deinit */
    HAL_NVIC_DisableIRQ(TIM3_IRQn);
  /* USER CODE BEGIN TIM3_MspDeInit 1 */

  /* USER CODE END TIM3_MspDeInit 1 */
  }
} 


void TIM3_IRQHandler(void)
{
	//HAL_TIM_IRQHandler(&htim3);
	/* TIM Update event */
	if(__HAL_TIM_GET_FLAG(&htim3, TIM_FLAG_UPDATE) != RESET)
	{
		if(__HAL_TIM_GET_IT_SOURCE(&htim3, TIM_IT_UPDATE) !=RESET)
		{
			__HAL_TIM_CLEAR_IT(&htim3, TIM_IT_UPDATE);
			//HAL_TIM_PeriodElapsedCallback(&htim3);
			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7, !HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_7));
		}
	}
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
//	if(htim->Instance == htim3.Instance)
//	{
//		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7, !HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_7));
//	}
}


