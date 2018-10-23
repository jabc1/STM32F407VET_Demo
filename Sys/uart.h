#ifndef _uart_h
#define _uart_h
#include "stm32f4xx_hal.h"
#include "Sys.h"
extern UART_HandleTypeDef huart1;

void MX_USART1_UART_Init(void);
void MX_USART2_UART_Init(void);
void HAL_UART_MspDeInit(UART_HandleTypeDef* uartHandle);
void HAL_UART_MspInit(UART_HandleTypeDef* uartHandle);

#endif

