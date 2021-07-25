#ifndef __TIMER2_H
#define __TIMER2_H


#include "stm32f10x.h"



#define            GENERAL_TIM2                  TIM3
#define            GENERAL_TIM2_APBxClock_FUN     RCC_APB1PeriphClockCmd
#define            GENERAL_TIM2_CLK               RCC_APB1Periph_TIM3
#define            GENERAL_TIM2_Period            99    
#define            GENERAL_TIM2_Prescaler         7199   //  //(99+1)(7199+1)/72000000=10ms
#define            GENERAL_TIM2_IRQ               TIM3_IRQn
#define            GENERAL_TIM2_IRQHandler        TIM3_IRQHandler

/**************************º¯ÊýÉùÃ÷********************************/

void GENERAL_TIM2_Init(void);


#endif	/* __BSP_GENERALTIME_H */


