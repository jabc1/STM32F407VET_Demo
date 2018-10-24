#include "uart.h"


UART_HandleTypeDef huart1;
UART_HandleTypeDef huart2;


QueueType Uart1queue;//结构体变量
QueueType Uart2queue;//结构体变量
_Uart1 Uart1;//结构体变量

_Uart1fifo Uart1fifo;//fifo结构体
_Uart2fifo Uart2fifo;//fifo结构体


/* USART1 init function */
void MX_USART1_UART_Init(void)
{

	huart1.Instance = USART1;
	huart1.Init.BaudRate = 115200;
	huart1.Init.WordLength = UART_WORDLENGTH_8B;
	huart1.Init.StopBits = UART_STOPBITS_1;
	huart1.Init.Parity = UART_PARITY_NONE;
	huart1.Init.Mode = UART_MODE_TX_RX;
	huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
	huart1.Init.OverSampling = UART_OVERSAMPLING_16;
	if (HAL_UART_Init(&huart1) != HAL_OK)
	{
		_Error_Handler(__FILE__, __LINE__);
	}
	__HAL_UART_ENABLE_IT(&huart1, UART_IT_RXNE);//使能串口接收中断
	Uart1.status = uart1head;
}
/* USART2 init function */

void MX_USART2_UART_Init(void)
{

	huart2.Instance = USART2;
	huart2.Init.BaudRate = 115200;
	huart2.Init.WordLength = UART_WORDLENGTH_8B;
	huart2.Init.StopBits = UART_STOPBITS_1;
	huart2.Init.Parity = UART_PARITY_NONE;
	huart2.Init.Mode = UART_MODE_TX_RX;
	huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
	huart2.Init.OverSampling = UART_OVERSAMPLING_16;
	if (HAL_UART_Init(&huart2) != HAL_OK)
	{
		_Error_Handler(__FILE__, __LINE__);
	}
	__HAL_UART_ENABLE_IT(&huart2, UART_IT_RXNE);//使能串口接收中断
}

void HAL_UART_MspInit(UART_HandleTypeDef* uartHandle)
{

  GPIO_InitTypeDef GPIO_InitStruct;
  if(uartHandle->Instance==USART1)
  {
  /* USER CODE BEGIN USART1_MspInit 0 */

  /* USER CODE END USART1_MspInit 0 */
    /* USART1 clock enable */
    __HAL_RCC_USART1_CLK_ENABLE();
  
    /**USART1 GPIO Configuration    
    PA9     ------> USART1_TX
    PA10     ------> USART1_RX 
    */
    GPIO_InitStruct.Pin = GPIO_PIN_9|GPIO_PIN_10;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF7_USART1;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /* USER CODE BEGIN USART1_MspInit 1 */

  /* USER CODE END USART1_MspInit 1 */
  }
  else if(uartHandle->Instance==USART2)
  {
  /* USER CODE BEGIN USART2_MspInit 0 */

  /* USER CODE END USART2_MspInit 0 */
    /* USART2 clock enable */
    __HAL_RCC_USART2_CLK_ENABLE();
  
    /**USART2 GPIO Configuration    
    PA2     ------> USART2_TX
    PA3     ------> USART2_RX 
    */
    GPIO_InitStruct.Pin = GPIO_PIN_2|GPIO_PIN_3;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF7_USART2;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /* USER CODE BEGIN USART2_MspInit 1 */

  /* USER CODE END USART2_MspInit 1 */
  }
}

