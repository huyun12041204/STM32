#ifndef __LCD_H
#define __LCD_H		


#include "sys.h"


#define USE_HORIZONTAL 0  //设置横屏或者竖屏显示 0或1为竖屏 2或3为横屏
#define LCD_W 240
#define LCD_H 240


#define	u8 unsigned char
#define	u16 unsigned int
#define	u32 unsigned long


//-----------------LCD端口定义---------------- 

#define OLED_SCLK_Clr() HAL_GPIO_WritePin(GPIOA,GPIO_PIN_5, GPIO_PIN_RESET)//CLK
#define OLED_SCLK_Set() HAL_GPIO_WritePin(GPIOA,GPIO_PIN_5, GPIO_PIN_SET)

#define OLED_SDIN_Clr() HAL_GPIO_WritePin(GPIOA,GPIO_PIN_7, GPIO_PIN_RESET)//DIN
#define OLED_SDIN_Set() HAL_GPIO_WritePin(GPIOA,GPIO_PIN_7, GPIO_PIN_SET)

#define OLED_RST_Clr() HAL_GPIO_WritePin(GPIOC,GPIO_PIN_4, GPIO_PIN_RESET)//RES
#define OLED_RST_Set() HAL_GPIO_WritePin(GPIOC,GPIO_PIN_4, GPIO_PIN_SET)

#define OLED_DC_Clr() HAL_GPIO_WritePin(GPIOC,GPIO_PIN_5, GPIO_PIN_RESET)//DC
#define OLED_DC_Set() HAL_GPIO_WritePin(GPIOC,GPIO_PIN_5, GPIO_PIN_SET)

#define OLED_BLK_Clr()  HAL_GPIO_WritePin(GPIOB,GPIO_PIN_0, GPIO_PIN_RESET)//BLK
#define OLED_BLK_Set()  HAL_GPIO_WritePin(GPIOB,GPIO_PIN_0, GPIO_PIN_SET)

#define OLED_CMD  0	//写命令
#define OLED_DATA 1	//写数据

extern  u16 BACK_COLOR;   //背景色

void LCD_Writ_Bus(u8 dat);
void LCD_WR_DATA8(u8 dat);
void LCD_WR_DATA(u16 dat);
void LCD_WR_REG(u8 dat);
void LCD_Address_Set(u16 x1,u16 y1,u16 x2,u16 y2);
void Lcd_Init(void);
void LCD_Clear(u16 Color);
void LCD_ShowChinese(u16 x,u16 y,u8 index,u8 size,u16 color);
void LCD_DrawPoint(u16 x,u16 y,u16 color);
void LCD_DrawPoint_big(u16 x,u16 y,u16 color);
void LCD_Fill(u16 xsta,u16 ysta,u16 xend,u16 yend,u16 color);
void LCD_DrawLine(u16 x1,u16 y1,u16 x2,u16 y2,u16 color);
void LCD_DrawRectangle(u16 x1, u16 y1, u16 x2, u16 y2,u16 color);
void Draw_Circle(u16 x0,u16 y0,u8 r,u16 color);
void LCD_ShowChar(u16 x,u16 y,u8 num,u8 mode,u16 color);
void LCD_ShowString(u16 x,u16 y,const u8 *p,u16 color);
u32 mypow(u8 m,u8 n);
void LCD_ShowNum(u16 x,u16 y,u16 num,u8 len,u16 color);
void LCD_ShowNum1(u16 x,u16 y,float num,u8 len,u16 color);
void LCD_ShowPicture(u16 x1,u16 y1,u16 x2,u16 y2);


//画笔颜色
#define WHITE         	 0xFFFF
#define BLACK         	 0x0000	  
#define BLUE           	 0x001F  
#define BRED             0XF81F
#define GRED 			       0XFFE0
#define GBLUE			       0X07FF
#define RED           	 0xF800
#define MAGENTA       	 0xF81F
#define GREEN         	 0x07E0
#define CYAN          	 0x7FFF
#define YELLOW        	 0xFFE0
#define BROWN 			     0XBC40 //棕色
#define BRRED 			     0XFC07 //棕红色
#define GRAY  			     0X8430 //灰色
//GUI颜色

#define DARKBLUE      	 0X01CF	//深蓝色
#define LIGHTBLUE      	 0X7D7C	//浅蓝色  
#define GRAYBLUE       	 0X5458 //灰蓝色
//以上三色为PANEL的颜色 
 
#define LIGHTGREEN     	 0X841F //浅绿色
#define LGRAY 			     0XC618 //浅灰色(PANNEL),窗体背景色

#define LGRAYBLUE        0XA651 //浅灰蓝色(中间层颜色)
#define LBBLUE           0X2B12 //浅棕蓝色(选择条目的反色)


void LCD_View_Init(void);


#define _Windows_S_X  5
#define _Windows_S_Y  5
#define _Windows_E_X  235
#define _Windows_E_Y  235


#define _Title_E_Y (_Windows_S_Y+_Win_Height)

//连接状态栏
#define _Connect_E_Y (_Title_E_Y+_Win_Height)


//当前连接类型
#define _Connect_TYPE_E_Y (_Connect_E_Y)
#define _Connect_TYPE_E_X (_Windows_S_X+120)

#define _Text_X  10

#define _Data_SS_E_Y (_Connect_E_Y+_Win_Height)

#define _PIN_SS_E_Y  (_Data_SS_E_Y+_Win_Height)

#define _Output_Text_Y  _PIN_SS_E_Y+5
#define _Output_Text_X  _Text_X
#define _Windows_Outpu_S_Y  _Data_SS_E_Y


#define _Windows_Color  LGRAY
#define _Windows_Sub_Color  LGRAYBLUE

#define _Win_Height  20
#define _Row_Height  16


#define FRONT_COLOR RED

					  		 
#endif  
	 
	 



