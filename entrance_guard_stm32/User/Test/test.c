#include <stdio.h>  
#include <string.h>  
 #include "stm32f10x.h"
#include "./usart/bsp_usart.h"	
#include "./lcd/bsp_ili9341_lcd.h"
#include "./flash/bsp_spi_flash.h"
#include "./SysTick/bsp_SysTick.h"
#include "rc522_config.h"
#include "rc522_function.h"
#include "./timer/timer.h"
#include "./timer2/timer2.h"
#include "./exti/bsp_exti.h"
#include "./dht11/bsp_dht11.h"
#include "./dwt_delay/core_delay.h" 
#include "./MLX90614/mlx90614.h"
#include "./led/bsp_led.h"
#include "./myled/my_led.h"
#include "./ESP8266/bsp_esp8266.h"
#include "./Test/test.h"
#include "./pelette/palette.h"
#include <stdbool.h>
#define LED_CMD_NUMBER   6

volatile uint32_t time = 0;  //时间
uint8_t mode = 1;  //0就是进(按k1），1是出(按k2）

DHT11_Data_TypeDef DHT11_Data;
uint32_t inputsno;

uint8_t KeyValue[]={0xFF ,0xFF, 0xFF, 0xFF, 0xFF, 0xFF};   // 卡A密钥

//指令数据
char *ledCmd[6] = { "0not_stu","1high_temp","2time_over","3time_over;high_temp","pass","inputsno" };
             
volatile uint8_t ucTcpClosedFlag = 0;


/**
  * @brief  根据指令执行相应的任务
  */
void Get_ESP82666_Cmd( char * cmd)
{
	uint8_t i;
	for(i = 0;i < LED_CMD_NUMBER; i++)
	{
     if(( bool ) strstr ( cmd, ledCmd[i] ))
		 break;
	}
	switch(i)
    {
      case 0:
        nopass2(0);
      break;
      case 1:
        nopass2(1);
      break;
      case 2:
        nopass2(2);
      break;
      case 3:
        nopass2(3);
			case 4:
        pass();
      break;
			case 5:
        LED_GREEN_ON;
				LED_RED_ON;
				Delay_us(500000);  //0.5s
				LED_GREEN_OFF;
				LED_RED_OFF;
      break;

      default:
        
        break;      
    }   
}


// ESP8266连接电脑函数
void ESP8266_Connect ( void )
{
	printf ( "\r\n正在配置 ESP8266 ......\r\n" );

	macESP8266_CH_ENABLE();
	
	ESP8266_AT_Test ();
	
	ESP8266_Net_Mode_Choose ( STA );

  while ( ! ESP8266_JoinAP ( macUser_ESP8266_ApSsid, macUser_ESP8266_ApPwd ) );	
	
	ESP8266_Enable_MultipleId ( DISABLE );
	
	while ( !	ESP8266_Link_Server ( enumTCP, macUser_ESP8266_TcpServer_IP, macUser_ESP8266_TcpServer_Port, Single_ID_0 ) );
	
	while ( ! ESP8266_UnvarnishSend () );
	
	LED1_ON;
	LED_YELLOW_ON;
	printf ( "\r\n配置 ESP8266 完毕\r\n" );
}

//确定是否需要重新连接函数
void ESP8266_isconnect(void)
{
	uint8_t ucStatus;
	
	if ( ucTcpClosedFlag )                                             //检测是否失去连接
	{
		LED1_OFF;
		ESP8266_ExitUnvarnishSend ();                                    //退出透传模式
		
		do ucStatus = ESP8266_Get_LinkStatus ();                         //获取连接状态
		while ( ! ucStatus );
		
		if ( ucStatus == 4 )                                             //确认失去连接后重连
		{
			printf ( "\r\n正在重连热点和服务器 ......\r\n" );
			
			while ( ! ESP8266_JoinAP ( macUser_ESP8266_ApSsid, macUser_ESP8266_ApPwd ) );
			
			while ( !	ESP8266_Link_Server ( enumTCP, macUser_ESP8266_TcpServer_IP, macUser_ESP8266_TcpServer_Port, Single_ID_0 ) );
			
			printf ( "\r\n重连热点和服务器成功\r\n" );

		}
		
		while ( ! ESP8266_UnvarnishSend () );		
		
	}
	LED1_ON;
	LED_YELLOW_ON;
}

void pass(void)
{
	LED_GREEN_ON;
	Delay_us(500000);  //0.5s
	LED_GREEN_OFF;
}