void HAL_UART_MspDeInit(UART_HandleTypeDef* uartHandle)
{

  if(uartHandle->Instance==USART1)
  {
  /* USER CODE BEGIN USART1_MspDeInit 0 */

  /* USER CODE END USART1_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_USART1_CLK_DISABLE();
  
    /**USART1 GPIO Configuration    
    PA9     ------> USART1_TX
    PA10     ------> USART1_RX 
    */
    HAL_GPIO_DeInit(GPIOA, GPIO_PIN_9|GPIO_PIN_10);

    /* USART1 interrupt Deinit */
    HAL_NVIC_DisableIRQ(USART1_IRQn);
  /* USER CODE BEGIN USART1_MspDeInit 1 */

  /* USER CODE END USART1_MspDeInit 1 */
  }
  else if(uartHandle->Instance==USART2)
  {
  /* USER CODE BEGIN USART2_MspDeInit 0 */

  /* USER CODE END USART2_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_USART2_CLK_DISABLE();
  
    /**USART2 GPIO Configuration    
    PA2     ------> USART2_TX
    PA3     ------> USART2_RX 
    */
    HAL_GPIO_DeInit(GPIOA, GPIO_PIN_2|GPIO_PIN_3);

    /* USART2 interrupt Deinit */
    HAL_NVIC_DisableIRQ(USART2_IRQn);
  /* USER CODE BEGIN USART2_MspDeInit 1 */

  /* USER CODE END USART2_MspDeInit 1 */
  }
} 
void queue_init()
{
	Queue_Init(&Uart1queue,Uart1fifo.Rxbuff,uart1len,2);
	Queue_Init(&Uart2queue,Uart2fifo.Rxbuff,uart2len,1);
}
void taskrun()
{
	uint8_t find;
	if(Queue_Query(&Uart1queue,&find))//队列查询
	{
		printf("Queue_Query:%x\r\n",find);
		if(find == 0x61)//进行队列查找知道找到正确的数据
		{
			while(Queue_Get(&Uart1queue,&Uart1fifo.Txbuff))//找到数据头进行全部队列出队操作,进行一个一个数据出队操作
			{
				printf("Queue_Get:%s\r\n",Uart1fifo.Txbuff);
			}
		}
		Queue_Get(&Uart1queue,&find);//进行队列后移
	}
}
void test2run()
{
	_Uart2fifo Uart3fifo;
	uint8_t find;
	u16 i = 0;
	if(Queue_Query(&Uart2queue,&find))//队列查询
	{
		HAL_Delay(50);
		while(Queue_Get(&Uart2queue,&Uart3fifo.Txbuff[i++]))
		{
			;
		}
		Uart3fifo.Txbuff[i++] = '@';
		Uart3fifo.Txbuff[i] = 0;
		printf("Queue_Get_t:%s\r\n",Uart3fifo.Txbuff);
	}
}


#ifdef user_fifo
void uart1_idle()//适用于fifo
{
	uint8_t temp;
	if((__HAL_UART_GET_FLAG(&huart1,UART_FLAG_RXNE)!=RESET))//receive data
	{
		temp = ((huart1.Instance->DR)&0xFF);
		Queue_Put(&Uart1queue,&temp);
		__HAL_UART_CLEAR_FLAG(&huart1,UART_FLAG_RXNE);//clear receive irq		
	}

}
#else

void uart1_idle()//适用用于结构体
{
	uint8_t temp;
	if((__HAL_UART_GET_FLAG(&huart1,UART_FLAG_RXNE)!=RESET))//receive data
	{
		temp = (uint8_t)(huart1.Instance->DR&(uint8_t)0x00FF);
		__HAL_UART_CLEAR_FLAG(&huart1,UART_FLAG_RXNE);//clear receive irq
		if(Uart1.status == uart1head)
		{
			Uart1.status = uart1read;
			Uart1.len = 0;
			Uart1.buff[Uart1.len++] = temp;
			__HAL_UART_ENABLE_IT(&huart1,UART_IT_IDLE);//start idle irq
		}
		else if(Uart1.status == uart1read)
		{
			Uart1.buff[Uart1.len++] = temp;
		}
	}
	if((__HAL_UART_GET_FLAG(&huart1,UART_FLAG_IDLE)!=RESET))//receive stop 
	{
		Uart1.status = uart1over;
		__HAL_UART_CLEAR_FLAG(&huart1,UART_FLAG_IDLE);
		__HAL_UART_ENABLE_IT(&huart1,UART_IT_RXNE);
		__HAL_UART_DISABLE_IT(&huart1,UART_IT_IDLE);
	}
}
#endif

/**
* @brief This function handles USART1 global interrupt.
*/
void USART1_IRQHandler(void)
{
	//HAL_UART_IRQHandler(&huart1);
	uart1_idle();
}
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	uint8_t temp=0;
	if(huart->Instance == USART1)
	{
		HAL_UART_Receive_IT(&huart1,&temp,1);
	}
	else if(huart->Instance == USART2)
	{
		HAL_UART_Receive_IT(&huart2,&temp,1);
	}	
}


void uart2_idle()
{
	uint8_t temp;
	if((__HAL_UART_GET_FLAG(&huart2,UART_FLAG_RXNE)!=RESET))//receive data
	{
		temp = ((huart2.Instance->DR)&0xFF);
		Queue_Put(&Uart2queue,&temp);
		__HAL_UART_CLEAR_FLAG(&huart2,UART_FLAG_RXNE);//clear receive irq		
	}
}



/**
* @brief This function handles USART2 global interrupt.
*/
void USART2_IRQHandler(void)
{
	//HAL_UART_IRQHandler(&huart2);
	uart2_idle();
}


















/* USER CODE BEGIN 1 */
#ifdef debug_print
struct __FILE 
{ 
	int handle; 

}; 
FILE __stdout;       
//定义_sys_exit()以避免使用半主机模式    
void _sys_exit(int x) 
{ 
	x = x; 
} 
int fputc(int ch, FILE *f)
{      
	while((USART2->SR&0X40)==0)
		;
    USART2->DR = (uint8_t)ch;      
	return ch;
}
#endif
/* USER CODE END 1 */

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/







