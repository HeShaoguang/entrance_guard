#ifndef __MYLED_H
#define	__MYLED_H


#include "stm32f10x.h"


/* ����LED���ӵ�GPIO�˿�, �û�ֻ��Ҫ�޸�����Ĵ��뼴�ɸı���Ƶ�LED���� */
// R-��ɫ
#define LED_RED_GPIO_PORT    	GPIOF			              /* GPIO�˿� */
#define LED_RED_GPIO_CLK 	    RCC_APB2Periph_GPIOF		/* GPIO�˿�ʱ�� */
#define LED_RED_GPIO_PIN		GPIO_Pin_0			        /* ���ӵ�SCLʱ���ߵ�GPIO */

// G-��ɫ
#define LED_YELLOW_GPIO_PORT    	GPIOF			              /* GPIO�˿� */
#define LED_YELLOW_GPIO_CLK 	    RCC_APB2Periph_GPIOF		/* GPIO�˿�ʱ�� */
#define LED_YELLOW_GPIO_PIN		GPIO_Pin_1			        /* ���ӵ�SCLʱ���ߵ�GPIO */

// B-��ɫ
#define LED_GREEN_GPIO_PORT    	GPIOF			              /* GPIO�˿� */
#define LED_GREEN_GPIO_CLK 	    RCC_APB2Periph_GPIOF		/* GPIO�˿�ʱ�� */
#define LED_GREEN_GPIO_PIN		GPIO_Pin_2			        /* ���ӵ�SCLʱ���ߵ�GPIO */


/** the macro definition to trigger the led on or off 
  * 1 - off
  *0 - on
  */
#define MYON  0
#define MYOFF 1

/* ʹ�ñ�׼�Ĺ̼������IO*/
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


/* ֱ�Ӳ����Ĵ����ķ�������IO */
#define	mydigitalHi(p,i)		 {p->BSRR=i;}	 //���Ϊ�ߵ�ƽ		
#define mydigitalLo(p,i)		 {p->BRR=i;}	 //����͵�ƽ
#define mydigitalToggle(p,i) {p->ODR ^=i;} //�����ת״̬


/* �������IO�ĺ� */
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
