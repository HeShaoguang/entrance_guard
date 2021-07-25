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
#include <stdbool.h>
	
volatile uint32_t time = 0;
uint8_t mode = 1;  //0就是进(按k1），1是出(按k2）

DHT11_Data_TypeDef DHT11_Data;

uint8_t KeyValue[]={0xFF ,0xFF, 0xFF, 0xFF, 0xFF, 0xFF};   // 卡A密钥

void pass(void)
{
	LED_GREEN_ON;
	Delay_us(500000);  //0.5s
	LED_GREEN_OFF;
}

void nopass(uint8_t reason)
{
	LED_RED_ON;
	
	LCD_SetTextColor(RED);
	if(reason&00000001)
	{
		ILI9341_DisplayStringEx(12,LINE(6),48,48,(uint8_t *)"OVER TIME",0);
	}
	if(reason&00000010)
	{
		ILI9341_DisplayStringEx(12,LINE(9),48,48,(uint8_t *)"HIGH TEMP",0);
	}
	if(mode == 1)
	{
		LCD_SetTextColor(BLUE);
	}else if(mode == 0){
		LCD_SetTextColor(GREEN);	
	}
	
	
	Delay_us(500000);  //0.5s
	ILI9341_Clear(0,LINE(6),240,100);
	LED_RED_OFF;
}

void IC_test ( void )
{
	uint8_t problem=00000000;
	float bodyTemperature;
	char bodyTemperatureStr [ 30 ];
	
	uint32_t readValue;
	uint32_t temp;
	char cStr [ 30 ];
  uint8_t ucArray_ID [ 4 ];    /*先后存放IC卡的类型和UID(IC卡序列号)*/                                                                                         
	uint8_t ucStatusReturn;      /*返回状态*/                                                                                           
  while ( 1 )
  {    
    /*寻卡，寻找未休眠的卡*/
		if ( ( ucStatusReturn = PcdRequest ( PICC_REQIDL, ucArray_ID ) ) != MI_OK )  
       /*若失败再次寻卡*/
			ucStatusReturn = PcdRequest ( PICC_REQIDL, ucArray_ID );		                                                

		if ( ucStatusReturn == MI_OK  )
		{
      /*防冲撞（当有多张卡进入读写器操作范围时，防冲突机制会从其中选择一张进行操作）*/
			if ( PcdAnticoll ( ucArray_ID ) == MI_OK )                                                                   
			{
				ILI9341_Clear(0,48,240,50);
				LED_YELLOW_ON;
				bodyTemperature = SMBus_ReadTemp();
				sprintf ( bodyTemperatureStr, "temputure:%f", bodyTemperature);				 										 	         
				ILI9341_DispStringLine_EN(LINE(16) , (char* )bodyTemperatureStr ); 
				if(bodyTemperature > 30)
				{
					problem |= 00000010;
				}
				
				if(mode == 1)  //写时间 和 读
				{
					PcdSelect(ucArray_ID);		
					PcdAuthState( PICC_AUTHENT1A, 0x12, KeyValue, ucArray_ID );//校验密码 
					WriteAmount(0x12,time); //写入金额
					if(ReadAmount(0x12,&readValue) == MI_OK)	//读取金额
					{		
						
						sprintf ( cStr, "The Card ID is: %02X%02X%02X%02X",ucArray_ID [0], ucArray_ID [1], ucArray_ID [2],ucArray_ID [3] );
						ILI9341_DispStringLine_EN(LINE(3) , (char* )cStr ); //在屏幕上面显示ID

						sprintf ( cStr, "Time:%dh %dm %ds", readValue/3600, (readValue%3600)/60, (readValue%3600)%60);					 	         
						ILI9341_DispStringLine_EN(LINE(5) , (char* )cStr ); 
						
						if(ReadAmount(0x11,&readValue) == MI_OK)
						{
							ILI9341_DispStringLine_EN(LINE(4),(char* )"sno:"); 
							ILI9341_DispNum(32,LINE(4),readValue,10,16);
						}
						PcdHalt();
					}	
				}else if(mode == 0)  //读现在时间，算出去了的时间
				{
					PcdSelect(ucArray_ID);		
					PcdAuthState( PICC_AUTHENT1A, 0x12, KeyValue, ucArray_ID );//校验密码 
					if(ReadAmount(0x12,&readValue) == MI_OK)	//读取金额
					{		
						sprintf ( cStr, "The Card ID is: %02X%02X%02X%02X",ucArray_ID [0], ucArray_ID [1], ucArray_ID [2],ucArray_ID [3] );
						ILI9341_DispStringLine_EN(LINE(3) , (char* )cStr ); //在屏幕上面显示ID
						
						temp = time-readValue;
						sprintf ( cStr, "Go Out Time:%dh %dm %ds", temp/3600, (temp%3600)/60, (temp%3600)%60);				 										 	         
						ILI9341_DispStringLine_EN(LINE(5) , (char* )cStr ); 
						
						if(ReadAmount(0x11,&readValue) == MI_OK)
						{
							ILI9341_DispStringLine_EN(LINE(4),(char* )"sno:"); 
							ILI9341_DispNum(32,LINE(4),readValue,10,16);
						}
						
						if(temp > 3) //3秒
						{
//							TIM_Cmd(TIM3, ENABLE);
//							LCD_SetTextColor(RED);
//							ILI9341_DisplayStringEx(12,102,48,48,(uint8_t *)"OVER TIME",0);
//							LCD_SetTextColor(GREEN);
							problem |=00000001;

						}
						
						PcdHalt();
					}
				}
				LED_YELLOW_OFF;	
				if(problem != 0x00)
				{
					nopass(problem);
				}else{
					pass();
				}
				problem=00000000;
			}

/*  写学号
				PcdSelect(ucArray_ID);
				PcdAuthState( PICC_AUTHENT1A, 0x11, KeyValue, ucArray_ID );//校验密码 
        WriteAmount(0x11,3118001454); //写入学号
        if(ReadAmount(0x11,&readValue) == MI_OK)	//读取金额
				{						
					ILI9341_DispStringLine_EN(LINE(4),(char* )"sno:");				 										 	         
					ILI9341_DispNum(32,LINE(4),readValue,10,16);
          PcdHalt();
				}	
			}
*/
							
		}		
		   
  }	
}


