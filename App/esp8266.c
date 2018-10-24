#include "esp8266.h"
void eps8266_reset()
{
	;
}

u8* esp_8266_check_cmd(u8 *str)
{
	char *strx=0;
	_Uart2fifo esp_uart;
	u16 i = 0;
	
	while(Queue_Get(&Uart2queue,&esp_uart.Txbuff[i++]))
	{
		;
	}
	esp_uart.Txbuff[i] = 0;//结束标志
	
	strx=strstr((const char*)esp_uart.Txbuff,(const char*)str);//从前面字符串中查找ack并返回
	return (u8*)strx;//返回找到的字符串进行处理
}
/*
 *返回0表示发送成功
 *返回1表示发送失败
 */
u8 esp_8266_send_cmd(u8 *cmd,u8 *ack,u16 waittime)
{
	u8 res=0,temp;
	printf("%s\r\n",cmd);//发送命令
	if(ack&&waittime)
	{
		while(--waittime)
		{
			SysTick_delay_ms(10);
			if(Queue_Query(&Uart2queue,&temp))
			{
				if(esp_8266_check_cmd(ack))
				{
					printf("find=%s\r\n",ack);
					break;
				}
			}
		}
		if(waittime == 0)
		{
			res = 1;//表示发送失败
		}
	}
	return res;
}
void esp8266_function()
{
	;
}


void esp8266_test()
{
	if(!esp_8266_send_cmd("AT+CIPMUX=1","OK",200))//0：单连接，1：多连接
	{
		printf("succ\r\n");
	}
}





