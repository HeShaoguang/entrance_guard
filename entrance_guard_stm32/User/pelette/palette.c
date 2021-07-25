#include "palette.h"
#include "./lcd/bsp_xpt2046_lcd.h"
#include "./lcd/bsp_ili9341_lcd.h"
#include "./Test/test.h"
#include "./usart/bsp_usart.h"

 
/*按钮结构体数组*/
Touch_Button button[BUTTON_NUM];

//定义学号数组
char password[PASSWORD_MAX];
uint8_t PASSWORD_NUM;


static void My_Draw_Button(void *btn);
static void My_Command_Num(void *btn);
static void My_Command_Clear(void *btn);
static void My_Command_Sure(void *btn);


/**  
* @brief  Palette_Init 画板初始化
* @param  无
* @retval 无
*/
void Palette_Init(uint8_t LCD_Mode)
{
  
  uint8_t i,j;

	ILI9341_GramScan ( LCD_Mode );
	
  /* 整屏清为black */
	LCD_SetBackColor(CL_BLACK);
  ILI9341_Clear(0,0,LCD_X_LENGTH,LCD_Y_LENGTH);	

  
  /* 初始化按钮 */
  Touch_Button_Init();
	
		//初始化密码数组
	PASSWORD_NUM=PASSWORD_MIN;
	for(j=0;j<=PASSWORD_MAX-1;j++)
	{
		password[j]=' ';
	}
  
  /* 描绘按钮 */
  for(i=0;i<BUTTON_NUM;i++)
  {
    button[i].draw_btn(&button[i]);
  }
	LCD_SetTextColor(TextColor);
}




/**
* @brief  My_Draw_Button 画按钮函数
* @param  无
* @retval 无
*/
static void My_Draw_Button(void *btn)
{
  Touch_Button *ptr = (Touch_Button *)btn;
  
  
    /* 背景颜色 没按下时为灰色，按下时为白色*/                  
    if(ptr->touch_flag ==0 )
    {
			
			LCD_SetColors(CL_BUTTON_GREY,CL_WHITE);
			ILI9341_DrawRectangle(	ptr->start_x,
																ptr->start_y,
																ptr->end_x - ptr->start_x,
																ptr->end_y - ptr->start_y,1);
      

			 /*显示文字时的背景颜色*/     
			LCD_SetColors(CL_BLUE4,CL_BUTTON_GREY);
			ILI9341_DrawRectangle(	ptr->start_x,
																ptr->start_y,
																ptr->end_x - ptr->start_x,
																ptr->end_y - ptr->start_y,0);

    }
    else
    {

			LCD_SetColors(CL_WHITE,CL_WHITE);
			ILI9341_DrawRectangle(	ptr->start_x,
																ptr->start_y,
																ptr->end_x - ptr->start_x,
																ptr->end_y - ptr->start_y,1);
      

			 /*显示文字时的背景颜色*/     
			LCD_SetColors(CL_BLUE4,CL_WHITE);
			ILI9341_DrawRectangle(	ptr->start_x,
																ptr->start_y,
																ptr->end_x - ptr->start_x,
																ptr->end_y - ptr->start_y,0);
    }
  
  /*根据画刷形状描绘按钮图案*/
 switch(ptr->para)
  {
    		
    case LINE_0_NUM:      
     		
		LCD_SetColors(CL_BLACK,CL_BUTTON_GREY);
		ILI9341_DisplayStringEx(ptr->start_x+32,
                          ptr->start_y+8,24,24,(uint8_t *)"0",0);
      
      break;   
    		
    case LINE_1_NUM:      
     		
		LCD_SetColors(CL_BLACK,CL_BUTTON_GREY);
		ILI9341_DisplayStringEx(ptr->start_x+32,
                          ptr->start_y+8,24,24,(uint8_t *)"1",0);
      
      break;   
    		
    case LINE_2_NUM:      
     		
		LCD_SetColors(CL_BLACK,CL_BUTTON_GREY);
		ILI9341_DisplayStringEx(ptr->start_x+32,
                          ptr->start_y+8,24,24,(uint8_t *)"2",0);
      
      break;   
    		
    case LINE_3_NUM:      
     		
		LCD_SetColors(CL_BLACK,CL_BUTTON_GREY);
		ILI9341_DisplayStringEx(ptr->start_x+32,
                          ptr->start_y+8,24,24,(uint8_t *)"3",0);
      
      break;   
    		
    case LINE_4_NUM:      
     		
		LCD_SetColors(CL_BLACK,CL_BUTTON_GREY);
		ILI9341_DisplayStringEx(ptr->start_x+32,
                          ptr->start_y+8,24,24,(uint8_t *)"4",0);
      
      break;   
    		
    case LINE_5_NUM:      
     		
		LCD_SetColors(CL_BLACK,CL_BUTTON_GREY);
		ILI9341_DisplayStringEx(ptr->start_x+32,
                          ptr->start_y+8,24,24,(uint8_t *)"5",0);
      
      break;   
    		
    case LINE_6_NUM:      
     		
		LCD_SetColors(CL_BLACK,CL_BUTTON_GREY);
		ILI9341_DisplayStringEx(ptr->start_x+32,
                          ptr->start_y+8,24,24,(uint8_t *)"6",0);
      
      break;   
    		
    case LINE_7_NUM:      
     		
		LCD_SetColors(CL_BLACK,CL_BUTTON_GREY);
		ILI9341_DisplayStringEx(ptr->start_x+32,
                          ptr->start_y+8,24,24,(uint8_t *)"7",0);
      
      break;   
    		
    case LINE_8_NUM:      
     		
		LCD_SetColors(CL_BLACK,CL_BUTTON_GREY);
		ILI9341_DisplayStringEx(ptr->start_x+32,
                          ptr->start_y+8,24,24,(uint8_t *)"8",0);
      
      break;   
    		
    case LINE_9_NUM:      
     		
		LCD_SetColors(CL_BLACK,CL_BUTTON_GREY);
		ILI9341_DisplayStringEx(ptr->start_x+32,
                          ptr->start_y+8,24,24,(uint8_t *)"9",0);
      
      break;   
    		
    case LINE_SURE_NUM:      
     		
		LCD_SetColors(CL_BLACK,CL_BUTTON_GREY);
		ILI9341_DisplayStringEx(ptr->start_x+32,
                          ptr->start_y+8,24,24,(uint8_t *)"#",0);
      
      break;   

      
    case LINE_CLEAR_NUM:
        
     		
		LCD_SetColors(CL_BLACK,CL_BUTTON_GREY);
		ILI9341_DisplayStringEx(ptr->start_x+32,
                          ptr->start_y+8,24,24,(uint8_t *)"X",0);
 
    
      break;

  }
  LCD_SetBackColor(CL_BLACK);
}


