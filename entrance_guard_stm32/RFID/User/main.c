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
uint8_t mode = 1;  //0���ǽ�(��k1����1�ǳ�(��k2��

DHT11_Data_TypeDef DHT11_Data;

uint8_t KeyValue[]={0xFF ,0xFF, 0xFF, 0xFF, 0xFF, 0xFF};   // ��A��Կ

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
  uint8_t ucArray_ID [ 4 ];    /*�Ⱥ���IC�������ͺ�UID(IC�����к�)*/                                                                                         
	uint8_t ucStatusReturn;      /*����״̬*/                                                                                           
  while ( 1 )
  {    
    /*Ѱ����Ѱ��δ���ߵĿ�*/
		if ( ( ucStatusReturn = PcdRequest ( PICC_REQIDL, ucArray_ID ) ) != MI_OK )  
       /*��ʧ���ٴ�Ѱ��*/
			ucStatusReturn = PcdRequest ( PICC_REQIDL, ucArray_ID );		                                                

		if ( ucStatusReturn == MI_OK  )
		{
      /*����ײ�����ж��ſ������д��������Χʱ������ͻ���ƻ������ѡ��һ�Ž��в�����*/
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
				
				if(mode == 1)  //дʱ�� �� ��
				{
					PcdSelect(ucArray_ID);		
					PcdAuthState( PICC_AUTHENT1A, 0x12, KeyValue, ucArray_ID );//У������ 
					WriteAmount(0x12,time); //д����
					if(ReadAmount(0x12,&readValue) == MI_OK)	//��ȡ���
					{		
						
						sprintf ( cStr, "The Card ID is: %02X%02X%02X%02X",ucArray_ID [0], ucArray_ID [1], ucArray_ID [2],ucArray_ID [3] );
						ILI9341_DispStringLine_EN(LINE(3) , (char* )cStr ); //����Ļ������ʾID

						sprintf ( cStr, "Time:%dh %dm %ds", readValue/3600, (readValue%3600)/60, (readValue%3600)%60);					 	         
						ILI9341_DispStringLine_EN(LINE(5) , (char* )cStr ); 
						
						if(ReadAmount(0x11,&readValue) == MI_OK)
						{
							ILI9341_DispStringLine_EN(LINE(4),(char* )"sno:"); 
							ILI9341_DispNum(32,LINE(4),readValue,10,16);
						}
						PcdHalt();
					}	
				}else if(mode == 0)  //������ʱ�䣬���ȥ�˵�ʱ��
				{
					PcdSelect(ucArray_ID);		
					PcdAuthState( PICC_AUTHENT1A, 0x12, KeyValue, ucArray_ID );//У������ 
					if(ReadAmount(0x12,&readValue) == MI_OK)	//��ȡ���
					{		
						sprintf ( cStr, "The Card ID is: %02X%02X%02X%02X",ucArray_ID [0], ucArray_ID [1], ucArray_ID [2],ucArray_ID [3] );
						ILI9341_DispStringLine_EN(LINE(3) , (char* )cStr ); //����Ļ������ʾID
						
						temp = time-readValue;
						sprintf ( cStr, "Go Out Time:%dh %dm %ds", temp/3600, (temp%3600)/60, (temp%3600)%60);				 										 	         
						ILI9341_DispStringLine_EN(LINE(5) , (char* )cStr ); 
						
						if(ReadAmount(0x11,&readValue) == MI_OK)
						{
							ILI9341_DispStringLine_EN(LINE(4),(char* )"sno:"); 
							ILI9341_DispNum(32,LINE(4),readValue,10,16);
						}
						
						if(temp > 3) //3��
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

/*  дѧ��
				PcdSelect(ucArray_ID);
				PcdAuthState( PICC_AUTHENT1A, 0x11, KeyValue, ucArray_ID );//У������ 
        WriteAmount(0x11,3118001454); //д��ѧ��
        if(ReadAmount(0x11,&readValue) == MI_OK)	//��ȡ���
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
  * @brief  ������
  * @param  ��
  * @retval ��
  */
int main(void)
{	

	
  /*�δ�ʱ�ӳ�ʼ��*/
  SysTick_Init ();
  
	/*LCD ��ʼ��*/
	ILI9341_Init ();  
  
	/* USART config */
	USART_Config(); 
	
	//������³�ʼ��
	SMBus_Init();
	LED_GPIO_Config();
	MYLED_GPIO_Config();
  
  /*RC522ģ����������ĳ�ʼ������*/
  RC522_Init (); 

	//�ж�����
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);	
	
	//��ʱ��
	GENERAL_TIM_Init();
	GENERAL_TIM2_Init();
	
	//�ⲿ�ж� 
	EXTI_Key_Config(); 
	
  /*����0��3��5��6 ģʽ�ʺϴ���������ʾ���֣�*/
	ILI9341_GramScan ( 6 ); 
  LCD_SetFont(&Font8x16);
	LCD_SetColors(BLACK,BLACK);
  
  /* ��������ʾȫ�� */
  ILI9341_Clear(0,0,LCD_X_LENGTH,LCD_Y_LENGTH);
  
	/********��ʼ������*******/
  LCD_SetTextColor(BLUE);  
	ILI9341_DisplayStringEx(84,0,48,48,(uint8_t *)"OUT",0);
  
  PcdReset ();
   
  /*���ù�����ʽ*/   
	M500PcdConfigISOType ( 'A' );
  
	TIM_Cmd(TIM2, ENABLE);

	//ʪ�¶ȴ�������ʼ��
	DHT11_Init ();
	printf ( "\r\n3118001454���ܹ⡪���๦���Ž�\r\n" );
  while(1)
  {
//		LED1_TOGGLE;
//		Delay_us(300000);
    /*IC�����	*/    
    IC_test ();     
//		a = SMBus_ReadTemp();
//		//printf("�¶� = %f��\r\n",a);

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