void nopass2(uint8_t reason2)
{
	LED_RED_ON;	
	LCD_SetTextColor(RED);
	if(reason2 == 0)
	{
		ILI9341_DisplayStringEx(92,LINE(8),16,16,(uint8_t *)"NOT STU",0);
	}
	if(reason2 == 1)
	{
		ILI9341_DisplayStringEx(144,LINE(8),16,16,(uint8_t *)"HIGH TEMP",0);
	}
	if(reason2 == 2)
	{
		ILI9341_DisplayStringEx(24,LINE(8),16,16,(uint8_t *)"OVER TIME",0);
	}
	if(reason2 == 3)
	{
		ILI9341_DisplayStringEx(24,LINE(8),16,16,(uint8_t *)"OVER TIME",0);
		ILI9341_DisplayStringEx(144,LINE(8),16,16,(uint8_t *)"HIGH TEMP",0);
	}
	
	LCD_SetTextColor(TextColor);	
	Delay_us(500000);  //0.5s
	ILI9341_Clear(0,LINE(8),240,16);
	LED_RED_OFF;
}

void nopass(uint8_t reason)
{
	LED_RED_ON;
	
	LCD_SetTextColor(RED);
	if(reason&00000001)
	{
		ILI9341_DisplayStringEx(24,LINE(8),16,16,(uint8_t *)"OVER TIME",0);
	}
	if(reason&00000010)
	{
		ILI9341_DisplayStringEx(144,LINE(8),16,16,(uint8_t *)"HIGH TEMP",0);
	}

	LCD_SetTextColor(TextColor);
	
	Delay_us(500000);  //0.5s
	ILI9341_Clear(0,LINE(8),240,16);
	LED_RED_OFF;
}

void Send_sno(uint32_t n)
{

	char WiFiStr2 [ 100 ]= { 0 };
	int bodyTemperature2;
	char bodyTemperatureStr2 [ 30 ]= { 0 };
	printf ("11sno:%u\r\n", n );

	LED_YELLOW_OFF;
	bodyTemperature2 = SMBus_ReadTemp();
	sprintf ( bodyTemperatureStr2, "temputure:%d", bodyTemperature2);				 										 	         
	ILI9341_DispStringLine_EN(LINE(6) , (char* )bodyTemperatureStr2 );
	if(mode == 1)
	{
		sprintf ( WiFiStr2, "SNOOUT:sno.%u;time.%d:%d:%d;temperature.%d", n,time/3600, (time%3600)/60, (time%3600)%60 , bodyTemperature2);					 	         
		ESP8266_SendString ( ENABLE, WiFiStr2, 100, Single_ID_0 );
	}else if(mode == 0)
	{
		sprintf ( WiFiStr2, "SNOIN:sno.%u;time.%d:%d:%d;temperature.%d", n,time/3600, (time%3600)/60, (time%3600)%60 , bodyTemperature2);					 	         
		ESP8266_SendString ( ENABLE, WiFiStr2, 100, Single_ID_0 );
	}else if(mode == 3)
	{
		inputsno = n;
	}
	
	LED_YELLOW_ON;	
}


