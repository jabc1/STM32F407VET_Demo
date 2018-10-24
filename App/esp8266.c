#include "esp8266.h"
void eps8266_reset()
{
//	SET_GPIO_L(ESP_GPIO);
//	SysTick_delay_ms(200);
//	SET_GPIO_H(ESP_GPIO);
//	SysTick_delay_ms(200);
}
_IDINFO Idinfo;
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
	strx=strstr((const char*)&esp_uart.Txbuff[0],(const char*)str);//从前面字符串中查找ack并返回
	return (u8*)strx;//返回找到的字符串进行处理
}
u8* esp_8266_check_cmd1(u8 *str)//STAMAC
{
	u8 *strx=NULL;
	_Uart2fifo esp_uart;
	u16 i = 0;
	
	strx = (u8 *)malloc(100 * sizeof(u8)); 
	if (NULL == strx)
	{ 
		return NULL;
	}
	while(Queue_Get(&Uart2queue,&esp_uart.Txbuff[i++]))
	{
		;
	}
	esp_uart.Txbuff[i] = 0;//结束标志
	strx=strstr((const char*)&esp_uart.Txbuff[0],(const char*)str);//从前面字符串中查找ack并返回
	strncpy(&Idinfo.macbuff[0],(u8 *)strx,60);
	free(strx);
	return (u8*)strx;//返回找到的字符串进行处理
}
u8* esp_8266_check_cmd2(u8 *str)//STAIP
{
	u8 *strx=NULL;
	_Uart2fifo esp_uart;
	u16 i = 0;
	
	strx = (u8 *)malloc(100 * sizeof(u8)); 
	if (NULL == strx)
	{ 
		return NULL;
	}
	while(Queue_Get(&Uart2queue,&esp_uart.Txbuff[i++]))
	{
		;
	}
	esp_uart.Txbuff[i] = 0;//结束标志
	strx=strstr((const char*)&esp_uart.Txbuff[0],(const char*)str);//从前面字符串中查找ack并返回
	strncpy(&Idinfo.ipbuff[0],(u8 *)strx,60);
	free(strx);
	return (u8*)strx;//返回找到的字符串进行处理
}
/*
 *返回0表示发送成功
 *返回1表示发送失败
 */
u8 esp_8266_send_cmd(u8 *cmd,u8 *ack,u16 waittime)
{
	u8 res=0,temp;
	printf("%s",cmd);//发送命令
	if(ack&&waittime)
	{
		while(--waittime)
		{
			SysTick_delay_ms(10);
			if(Queue_Query(&Uart2queue,&temp))
			{
				if(NULL==strcmp("STAIP",ack))
				{
					SysTick_delay_ms(50);
					if(esp_8266_check_cmd2(ack))
					{
						break;
					}					
				}
				else if(NULL==strcmp("STAMAC",ack))
				{
					SysTick_delay_ms(50);
					if(esp_8266_check_cmd1(ack))
					{
						break;
					}					
				}
				else
				{
					if(esp_8266_check_cmd(ack))
					{
						break;
					}
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


void esp8266_init()
{
	eps8266_reset();
	while(esp_8266_send_cmd("AT\r\n","OK",20));//检查WIFI模块是否在线
	while(esp_8266_send_cmd("ATE0\r\n","OK",20));//关闭回显
	esp_8266_send_cmd(CWMODE,"OK",350);//配置wifi mode
	SysTick_delay_ms(500);
	esp_8266_send_cmd(RST,"OK",300);//重启模块,设置摸得生效
	SysTick_delay_ms(500);
	while(esp_8266_send_cmd(CWJAP,"OK",500));//连接wifi
	while(esp_8266_send_cmd(CIFSR,"STAMAC",300));//查询wifi信息
	while(esp_8266_send_cmd(CIFSR,"STAIP",300));//查询wifi信息
	SysTick_delay_ms(500);
	esp_8266_send_cmd(CIPMUX,"OK",300);//设置但连接
	SysTick_delay_ms(500);
	esp_8266_send_cmd(CIPMODE1,"OK",300);//设置透传模式
	SysTick_delay_ms(500);
	esp_8266_send_cmd(CIPSTART,"OK",300);//连接远端
	SysTick_delay_ms(500);
	esp_8266_send_cmd(CIPSEND,">",200);//进入透传模式
	SysTick_delay_ms(500);
	printf("%s","A2 1000,5554443733078,0002,20181024AA,0000,00,0818030626,,,,0000,\r\n");
//	SysTick_delay_ms(200);
//	printf("%s",CLOSE1);
//	esp_8266_send_cmd(CLOSE2,"OK",500);

}








