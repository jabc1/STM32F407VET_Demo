#ifndef _uart_h
#define _uart_h
#include "stm32f4xx_hal.h"
#include "Sys.h"
#include "def.h"
#include "queue_jk.h"

#define 	uart1len		512
#define 	uart2len		2000

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

typedef struct _Uart1fifo
{
	u8 Rxbuff[uart1len];
	u8 Txbuff[uart1len];
}_Uart1fifo;

typedef struct _Uart2fifo
{
	u8 Rxbuff[uart2len];
	u8 Txbuff[uart2len];
}_Uart2fifo;
#pragma pack(pop)

extern _Uart1 Uart1;

extern QueueType Uart1queue;
extern QueueType Uart2queue;
extern _Uart1fifo Uart1fifo;
extern _Uart2fifo Uart2fifo;//fifo½á¹¹Ìå

extern UART_HandleTypeDef huart1;
extern UART_HandleTypeDef huart2;
void MX_USART1_UART_Init(void);
void MX_USART2_UART_Init(void);
void HAL_UART_MspDeInit(UART_HandleTypeDef* uartHandle);
void HAL_UART_MspInit(UART_HandleTypeDef* uartHandle);

void queue_init(void);
void taskrun(void);
void test2run(void);
void USART2_Printf(const char *fmt, ...);
void RS485_Send_Data(char *buf,uint32_t len);
#endif

