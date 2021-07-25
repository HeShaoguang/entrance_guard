/**
  ******************************************************************************
  * @file    Project/STM32F10x_StdPeriph_Template/stm32f10x_it.c 
  * @author  MCD Application Team
  * @version V3.5.0
  * @date    08-April-2011
  * @brief   Main Interrupt Service Routines.
  *          This file provides template for all exceptions handler and 
  *          peripherals interrupt service routine.
  ******************************************************************************
  * @attention
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTI
  
  AL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2011 STMicroelectronics</center></h2>
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x_it.h"
#include "bsp_SysTick.h"
#include "./lcd/bsp_xpt2046_lcd.h"  
#include "./usart/bsp_usart.h"
#include "./lcd/bsp_ili9341_lcd.h"
#include "./exti/bsp_exti.h"
#include "timer.h"
#include "./timer2/timer2.h"
#include "./dht11/bsp_dht11.h"

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
		LCD_ClearLine(LINE(19));
		sprintf ( cStr, "Time:%dh %dm %ds", time/3600, (time%3600)/60, (time%3600)%60);				 										 	         
		ILI9341_DispStringLine_EN(LINE(19) , (char* )cStr );
		
		//每10秒1次
		if(time%2==0)
		{
			/*调用DHT11_Read_TempAndHumidity读取温湿度，若成功则输出该信息*/
			if( DHT11_Read_TempAndHumidity ( & DHT11_Data ) == SUCCESS)
			{					
				 /* 显示温度 */
				sprintf(cStr,"Temperature:%d.%d.C",DHT11_Data.temp_int, DHT11_Data.temp_deci);
				LCD_ClearLine(LINE(17));	/* 清除单行文字 */
				ILI9341_DispStringLine_EN(LINE(17),cStr);
						
						/* 显示湿度 */
				sprintf(cStr,"Humidity:%d.%d%% ",DHT11_Data.humi_int, DHT11_Data.humi_deci);
				LCD_ClearLine(LINE(18));	/* 清除单行文字 */
				ILI9341_DispStringLine_EN(LINE(18),cStr);
			}			
			else
			{
				LCD_ClearLine(LINE(17));	/* 清除单行文字 */
				LCD_ClearLine(LINE(18));	/* 清除单行文字 */
				ILI9341_DispStringLine_EN(LINE(17),"Read DHT11 ERROR");
				ILI9341_DispStringLine_EN(LINE(18),"Read DHT11 ERROR");
			}
		}
		
		TIM_ClearITPendingBit(TIM2,TIM_IT_Update);
	}
}
void TIM3_IRQHandler(void)
{
//	if(TIM_GetITStatus(TIM3,TIM_IT_Update)==SET) 
//	{
//		TIM_Cmd(TIM3, DISABLE);
//		ILI9341_Clear(0,102,240,50);
//		TIM_ClearITPendingBit(TIM3,TIM_IT_Update);   
//	} 
}
void KEY1_IRQHandler(void)
{
  //确保是否产生了EXTI Line中断
	if(EXTI_GetITStatus(KEY1_INT_EXTI_LINE) != RESET) 
	{
		mode = 0;	
		LCD_SetTextColor(GREEN);
		ILI9341_Clear(0,0,240,49);
		ILI9341_Clear(0,48,240,50);
		ILI9341_DisplayStringEx(96,0,48,48,(uint8_t *)"IN",0);
    //清除中断标志位
		EXTI_ClearITPendingBit(KEY1_INT_EXTI_LINE);     
	}  
}

void KEY2_IRQHandler(void)  
{
  //确保是否产生了EXTI Line中断
	if(EXTI_GetITStatus(KEY2_INT_EXTI_LINE) != RESET) 
	{
		mode = 1;	
		LCD_SetTextColor(BLUE);
		ILI9341_Clear(0,0,320,49);
		ILI9341_Clear(0,48,320,50);
		ILI9341_DisplayStringEx(84,0,48,48,(uint8_t *)"OUT",0);
    //清除中断标志位
		EXTI_ClearITPendingBit(KEY2_INT_EXTI_LINE);     
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