//当数字按钮被按下时候的处理函数
static void My_Command_Num(void *btn)
{
	if(PASSWORD_NUM<PASSWORD_MAX)
	{
		Touch_Button *ptr = (Touch_Button *)btn;
		 switch(ptr->para)
		{	
			case LINE_0_NUM:password[PASSWORD_NUM]='0';PASSWORD_NUM++;break;
			case LINE_1_NUM:password[PASSWORD_NUM]='1';PASSWORD_NUM++;break;
			case LINE_2_NUM:password[PASSWORD_NUM]='2';PASSWORD_NUM++;break;
			case LINE_3_NUM:password[PASSWORD_NUM]='3';PASSWORD_NUM++;break;
			case LINE_4_NUM:password[PASSWORD_NUM]='4';PASSWORD_NUM++;break;
			case LINE_5_NUM:password[PASSWORD_NUM]='5';PASSWORD_NUM++;break;
			case LINE_6_NUM:password[PASSWORD_NUM]='6';PASSWORD_NUM++;break;
			case LINE_7_NUM:password[PASSWORD_NUM]='7';PASSWORD_NUM++;break;
			case LINE_8_NUM:password[PASSWORD_NUM]='8';PASSWORD_NUM++;break;
			case LINE_9_NUM:password[PASSWORD_NUM]='9';PASSWORD_NUM++;break;
		}
	}
	
}

//当清除按钮按下时候的处理函数
static void My_Command_Clear(void *btn)
{
	uint8_t i;
	for(i=PASSWORD_MIN;i<=PASSWORD_NUM;i++)
	{
		password[i]=' ';
	}
	PASSWORD_NUM=PASSWORD_MIN;
	My_Face();
}

