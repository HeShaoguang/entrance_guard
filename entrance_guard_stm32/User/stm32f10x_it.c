
#include "stm32f10x_it.h"
#include "bsp_SysTick.h"
#include "./lcd/bsp_xpt2046_lcd.h"  
#include "./usart/bsp_usart.h"
#include "./lcd/bsp_ili9341_lcd.h"
#include "./exti/bsp_exti.h"
#include "timer.h"
#include "./timer2/timer2.h"
#include "./dht11/bsp_dht11.h"
#include "./ESP8266/bsp_esp8266.h"
#include "./Test/test.h"
#include <stdio.h>
#include <string.h> 

extern volatile uint32_t time;
extern uint8_t mode;
extern DHT11_Data_TypeDef DHT11_Data;

/** @addtogroup STM32F10x_StdPeriph_Template
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/******************************************************************************/
/*            Cortex-M3 Processor Exceptions Handlers                         */
/******************************************************************************/

/**
  * @brief  This function handles NMI exception.
  * @param  None
  * @retval None
  */
void NMI_Handler(void)
{
}

/**
  * @brief  This function handles Hard Fault exception.
  * @param  None
  * @retval None
  */
void HardFault_Handler(void)
{
  /* Go to infinite loop when Hard Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Memory Manage exception.
  * @param  None
  * @retval None
  */
void MemManage_Handler(void)
{
  /* Go to infinite loop when Memory Manage exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Bus Fault exception.
  * @param  None
  * @retval None
  */
void BusFault_Handler(void)
{
  /* Go to infinite loop when Bus Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Usage Fault exception.
  * @param  None
  * @retval None
  */
void UsageFault_Handler(void)
{
  /* Go to infinite loop when Usage Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles SVCall exception.
  * @param  None
  * @retval None
  */
void SVC_Handler(void)
{
}

/**
  * @brief  This function handles Debug Monitor exception.
  * @param  None
  * @retval None
  */
void DebugMon_Handler(void)
{
}

/**
  * @brief  This function handles PendSVC exception.
  * @param  None
  * @retval None
  */
void PendSV_Handler(void)
{
}

/**
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval None
  */
void SysTick_Handler(void)
{
	TimingDelay_Decrement();
}

/******************************************************************************/
/*                 STM32F10x Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32f10x_xx.s).                                            */
/******************************************************************************/
void USART1_IRQHandler(void)
{	 
}

void TIM2_IRQHandler(void)
{
	char cStr [ 50 ];
	if(TIM_GetITStatus(TIM2,TIM_IT_Update)==SET)
	{
		time++;
		LCD_ClearLine(LINE(3));
		sprintf ( cStr, "Time:%dh %dm %ds", time/3600, (time%3600)/60, (time%3600)%60);				 										 	         
		ILI9341_DispStringLine_EN(LINE(3) , (char* )cStr );
		
		TIM_ClearITPendingBit(TIM2,TIM_IT_Update);
	}
}
void TIM3_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM3,TIM_IT_Update)==SET) 
	{
		XPT2046_TouchEvenHandler();
		TIM_ClearITPendingBit(TIM3,TIM_IT_Update);
	} 
}
void KEY1_IRQHandler(void)
{
  //确保是否产生了EXTI Line中断
	if(EXTI_GetITStatus(KEY1_INT_EXTI_LINE) != RESET) 
	{
		if(KEY2 == 1)
		{
			mode = 3;
			TextColor = YELLOW;
			LCD_SetTextColor(TextColor);
			ILI9341_Clear(0,0,240,49);
			ILI9341_Clear(0,48,240,50);
			ILI9341_DisplayStringEx(96,0,48,48,(uint8_t *)"LK",0);
		}
		else{
			mode = 0;	
			TextColor = GREEN;
			LCD_SetTextColor(TextColor);
			ILI9341_Clear(0,0,240,49);
			ILI9341_Clear(0,48,240,50);
			ILI9341_DisplayStringEx(96,0,48,48,(uint8_t *)"IN",0);
		}
    //清除中断标志位
		EXTI_ClearITPendingBit(KEY1_INT_EXTI_LINE);     
	}  
}

void KEY2_IRQHandler(void)  
{
  //确保是否产生了EXTI Line中断
	if(EXTI_GetITStatus(KEY2_INT_EXTI_LINE) != RESET) 
	{
		if(KEY1 == 1)
		{
			mode = 3;
			TextColor = YELLOW;
			LCD_SetTextColor(TextColor);
			ILI9341_Clear(0,0,240,49);
			ILI9341_Clear(0,48,240,50);
			ILI9341_DisplayStringEx(96,0,48,48,(uint8_t *)"LK",0);
		}
		else{
			mode = 1;	
			TextColor = BLUE;
			LCD_SetTextColor(TextColor);
			ILI9341_Clear(0,0,320,49);
			ILI9341_Clear(0,48,320,50);
			ILI9341_DisplayStringEx(84,0,48,48,(uint8_t *)"OUT",0);
		}
    //清除中断标志位
		EXTI_ClearITPendingBit(KEY2_INT_EXTI_LINE);     
	}  
}

void macESP8266_USART_INT_FUN ( void )
{	
	uint8_t ucCh;
	
	if ( USART_GetITStatus ( macESP8266_USARTx, USART_IT_RXNE ) != RESET )
	{
		ucCh  = USART_ReceiveData( macESP8266_USARTx );
		
		if ( strEsp8266_Fram_Record .InfBit .FramLength < ( RX_BUF_MAX_LEN - 1 ) )                       //预留1个字节写结束符
			strEsp8266_Fram_Record .Data_RX_BUF [ strEsp8266_Fram_Record .InfBit .FramLength ++ ]  = ucCh;

	}
	 	 
	if ( USART_GetITStatus( macESP8266_USARTx, USART_IT_IDLE ) == SET )                                         //数据帧接收完毕
	{
    strEsp8266_Fram_Record .InfBit .FramFinishFlag = 1;
		
		ucCh = USART_ReceiveData( macESP8266_USARTx );                                                              //由软件序列清除中断标志位(先读USART_SR，然后读USART_DR)
	
		ucTcpClosedFlag = strstr ( strEsp8266_Fram_Record .Data_RX_BUF, "CLOSED\r\n" ) ? 1 : 0;
		
  }	

}
/**
  * @brief  This function handles PPP interrupt request.
  * @param  None
  * @retval None
  */
/*void PPP_IRQHandler(void)
{
}*/

/**
  * @}
  */ 


/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
