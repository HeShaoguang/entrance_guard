#ifndef __TIMER_H
#define __TIMER_H


#include "stm32f10x.h"



#define            GENERAL_TIM                   TIM2
#define            GENERAL_TIM_APBxClock_FUN     RCC_APB1PeriphClockCmd
#define            GENERAL_TIM_CLK               RCC_APB1Periph_TIM2
#define            GENERAL_TIM_Period            9999    //正式值应该为9999
#define            GENERAL_TIM_Prescaler         7199   //正式值应该为7199  //(9999+1)(7199+1)/72000000=1s
#define            GENERAL_TIM_IRQ               TIM2_IRQn
#define            GENERAL_TIM_IRQHandler        TIM2_IRQHandler

/**************************函数声明********************************/

void GENERAL_TIM_Init(void);


#endif	/* __BSP_GENERALTIME_H */


