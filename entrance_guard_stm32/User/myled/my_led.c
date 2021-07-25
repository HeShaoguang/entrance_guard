
#include "./myled/my_led.h"   

 /**
  * @brief  ��ʼ������LED��IO
  * @param  ��
  * @retval ��
  */
void MYLED_GPIO_Config(void)
{		
		/*����һ��GPIO_InitTypeDef���͵Ľṹ��*/
		GPIO_InitTypeDef GPIO_InitStructure;

		/*����LED��ص�GPIO����ʱ��*/
		RCC_APB2PeriphClockCmd( LED_RED_GPIO_CLK | LED_YELLOW_GPIO_CLK | LED_GREEN_GPIO_CLK, ENABLE);
		/*ѡ��Ҫ���Ƶ�GPIO����*/
		GPIO_InitStructure.GPIO_Pin = LED_RED_GPIO_PIN;	

		/*��������ģʽΪͨ���������*/
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;   

		/*������������Ϊ50MHz */   
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 

		/*���ÿ⺯������ʼ��GPIO*/
		GPIO_Init(LED_RED_GPIO_PORT, &GPIO_InitStructure);	
		
		/*ѡ��Ҫ���Ƶ�GPIO����*/
		GPIO_InitStructure.GPIO_Pin = LED_YELLOW_GPIO_PIN;

		/*���ÿ⺯������ʼ��GPIO*/
		GPIO_Init(LED_YELLOW_GPIO_PORT, &GPIO_InitStructure);
		
		/*ѡ��Ҫ���Ƶ�GPIO����*/
		GPIO_InitStructure.GPIO_Pin = LED_GREEN_GPIO_PIN;

		/*���ÿ⺯������ʼ��GPIOF*/
		GPIO_Init(LED_GREEN_GPIO_PORT, &GPIO_InitStructure);

		/* �ر�����led��	*/
		GPIO_ResetBits(LED_RED_GPIO_PORT, LED_RED_GPIO_PIN);
		
		/* �ر�����led��	*/
		GPIO_ResetBits(LED_YELLOW_GPIO_PORT, LED_YELLOW_GPIO_PIN);	 
    
    /* �ر�����led��	*/
		GPIO_ResetBits(LED_GREEN_GPIO_PORT, LED_GREEN_GPIO_PIN);
}


/*********************************************END OF FILE**********************/
