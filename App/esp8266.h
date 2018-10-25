#ifndef _esp_8266_h
#define _esp_8266_h

#include "uart.h"
#include "delay.h"
#include "queue_jk.h"
#include "gpio.h"

#define 	AT          "AT\r\n"		//����ģ���Ƿ������᷵��ok
#define		AT1			"AT+RESTORE\r\n"//�ָ���������
#define 	CWMODE      "AT+CWMODE=3\r\n"//����ΪSTA+APģʽ
#define 	RST         "AT+RST\r\n"//��λ����

#define 	CWJAP       "AT+CWJAP=\"LINK_001\",\"0123456789\"\r\n"//����·����

#define test
#ifdef test
#define 	CIPSTART    "AT+CIPSTART=\"TCP\",\"192.168.1.101\",3033\r\n"//����Զ��
#else
#define 	CIPSTART    "AT+CIPSTART=\"TCP\",\"119.23.75.37\",3000\r\n"//����Զ��
#endif

#define		CIPMUX		"AT+CIPMUX=0\r\n"//���õ����ӣ�͸��ģʽֻ�����õ�����
#define 	CIPMODE1    "AT+CIPMODE=1\r\n"//����͸��ģʽ
#define 	CIPSEND     "AT+CIPSEND\r\n"//����͸��ģʽ,����>



#define 	CIPSTATUS   "AT+CIPSTATUS\r\n"//��ѯ����״̬
//��ѯIP����Ϊ��STA��AP����ģʽ������������MAC��IP����������192.168.x.x������IP
#define 	CIFSR       "AT+CIFSR\r\n"


#define		BACKAT		"+++"//����ָ��ģʽ
#define		CLOSESER	"AT+CIPCLOSE\r\n"//�Ͽ��������������
#define		EXITLINK	"AT+CWQAP\r\n"//�˳���·����������

#define		idlen		60

#pragma pack(push,1)
typedef struct 
{
	u8 buff[idlen];
	u8 ipbuff[4];
	u8 macbuff[12];
}_IDINFO;
#pragma pack(pop)

extern _IDINFO Idinfo;

u8 esp_8266_send_cmd(u8 *cmd,u8 *ack,u16 waittime);
u8* esp_8266_check_cmd(u8 *str);
u8* esp_8266_check_cmd2(u8 *str);
void eps8266_reset(void);
void esp8266_init(void);
void esp8266_function(void);
void esp8266_softreset(void);




#endif