/**
  * @brief  主函数
  * @param  无
  * @retval 无
  */
int main(void)
{	

	
  /*滴答时钟初始化*/
  SysTick_Init ();
  
	/*LCD 初始化*/
	ILI9341_Init ();  
  
	/* USART config */
	USART_Config(); 
	
	//红外测温初始化
	SMBus_Init();
	LED_GPIO_Config();
	MYLED_GPIO_Config();
  
  /*RC522模块所需外设的初始化配置*/
  RC522_Init (); 

	//中断设置
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);	
	
	//计时器
	GENERAL_TIM_Init();
	GENERAL_TIM2_Init();
	
	//外部中断 
	EXTI_Key_Config(); 
	
  /*其中0、3、5、6 模式适合从左至右显示文字，*/
	ILI9341_GramScan ( 6 ); 
  LCD_SetFont(&Font8x16);
	LCD_SetColors(BLACK,BLACK);
  
  /* 清屏，显示全黑 */
  ILI9341_Clear(0,0,LCD_X_LENGTH,LCD_Y_LENGTH);
  
	/********初始化界面*******/
  LCD_SetTextColor(BLUE);  
	ILI9341_DisplayStringEx(84,0,48,48,(uint8_t *)"OUT",0);
  
  PcdReset ();
   
  /*设置工作方式*/   
	M500PcdConfigISOType ( 'A' );
  
	TIM_Cmd(TIM2, ENABLE);

	//湿温度传感器初始化
	DHT11_Init ();
	printf ( "\r\n3118001454何绍光——多功能门禁\r\n" );
  while(1)
  {
//		LED1_TOGGLE;
//		Delay_us(300000);
    /*IC卡检测	*/    
    IC_test ();     
//		a = SMBus_ReadTemp();
//		//printf("温度 = %f℃\r\n",a);

//		sprintf ( cStra, "temputure:%f", a);				 										 	         
//		ILI9341_DispStringLine_EN(LINE(5) , (char* )cStra ); 
//		LED1_TOGGLE;
//		LED_RED_TOGGLE;
//		LED_YELLOW_OFF;
//		LED_GREEN_ON;
////		LED_YELLOW_TOGGLE;
////	  LED_GREEN_TOGGLE;
//		Delay_us(250000);	
  }

}


/* ------------------------------------------end of file---------------------------------------- */

