#ifndef _esp_8266_h
#define _esp_8266_h

#include "uart.h"
#include "delay.h"
#include "queue_jk.h"




#define		CIPSTEST	"AT\r\n"//≤‚ ‘÷∏¡Ó

#define 	AT          "AT\r\n"		//≤‚ ‘ƒ£øÈ «∑Ò∆Ù∂Ø
#define 	CWMODE      "AT+CWMODE=3\r\n"
#define 	RST         "AT+RST\r\n"
#define 	CIFSR       "AT+CIFSR\r\n"
#define 	CWJAP       "AT+CWJAP=LINK_001,0123456789\r\n"
#define 	CIPSTART    "AT+CIPSTART=TCP,192.168.1.100,3002\r\n"
#define 	CIPMODE0    "AT+CIPMODE=0\r\n"
#define 	CIPMODE1    "AT+CIPMODE=1\r\n"
#define 	CIPSEND     "AT+CIPSEND\r\n"
#define 	CIPSTATUS   "AT+CIPSTATUS\r\n"


void eps8266_reset(void);
u8 esp_8266_send_cmd(u8 *cmd,u8 *ack,u16 waittime);
void esp8266_test(void);






#endif




