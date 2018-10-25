#include "gpio.h"
/*!
 * @file gpio.c
 * @brief 主要实现gpio重新封装
 * @author jason
 * @date 2018-10-18
 * @version ver1.0
 */
void MX_GPIO_Init(void)
{
//	GPIO_InitTypeDef GPIO_InitStruct;
//	/* GPIO Ports Clock Enable */
//	__HAL_RCC_GPIOA_CLK_ENABLE();

//	/*Configure GPIO pin Output Level */
//	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7, GPIO_PIN_RESET);

//	/*Configure GPIO pin : PA7 */
//	GPIO_InitStruct.Pin = GPIO_PIN_7;
//	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
//	GPIO_InitStruct.Pull = GPIO_NOPULL;
//	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
//	HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
	__HAL_RCC_GPIOA_CLK_ENABLE();
	
	SET_GPIO_OUT(ESP_GPIO);
	SET_GPIO_OUT(LED1_GPIO);
	SET_GPIO_L(ESP_GPIO);
	

}

void Set_GPIO_PIN(GPIO_TypeDef *gpio, uint16_t nPin,uint32_t mode,uint32_t speed)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	
	HAL_GPIO_WritePin(gpio, nPin, GPIO_PIN_RESET);
	GPIO_InitStruct.Pin = nPin;
	GPIO_InitStruct.Mode = mode;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = speed;
	HAL_GPIO_Init(gpio, &GPIO_InitStruct);
}