void IC_test ( void )
{
	uint8_t problem=00000000;
	int bodyTemperature;
	char bodyTemperatureStr [ 30 ];
	char WiFiStr [ 100 ]= { 0 };
	
	  uint16_t i;
	
	uint32_t readValue;
	uint32_t temp;
	char cStr [ 30 ] = { 0 };
  uint8_t ucArray_ID [ 4 ];    /*先后存放IC卡的类型和UID(IC卡序列号)*/                                                                                         
	uint8_t ucStatusReturn;      /*返回状态*/ 
  while ( 1 )
  { 
		//检测是否收到指令
		if(strEsp8266_Fram_Record .InfBit .FramFinishFlag)                             //如果接收到了ESP8266的数据
		{                                                      
			for(i = 0;i < strEsp8266_Fram_Record .InfBit .FramLength; i++)               
			{
				 USART_SendData( DEBUG_USARTx ,strEsp8266_Fram_Record .Data_RX_BUF[i]);    
				 while(USART_GetFlagStatus(DEBUG_USARTx,USART_FLAG_TC)==RESET){}
			}
			 strEsp8266_Fram_Record .InfBit .FramLength = 0;                             //接收数据长度置零
			 strEsp8266_Fram_Record.InfBit.FramFinishFlag = 0;                           //接收标志置零
			 Get_ESP82666_Cmd(strEsp8266_Fram_Record .Data_RX_BUF);                      //检查一下是不是命令
		}
		
		
    /*寻卡，寻找未休眠的卡*/
		if ( ( ucStatusReturn = PcdRequest ( PICC_REQIDL, ucArray_ID ) ) != MI_OK )  
       /*若失败再次寻卡*/
			ucStatusReturn = PcdRequest ( PICC_REQIDL, ucArray_ID );		                                                

		if ( ucStatusReturn == MI_OK  )
		{
      /*防冲撞（当有多张卡进入读写器操作范围时，防冲突机制会从其中选择一张进行操作）*/
			if ( PcdAnticoll ( ucArray_ID ) == MI_OK )                                                                   
			{
				ILI9341_Clear(0,64,240,32);
				LED_YELLOW_OFF;
				bodyTemperature = SMBus_ReadTemp();
				sprintf ( bodyTemperatureStr, "temputure:%d", bodyTemperature);				 										 	         
				ILI9341_DispStringLine_EN(LINE(6) , (char* )bodyTemperatureStr );
				
				if(bodyTemperature > 28)
				{
					problem |= 00000010;
				}
				
				if(mode == 1)  //写时间 和 读  OUT
				{
					PcdSelect(ucArray_ID);		
					PcdAuthState( PICC_AUTHENT1A, 0x12, KeyValue, ucArray_ID );//校验密码 
					WriteAmount(0x12,time); 
					if(ReadAmount(0x12,&readValue) == MI_OK)	
					{		
						
						//sprintf ( cStr, "The Card ID is: %02X%02X%02X%02X",ucArray_ID [0], ucArray_ID [1], ucArray_ID [2],ucArray_ID [3] );
						//ILI9341_DispStringLine_EN(LINE(3) , (char* )cStr ); 
						
						sprintf ( cStr, "Time:%dh %dm %ds", readValue/3600, (readValue%3600)/60, (readValue%3600)%60);					 	         
						ILI9341_DispStringLine_EN(LINE(5) , (char* )cStr ); 
						
						sprintf ( WiFiStr, "OUT:id.%02X%02X%02X%02X;time.%d:%d:%d;temperature.%d", ucArray_ID [0], ucArray_ID [1], ucArray_ID [2],ucArray_ID [3], 
						readValue/3600, (readValue%3600)/60, (readValue%3600)%60 , bodyTemperature);					 	         
						ESP8266_SendString ( ENABLE, WiFiStr, 100, Single_ID_0 );
						
						PcdHalt();
					}	
				}else if(mode == 0)  //读现在时间，算出去了的时间  IN
				{
					PcdSelect(ucArray_ID);	
					PcdAuthState( PICC_AUTHENT1A, 0x11, KeyValue, ucArray_ID );
					WriteAmount(0x11,time);
					
					if(ReadAmount(0x11,&readValue) == MI_OK)
					{
						//sprintf ( cStr, "The Card ID is: %02X%02X%02X%02X",ucArray_ID [0], ucArray_ID [1], ucArray_ID [2],ucArray_ID [3] );
						//ILI9341_DispStringLine_EN(LINE(3) , (char* )cStr );
						
						sprintf ( cStr, "Enter Time:%dh %dm %ds", time/3600, (time%3600)/60, (time%3600)%60);				 										 	         
						ILI9341_DispStringLine_EN(LINE(4) , (char* )cStr ); 
											
						if(ReadAmount(0x12,&readValue) == MI_OK)	
						{		
 
							
							temp = time-readValue;
							if(temp>1073741824) //防止先进后出的时候溢出
							{
								temp=1;
							}
							sprintf ( cStr, "How long:%dh %dm %ds", temp/3600, (temp%3600)/60, (temp%3600)%60);				 										 	         
							ILI9341_DispStringLine_EN(LINE(5) , (char* )cStr ); 
							
							sprintf ( WiFiStr, "IN:id.%02X%02X%02X%02X;time.%d:%d:%d;howlong.%d:%d:%d;temperature.%d", ucArray_ID [0], ucArray_ID [1], ucArray_ID [2],ucArray_ID [3], 
							time/3600, (time%3600)/60, (time%3600)%60 ,  temp/3600, (temp%3600)/60, (temp%3600)%60, bodyTemperature);					 	         
							ESP8266_SendString ( ENABLE, WiFiStr, 100, Single_ID_0 );
							
							
							if(temp > 3) //3秒
							{
								problem |=00000001;
							}
							
							PcdHalt();
						}
					}
				}else if(mode == 3)	//录卡模式
				{
					PcdSelect(ucArray_ID);
					sprintf ( cStr, "The Card ID is: %02X%02X%02X%02X",ucArray_ID [0], ucArray_ID [1], ucArray_ID [2],ucArray_ID [3] );
					ILI9341_DispStringLine_EN(LINE(4) , (char* )cStr );
					
					sprintf ( WiFiStr, "LK:id.%02X%02X%02X%02X;sno.%u", ucArray_ID [0], ucArray_ID [1], ucArray_ID [2],ucArray_ID [3], inputsno);					 	         
					ESP8266_SendString ( ENABLE, WiFiStr, 100, Single_ID_0 );
					PcdHalt();
				}
				LED_YELLOW_ON;	
				if(problem != 0x00)
				{
					nopass(problem);
				}else{
					pass();
				}
				problem=00000000;
			}						
		}		
		   
  }	
}

