#include "wifipack.h"
/**
******************************************************************************
* @file   esp8266.c
* @author  JKk
* @date    2018/10/24
* @brief   ��Ҫʵ�����ݰ�������͹���
******************************************************************************
*/
u8 sendbuff[100];
void senf_pack()
{
	u8 len = 0;
    char str[16];
	memset(sendbuff,0,sizeof(sendbuff));
    memcpy(sendbuff+len,"send 1000,",10);//��ͷ
    len += 10;

    memcpy(sendbuff+len,Idinfo.macbuff,12);//DeviceID mac
    len += 12;
	
    sprintf(str,",%02X%02X,",0xa1,0x1a);    //�豸����汾
    memcpy(sendbuff+len,str,6);
    len +=6;

    sprintf(str,"%02X%02X%02X%02X%02X,",0xaa,0xaa,0xaa,0xaa,0xaa);   //��ǩID
    memcpy(sendbuff+len,str,11);
    len +=11;

    sprintf(str,"%04X,%02X,",0x2211,0x11);//��ǩ�汾�͵���
    memcpy(sendbuff+len,str,8);
    len +=8;

    sprintf(str,"%02X%02X%02X%02X%02X,",0x08,0x08,0x08,0x08,0x08);//ʱ��
    memcpy(sendbuff+len,str,11);
    len +=11;
    sprintf(str,",,,0000,\r\n");//end
    memcpy(sendbuff+len,str,10);
    len += 10;
	
	while(esp_8266_send_cmd(sendbuff,"1",300));//senf data
}







