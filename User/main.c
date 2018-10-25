/* Includes ------------------------------------------------------------------*/
#include "stdio.h"
#include "stm32f4xx_hal.h"
#include "Sys.h"
#include "delay.h"
#include "gpio.h"
#include "uart.h"
#include "time.h"
#include "fifo.h"
#include "queue_jk.h"
#include "esp8266.h"
#include "wifipack.h"

static void MX_NVIC_Init(void);

int main(void)
{
	HAL_Init();
	SystemClock_Config();
	
	MX_GPIO_Init();
	MX_USART1_UART_Init();
	MX_USART2_UART_Init();
	MX_TIM3_Init();
	MX_NVIC_Init();
	queue_init();
	esp8266_init();
	//esp8266_softreset();
	while (1)
	{
//		if(Uart1.status == uart1over)
//		{
//			Uart1.status = uart1head;
//			printf("re:%s\r\n",Uart1.buff);
//			memset(Uart1.buff,0,sizeof(Uart1.buff));
//		}
//		SysTick_delay_ms(500);
//		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7, !HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_7));
//		taskrun();
//		test2run();
//		esp_8266_send_cmd(CIFSR,"OK",100);
		senf_pack();
		USART2_Printf("%s\r\n","test");
		USART2_Printf("mac=%s\r\n",Idinfo.macbuff);
		USART2_Printf("ip=%03d.%03d.%03d.%03d\r\n",Idinfo.ipbuff[0],Idinfo.ipbuff[1],\
													Idinfo.ipbuff[2],Idinfo.ipbuff[3]);
		SysTick_delay_xms(3500);
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
	/* TIM3_IRQn interrupt configuration */
	HAL_NVIC_SetPriority(TIM3_IRQn, 0, 0);
	HAL_NVIC_EnableIRQ(TIM3_IRQn);	
}




/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/






