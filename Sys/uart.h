#ifndef _uart_h
#define _uart_h
#include "stm32f4xx_hal.h"
#include "Sys.h"
#define 	uart1len		512
#define		uart1head		1
#define		uart1read		2
#define		uart1over		3


#pragma pack(push,1)
typedef struct _Uart1
{
	u8 buff[uart1len];
	u8 backbuff[uart1len];
	u16 len;
	u8 status;
}_Uart1;
#pragma pack(push)

extern _Uart1 Uart1;

extern UART_HandleTypeDef huart1;

void MX_USART1_UART_Init(void);
void MX_USART2_UART_Init(void);
void HAL_UART_MspDeInit(UART_HandleTypeDef* uartHandle);
void HAL_UART_MspInit(UART_HandleTypeDef* uartHandle);

#endif

