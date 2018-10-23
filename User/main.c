/* Includes ------------------------------------------------------------------*/
#include "stdio.h"
#include "stm32f4xx_hal.h"
#include "Sys.h"
#include "gpio.h"
#include "uart.h"
static void MX_NVIC_Init(void);

int main(void)
{
	HAL_Init();
	SystemClock_Config();
	
	MX_GPIO_Init();
	MX_USART1_UART_Init();
	MX_USART2_UART_Init();
	MX_NVIC_Init();
	while (1)
	{
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7, GPIO_PIN_RESET);
		HAL_Delay(200);
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7, GPIO_PIN_SET);
		HAL_Delay(200);
	}
}


static void MX_NVIC_Init(void)
{
	/* USART1_IRQn interrupt configuration */
	HAL_NVIC_SetPriority(USART1_IRQn, 0, 0);
	HAL_NVIC_EnableIRQ(USART1_IRQn);
	/* USART2_IRQn interrupt configuration */
	HAL_NVIC_SetPriority(USART2_IRQn, 0, 0);
	HAL_NVIC_EnableIRQ(USART2_IRQn);
}




/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/






