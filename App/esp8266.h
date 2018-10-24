#ifndef _esp_8266_h
#define _esp_8266_h

#include "uart.h"
#include "delay.h"
#include "queue_jk.h"
#include "gpio.h"

#define 	AT          "AT\r\n"		//测试模块是否启动会返回ok
#define		AT1			"AT+RESTORE\r\n"//恢复出厂设置
#define 	CWMODE      "AT+CWMODE=3\r\n"//设置为STA+AP模式
#define 	RST         "AT+RST\r\n"//复位命令

#define 	CWJAP       "AT+CWJAP=\"LINK_001\",\"0123456789\"\r\n"//连接路由器
#define 	CIPSTART    "AT+CIPSTART=\"TCP\",\"119.23.75.37\",3000\r\n"//连接远端
#define		CIPMUX		"AT+CIPMUX=0\r\n"//设置但连接，透传模式只能设置但连接
#define 	CIPMODE1    "AT+CIPMODE=1\r\n"//设置透传模式
#define 	CIPSEND     "AT+CIPSEND\r\n"//进入透传模式,返回>

#define		CLOSE1		"+++"
#define		CLOSE2		"AT+CIPCLOSE\r\n"//"+++"//关闭透传

#define 	CIPSTATUS   "AT+CIPSTATUS\r\n"//查询网络状态
//查询IP，因为有STA和AP两个模式，所以有两组MAC和IP，常见的是192.168.x.x局域网IP
#define 	CIFSR       "AT+CIFSR\r\n"

#define		idlen		150
#pragma pack(push,1)
typedef struct _IDINFO
{
	u8 buff[idlen];
	u8 ipbuff[20];
	u8 macbuff[20];
}_IDINFO;
#pragma pack(pop) 

extern _IDINFO Idinfo;



void eps8266_reset(void);
u8 esp_8266_send_cmd(u8 *cmd,u8 *ack,u16 waittime);
u8* esp_8266_check_cmd(u8 *str);
u8* esp_8266_check_cmd2(u8 *str);
void esp8266_init(void);
void esp8266_function(void);





#endif