//求10的几次方
uint32_t Pow(uint8_t n)
{
	uint32_t result=1;	
	--n;
	while(n)
	{
		result *= 10;
		--n;
	}
	return result;
}	
//当确定按钮按下时候的处理函数，先将学号的数据改为uint32_t的类型，发送该学号给电脑
static void My_Command_Sure(void *btn)
{
	uint8_t i,j;
	uint32_t num=0;
	char cStr [ 30 ] = { 0 };
	for(i=PASSWORD_NUM-1,j=1;i>=PASSWORD_MIN;i--,j++)
	{
		num = num + ((password[i]-'0')*Pow(j));
	}
	printf ("sno:%u\r\n", num );
	Send_sno(num);
}
//按钮初始化
void Touch_Button_Init(void)
{
  /*第一列，主要为颜色按钮*/
  button[0].start_x = COLOR_BLOCK_WIDTH;
  button[0].start_y = PALETTE_START_Y+COLOR_BLOCK_HEIGHT*3;
  button[0].end_x = COLOR_BLOCK_WIDTH*2 ;
  button[0].end_y = PALETTE_START_Y+COLOR_BLOCK_HEIGHT*4;
  button[0].para = LINE_0_NUM;
  button[0].touch_flag = 0;  
  button[0].draw_btn = My_Draw_Button ;
  button[0].btn_command = My_Command_Num ;
  
  button[1].start_x = 0;
  button[1].start_y = PALETTE_START_Y;
  button[1].end_x = COLOR_BLOCK_WIDTH;
  button[1].end_y = PALETTE_START_Y+COLOR_BLOCK_HEIGHT;
  button[1].para = LINE_1_NUM;
  button[1].touch_flag = 0;  
  button[1].draw_btn = My_Draw_Button ;
  button[1].btn_command = My_Command_Num ;
  
  button[2].start_x = COLOR_BLOCK_WIDTH;
  button[2].start_y = PALETTE_START_Y;
  button[2].end_x = COLOR_BLOCK_WIDTH*2 ;
  button[2].end_y = PALETTE_START_Y+COLOR_BLOCK_HEIGHT;
  button[2].para = LINE_2_NUM;
  button[2].touch_flag = 0;  
  button[2].draw_btn = My_Draw_Button ;
  button[2].btn_command = My_Command_Num ;
  
  button[3].start_x = COLOR_BLOCK_WIDTH*2;
  button[3].start_y = PALETTE_START_Y;
  button[3].end_x = COLOR_BLOCK_WIDTH*3 ;
  button[3].end_y = PALETTE_START_Y+COLOR_BLOCK_HEIGHT;
  button[3].para = LINE_3_NUM;
  button[3].touch_flag = 0;  
  button[3].draw_btn = My_Draw_Button ;
  button[3].btn_command = My_Command_Num ;
  
  button[4].start_x = 0;
  button[4].start_y = PALETTE_START_Y+COLOR_BLOCK_HEIGHT;
  button[4].end_x = COLOR_BLOCK_WIDTH;
  button[4].end_y = PALETTE_START_Y+COLOR_BLOCK_HEIGHT*2;
  button[4].para = LINE_4_NUM;
  button[4].touch_flag = 0;  
  button[4].draw_btn = My_Draw_Button ;
  button[4].btn_command = My_Command_Num ;
  
  button[5].start_x = COLOR_BLOCK_WIDTH;
  button[5].start_y = PALETTE_START_Y+COLOR_BLOCK_HEIGHT;
  button[5].end_x = COLOR_BLOCK_WIDTH*2;
  button[5].end_y = PALETTE_START_Y+COLOR_BLOCK_HEIGHT*2;
  button[5].para = LINE_5_NUM;
  button[5].touch_flag = 0;  
  button[5].draw_btn = My_Draw_Button ;
  button[5].btn_command = My_Command_Num ;
  
  button[6].start_x = COLOR_BLOCK_WIDTH*2;
  button[6].start_y = PALETTE_START_Y+COLOR_BLOCK_HEIGHT;
  button[6].end_x = COLOR_BLOCK_WIDTH*3;
  button[6].end_y = PALETTE_START_Y+COLOR_BLOCK_HEIGHT*2;
  button[6].para = LINE_6_NUM;
  button[6].touch_flag = 0;  
  button[6].draw_btn = My_Draw_Button ;
  button[6].btn_command = My_Command_Num ;  
  
  button[7].start_x = 0;
  button[7].start_y = PALETTE_START_Y+COLOR_BLOCK_HEIGHT*2;
  button[7].end_x = COLOR_BLOCK_WIDTH;
  button[7].end_y = PALETTE_START_Y+COLOR_BLOCK_HEIGHT*3;
  button[7].para = LINE_7_NUM;
  button[7].touch_flag = 0;  
  button[7].draw_btn = My_Draw_Button ;
  button[7].btn_command = My_Command_Num ;
   
  button[8].start_x = COLOR_BLOCK_WIDTH;
  button[8].start_y = PALETTE_START_Y+COLOR_BLOCK_HEIGHT*2;
  button[8].end_x = COLOR_BLOCK_WIDTH*2;
  button[8].end_y = PALETTE_START_Y+COLOR_BLOCK_HEIGHT*3;
  button[8].para = LINE_8_NUM;
  button[8].touch_flag = 0;  
  button[8].draw_btn = My_Draw_Button ;
  button[8].btn_command = My_Command_Num ;
  
  button[9].start_x = COLOR_BLOCK_WIDTH*2;
  button[9].start_y = PALETTE_START_Y+COLOR_BLOCK_HEIGHT*2;
  button[9].end_x = COLOR_BLOCK_WIDTH*3;
  button[9].end_y = PALETTE_START_Y+COLOR_BLOCK_HEIGHT*3;
  button[9].para = LINE_9_NUM;
  button[9].touch_flag = 0;  
  button[9].draw_btn =My_Draw_Button ;
  button[9].btn_command = My_Command_Num ;
  
  button[10].start_x =0;
  button[10].start_y = PALETTE_START_Y+COLOR_BLOCK_HEIGHT*3;
  button[10].end_x = COLOR_BLOCK_WIDTH ;
  button[10].end_y = PALETTE_START_Y+COLOR_BLOCK_HEIGHT*4;
  button[10].para = LINE_SURE_NUM;
  button[10].touch_flag = 0;  
  button[10].draw_btn = My_Draw_Button ;
  button[10].btn_command = My_Command_Sure;
  
  button[11].start_x = COLOR_BLOCK_WIDTH*2;
  button[11].start_y = PALETTE_START_Y+COLOR_BLOCK_HEIGHT*3;
  button[11].end_x = COLOR_BLOCK_WIDTH*3 ;
  button[11].end_y = PALETTE_START_Y+COLOR_BLOCK_HEIGHT*4;
  button[11].para = LINE_CLEAR_NUM;
  button[11].touch_flag = 0;  
  button[11].draw_btn = My_Draw_Button ;
  button[11].btn_command = My_Command_Clear ;
  

}


