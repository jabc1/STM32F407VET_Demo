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
	esp_uart.Txbuff[i] = 0;//������־
	
	strx=strstr((const char*)esp_uart.Txbuff,(const char*)str);//��ǰ���ַ����в���ack������
	return (u8*)strx;//�����ҵ����ַ������д���
}
/*
 *����0��ʾ���ͳɹ�
 *����1��ʾ����ʧ��
 */
u8 esp_8266_send_cmd(u8 *cmd,u8 *ack,u16 waittime)
{
	u8 res=0,temp;
	printf("%s\r\n",cmd);//��������
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
			res = 1;//��ʾ����ʧ��
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
	if(!esp_8266_send_cmd("AT+CIPMUX=1","OK",200))//0�������ӣ�1��������
	{
		printf("succ\r\n");
	}
}





