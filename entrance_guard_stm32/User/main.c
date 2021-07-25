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
	//触摸屏初始化
	XPT2046_Init();
	//从FLASH里获取校正参数，若FLASH无参数，则使用模式3进行校正。第二个参数为1则强制校准（完全重新校准）
	Calibrate_or_Get_TouchParaWithFlash(6,0);	
  
	/* USART config */
	USART_Config(); 
	
	//红外测温初始化
	SMBus_Init();
	//灯初始化
	LED_GPIO_Config();
	MYLED_GPIO_Config(); 
	//wifi初始化
	ESP8266_Init ();
	
  /*RC522模块所需外设的初始化配置*/
  RC522_Init (); 

	//中断设置
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);	
	
	//计时器初始化
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
	//绘制触摸画板界面
	Palette_Init(LCD_SCAN_MODE);
	
  LCD_SetTextColor(TextColor);  
	ILI9341_DisplayStringEx(84,0,48,48,(uint8_t *)"OUT",0);

  
  PcdReset ();
   
  /*设置工作方式*/   
	M500PcdConfigISOType ( 'A' );
  
	//开启定时器
	TIM_Cmd(TIM2, ENABLE);
	TIM_Cmd(TIM3, ENABLE);

	//湿温度传感器初始化
//	DHT11_Init ();
	printf ( "\r\n3118001454何绍光——多功能门禁\r\n" );
	
	//连接wifi 
 	ESP8266_Connect();
	
  while(1)
  {
//		LED1_TOGGLE;
//		Delay_us(300000);
    /*IC卡检测	*/    
    IC_test ();     
  }

}


/* ------------------------------------------end of file---------------------------------------- */