/**
* @brief  Touch_Button_Down 按键被按下时调用的函数，由触摸屏调用，改变按键的颜色
* @param  x 触摸位置的x坐标
* @param  y 触摸位置的y坐标
* @retval 无
*/
void Touch_Button_Down(uint16_t x,uint16_t y)
{
  uint8_t i;
  for(i=0;i<BUTTON_NUM;i++)
  {
    /* 触摸到了按钮 */
    if(x<=button[i].end_x && y<=button[i].end_y && y>=button[i].start_y && x>=button[i].start_x )
    {
      if(button[i].touch_flag == 0)     /*原本的状态为没有按下，则更新状态*/
      {
      button[i].touch_flag = 1;         /* 记录按下标志 */
      
      button[i].draw_btn(&button[i]);  /*重绘按钮*/
      }        
      
    }
    else if(button[i].touch_flag == 1) /* 触摸移出了按键的范围且之前有按下按钮 */
    {
      button[i].touch_flag = 0;         /* 清除按下标志，判断为误操作*/
      
      button[i].draw_btn(&button[i]);   /*重绘按钮*/
    }

  }

}

/**
* @brief  Touch_Button_Up 按键被释放时调用的函数，由触摸屏调用
* @param  x 触摸最后释放时的x坐标
* @param  y 触摸最后释放时的y坐标
* @retval 无
*/
void Touch_Button_Up(uint16_t x,uint16_t y)
{
   uint8_t i; 
   for(i=0;i<BUTTON_NUM;i++)
   {
     /* 触笔在按钮区域释放 */
      if((x<button[i].end_x && x>button[i].start_x && y<button[i].end_y && y>button[i].start_y))
      {        
        button[i].touch_flag = 0;       /*释放触摸标志*/
        
        button[i].draw_btn(&button[i]); /*重绘按钮*/        
      
        button[i].btn_command(&button[i]);  /*执行按键的功能命令*/
        
        break;
      }
    }  

}

void My_Face(void)
{
	LCD_SetTextColor(TextColor);
	ILI9341_DispStringLine_EN(LINE(7),password);
	//ILI9341_DispStringLine_EN(LINE(0),"test time");
	ILI9341_DispStringLine_EN(LINE(7),"sno:");
}



