#ifndef  __TEST_H
#define	 __TEST_H



#include "stm32f10x.h"
#include "./lcd/bsp_xpt2046_lcd.h"



/********************************** 用户需要设置的参数**********************************/
#define      macUser_ESP8266_ApSsid                       "XM8"                //要连接的热点的名称
#define      macUser_ESP8266_ApPwd                        "pppppppp"           //要连接的热点的密钥

#define      macUser_ESP8266_TcpServer_IP                 "192.168.43.6"      //要连接的服务器的 IP
#define      macUser_ESP8266_TcpServer_Port               "1454"               //要连接的服务器的端口



/********************************** 外部全局变量 ***************************************/
extern volatile uint8_t ucTcpClosedFlag;

static uint16_t TextColor  = BLUE;//字体颜色

/********************************** 测试函数声明 ***************************************/
void                     ESP8266_StaTcpClient_UnvarnishTest  ( void );
void IC_test ( void );
void nopass(uint8_t reason);
void nopass2(uint8_t reason2);
void pass(void);
void ESP8266_isconnect(void);
void ESP8266_Connect(void);
void Send_sno(uint32_t n);


#endif

