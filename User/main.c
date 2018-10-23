/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"
#include "Sys.h"
#include "gpio.h"

int main(void)
{
	HAL_Init();
	SystemClock_Config();
	MX_GPIO_Init();
	while (1)
	{
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7, GPIO_PIN_RESET);
		HAL_Delay(200);
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7, GPIO_PIN_SET);
		HAL_Delay(200);
	}
}







/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/






