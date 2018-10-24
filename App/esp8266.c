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
	esp_uart.Txbuff[i] = 0;//������־
	strx=strstr((const char*)&esp_uart.Txbuff[0],(const char*)str);//��ǰ���ַ����в���ack������
	return (u8*)strx;//�����ҵ����ַ������д���
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
	esp_uart.Txbuff[i] = 0;//������־
	strx=strstr((const char*)&esp_uart.Txbuff[0],(const char*)str);//��ǰ���ַ����в���ack������
	strncpy(&Idinfo.macbuff[0],(u8 *)strx,60);
	free(strx);
	return (u8*)strx;//�����ҵ����ַ������д���
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
	esp_uart.Txbuff[i] = 0;//������־
	strx=strstr((const char*)&esp_uart.Txbuff[0],(const char*)str);//��ǰ���ַ����в���ack������
	strncpy(&Idinfo.ipbuff[0],(u8 *)strx,60);
	free(strx);
	return (u8*)strx;//�����ҵ����ַ������д���
}
/*
 *����0��ʾ���ͳɹ�
 *����1��ʾ����ʧ��
 */
u8 esp_8266_send_cmd(u8 *cmd,u8 *ack,u16 waittime)
{
	u8 res=0,temp;
	printf("%s",cmd);//��������
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
			res = 1;//��ʾ����ʧ��
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
	while(esp_8266_send_cmd("AT\r\n","OK",20));//���WIFIģ���Ƿ�����
	while(esp_8266_send_cmd("ATE0\r\n","OK",20));//�رջ���
	esp_8266_send_cmd(CWMODE,"OK",350);//����wifi mode
	SysTick_delay_ms(500);
	esp_8266_send_cmd(RST,"OK",300);//����ģ��,����������Ч
	SysTick_delay_ms(500);
	while(esp_8266_send_cmd(CWJAP,"OK",500));//����wifi
	while(esp_8266_send_cmd(CIFSR,"STAMAC",300));//��ѯwifi��Ϣ
	while(esp_8266_send_cmd(CIFSR,"STAIP",300));//��ѯwifi��Ϣ
	SysTick_delay_ms(500);
	esp_8266_send_cmd(CIPMUX,"OK",300);//���õ�����
	SysTick_delay_ms(500);
	esp_8266_send_cmd(CIPMODE1,"OK",300);//����͸��ģʽ
	SysTick_delay_ms(500);
	esp_8266_send_cmd(CIPSTART,"OK",300);//����Զ��
	SysTick_delay_ms(500);
	esp_8266_send_cmd(CIPSEND,">",200);//����͸��ģʽ
	SysTick_delay_ms(500);
	printf("%s","A2 1000,5554443733078,0002,20181024AA,0000,00,0818030626,,,,0000,\r\n");
//	SysTick_delay_ms(200);
//	printf("%s",CLOSE1);
//	esp_8266_send_cmd(CLOSE2,"OK",500);

}








