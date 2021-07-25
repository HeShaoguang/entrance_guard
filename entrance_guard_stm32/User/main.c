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
#include "./lcd/bsp_xpt2046_lcd.h"
#include "./pelette/palette.h"
#include <stdbool.h>


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
	//��������ʼ��
	XPT2046_Init();
	//��FLASH���ȡУ����������FLASH�޲�������ʹ��ģʽ3����У�����ڶ�������Ϊ1��ǿ��У׼����ȫ����У׼��
	Calibrate_or_Get_TouchParaWithFlash(6,0);	
  
	/* USART config */
	USART_Config(); 
	
	//������³�ʼ��
	SMBus_Init();
	//�Ƴ�ʼ��
	LED_GPIO_Config();
	MYLED_GPIO_Config(); 
	//wifi��ʼ��
	ESP8266_Init ();
	
  /*RC522ģ����������ĳ�ʼ������*/
  RC522_Init (); 

	//�ж�����
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);	
	
	//��ʱ����ʼ��
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
	//���ƴ����������
	Palette_Init(LCD_SCAN_MODE);
	
  LCD_SetTextColor(TextColor);  
	ILI9341_DisplayStringEx(84,0,48,48,(uint8_t *)"OUT",0);

  
  PcdReset ();
   
  /*���ù�����ʽ*/   
	M500PcdConfigISOType ( 'A' );
  
	//������ʱ��
	TIM_Cmd(TIM2, ENABLE);
	TIM_Cmd(TIM3, ENABLE);

	//ʪ�¶ȴ�������ʼ��
//	DHT11_Init ();
	printf ( "\r\n3118001454���ܹ⡪���๦���Ž�\r\n" );
	
	//����wifi 
 	ESP8266_Connect();
	
  while(1)
  {
//		LED1_TOGGLE;
//		Delay_us(300000);
    /*IC�����	*/    
    IC_test ();     
  }

}


/* ------------------------------------------end of file---------------------------------------- */

