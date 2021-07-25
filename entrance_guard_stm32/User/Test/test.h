#ifndef  __TEST_H
#define	 __TEST_H



#include "stm32f10x.h"
#include "./lcd/bsp_xpt2046_lcd.h"



/********************************** �û���Ҫ���õĲ���**********************************/
#define      macUser_ESP8266_ApSsid                       "XM8"                //Ҫ���ӵ��ȵ������
#define      macUser_ESP8266_ApPwd                        "pppppppp"           //Ҫ���ӵ��ȵ����Կ

#define      macUser_ESP8266_TcpServer_IP                 "192.168.43.6"      //Ҫ���ӵķ������� IP
#define      macUser_ESP8266_TcpServer_Port               "1454"               //Ҫ���ӵķ������Ķ˿�



/********************************** �ⲿȫ�ֱ��� ***************************************/
extern volatile uint8_t ucTcpClosedFlag;

static uint16_t TextColor  = BLUE;//������ɫ

/********************************** ���Ժ������� ***************************************/
void                     ESP8266_StaTcpClient_UnvarnishTest  ( void );
void IC_test ( void );
void nopass(uint8_t reason);
void nopass2(uint8_t reason2);
void pass(void);
void ESP8266_isconnect(void);
void ESP8266_Connect(void);
void Send_sno(uint32_t n);


#endif

