#ifndef __MYLED_H
#define	__MYLED_H


#include "stm32f10x.h"


/* 定义LED连接的GPIO端口, 用户只需要修改下面的代码即可改变控制的LED引脚 */
// R-红色
#define LED_RED_GPIO_PORT    	GPIOF			              /* GPIO端口 */
#define LED_RED_GPIO_CLK 	    RCC_APB2Periph_GPIOF		/* GPIO端口时钟 */
#define LED_RED_GPIO_PIN		GPIO_Pin_0			        /* 连接到SCL时钟线的GPIO */

// G-绿色
#define LED_YELLOW_GPIO_PORT    	GPIOF			              /* GPIO端口 */
#define LED_YELLOW_GPIO_CLK 	    RCC_APB2Periph_GPIOF		/* GPIO端口时钟 */
#define LED_YELLOW_GPIO_PIN		GPIO_Pin_1			        /* 连接到SCL时钟线的GPIO */

// B-蓝色
#define LED_GREEN_GPIO_PORT    	GPIOF			              /* GPIO端口 */
#define LED_GREEN_GPIO_CLK 	    RCC_APB2Periph_GPIOF		/* GPIO端口时钟 */
#define LED_GREEN_GPIO_PIN		GPIO_Pin_2			        /* 连接到SCL时钟线的GPIO */


/** the macro definition to trigger the led on or off 
  * 1 - off
  *0 - on
  */
#define MYON  0
#define MYOFF 1

/* 使用标准的固件库控制IO*/
#define LED_RED(a)	if (a)	\
					GPIO_SetBits(LED_RED_GPIO_PORT,LED_RED_GPIO_PIN);\
					else		\
					GPIO_ResetBits(LED_RED_GPIO_PORT,LED_RED_GPIO_PIN)

#define LED_YELLOW(a)	if (a)	\
					GPIO_SetBits(LED_YELLOW_GPIO_PORT,LED_YELLOW_GPIO_PIN);\
					else		\
					GPIO_ResetBits(LED_YELLOW_GPIO_PORT,LED_YELLOW_GPIO_PIN)

#define LED_GREEN(a)	if (a)	\
					GPIO_SetBits(LED_GREEN_GPIO_PORT,LED_GREEN_GPIO_PIN);\
					else		\
					GPIO_ResetBits(LED_GREEN_GPIO_PORT,LED_GREEN_GPIO_PIN)


/* 直接操作寄存器的方法控制IO */
#define	mydigitalHi(p,i)		 {p->BSRR=i;}	 //输出为高电平		
#define mydigitalLo(p,i)		 {p->BRR=i;}	 //输出低电平
#define mydigitalToggle(p,i) {p->ODR ^=i;} //输出反转状态


/* 定义控制IO的宏 */
#define LED_RED_TOGGLE		 mydigitalToggle(LED_RED_GPIO_PORT,LED_RED_GPIO_PIN)
#define LED_RED_ON		   mydigitalHi(LED_RED_GPIO_PORT,LED_RED_GPIO_PIN)
#define LED_RED_OFF			   mydigitalLo(LED_RED_GPIO_PORT,LED_RED_GPIO_PIN)

#define LED_YELLOW_TOGGLE		 mydigitalToggle(LED_YELLOW_GPIO_PORT,LED_YELLOW_GPIO_PIN)
#define LED_YELLOW_ON		   mydigitalHi(LED_YELLOW_GPIO_PORT,LED_YELLOW_GPIO_PIN)
#define LED_YELLOW_OFF			   mydigitalLo(LED_YELLOW_GPIO_PORT,LED_YELLOW_GPIO_PIN)

#define LED_GREEN_TOGGLE		 mydigitalToggle(LED_GREEN_GPIO_PORT,LED_GREEN_GPIO_PIN)
#define LED_GREEN_ON		   mydigitalHi(LED_GREEN_GPIO_PORT,LED_GREEN_GPIO_PIN)
#define LED_GREEN_OFF			   mydigitalLo(LED_GREEN_GPIO_PORT,LED_GREEN_GPIO_PIN)


void MYLED_GPIO_Config(void);

#endif /* __MYLED_H */
