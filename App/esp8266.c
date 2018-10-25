#include "esp8266.h"

_IDINFO Idinfo;
u8 *infobuff[15];

u8 get_link_info(u8 *scr)
{
	const char *s = ",+:\".\r\n";
	u8 *token,i=0;

	for(i=0;i<15;i++)
	{
		infobuff[i] = NULL;
	}
	i=0;
	token = (u8 *)strtok(scr, s);
	while( token != NULL ) 
	{
		infobuff[i++] = token;
		token = strtok(NULL, s);
	}
	
	if((NULL==strcmp((const char *)"STAIP",infobuff[0])) \
		&&(NULL==strcmp((const char *)"CIFSR",infobuff[5])) \
		&&(NULL==strcmp((const char *)"STAMAC",infobuff[6])))
	{
		Idinfo.ipbuff[0] = atoi((char *)infobuff[1]);
		Idinfo.ipbuff[1] = atoi((char *)infobuff[2]);
		Idinfo.ipbuff[2] = atoi((char *)infobuff[3]);
		Idinfo.ipbuff[3] = atoi((char *)infobuff[4]);
		
//		strcpy (Idinfo.macbuff,infobuff[7]);
//		strcat (Idinfo.macbuff,infobuff[8]);
//		strcat (Idinfo.macbuff,infobuff[9]);
//		strcat (Idinfo.macbuff,infobuff[10]);
//		strcat (Idinfo.macbuff,infobuff[11]);
//		strcat (Idinfo.macbuff,infobuff[12]);
		sprintf(Idinfo.macbuff, "%s%s%s%s%s%s",infobuff[7],infobuff[8],infobuff[9], \
												infobuff[10],infobuff[11],infobuff[12]);
		return true;
	}
	else
	{
		return false;
	}
	
}


u8* esp_8266_check_cmd(u8 *str)
{
	char *strx=0;
	static _Uart2fifo esp_uart;
	u16 i = 0;
	memset(esp_uart.Txbuff,0,sizeof(esp_uart.Txbuff));
	while(Queue_Get(&Uart2queue,&esp_uart.Txbuff[i++]))
	{
		;
	}
	esp_uart.Txbuff[i] = 0;//������־
	strx=strstr((const char*)&esp_uart.Txbuff[0],(const char*)str);//��ǰ���ַ����в���ack������
	return (u8*)strx;//�����ҵ����ַ������д���
}

u8* esp_8266_check_cmd2(u8 *str)//STAIP
{
	u8 *strx=NULL;
	static _Uart2fifo esp_uart;
	u16 i = 0;
	memset(esp_uart.Txbuff,0,sizeof(esp_uart.Txbuff));
//	strx = (u8 *)malloc(100 * sizeof(u8)); 
//	if (NULL == strx)
//	{ 
//		return NULL;
//	}
	while(Queue_Get(&Uart2queue,&esp_uart.Txbuff[i++]))
	{
		;
	}
	esp_uart.Txbuff[i] = 0;//������־
	strx=strstr((const char*)&esp_uart.Txbuff[0],(const char*)str);//��ǰ���ַ����в���ack������
	strncpy(&Idinfo.buff[0],(u8 *)strx,60);

	if(get_link_info(&Idinfo.buff[0]))//��ȡIP��Ϣ
	{
		return (u8 *)strx;
	}
	else
	{
		return NULL;
	}
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
				if(NULL==strcmp((const char *)"STAIP",(char *)ack))
				{
					SysTick_delay_ms(150);
					if(esp_8266_check_cmd2(ack))
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

void eps8266_reset()
{
//	SET_GPIO_L(ESP_GPIO);
//	SysTick_delay_ms(200);
//	SET_GPIO_H(ESP_GPIO);
//	SysTick_delay_ms(200);
}
void esp8266_softreset()
{
	while(esp_8266_send_cmd(BACKAT,"+++",200));
	SysTick_delay_xms(1500);
	while(esp_8266_send_cmd(CLOSESER,"OK",200));
	while(esp_8266_send_cmd(EXITLINK,"OK",200));
}

void esp8266_function()
{
	;
}

void esp8266_init()
{
	eps8266_reset();
	while(esp_8266_send_cmd(AT1,"OK",20));//���WIFIģ���Ƿ�����
	while(esp_8266_send_cmd("AT\r\n","OK",20));//���WIFIģ���Ƿ�����
	while(esp_8266_send_cmd("ATE0\r\n","OK",20));//�رջ���
	esp_8266_send_cmd(CWMODE,"OK",350);//����wifi mode
	esp_8266_send_cmd(RST,"OK",300);//����ģ��,����������Ч
	while(esp_8266_send_cmd(CWJAP,"OK",500));//����wifi
	while(esp_8266_send_cmd(CIFSR,"STAIP",300));//��ѯwifi��Ϣ
	while(esp_8266_send_cmd(CIPMUX,"OK",300));//���õ�����
	esp_8266_send_cmd(CIPMODE1,"OK",300);//����͸��ģʽ
	esp_8266_send_cmd(CIPSTART,"OK",300);//����Զ��
	esp_8266_send_cmd(CIPSEND,">",200);//����͸��ģʽ
	printf("%s","A2 1000,5554443733078,0002,20181025AA,0000,00,0818030626,,,,0000,\r\n");
}








