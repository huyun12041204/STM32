/* 程序下载后D1指示灯闪烁表示程序正常运行，按键K_UP切换频率显示控制和电压控制调节，
	K_DOWN按键减，K_RIGHT按键加，AD输入端口采用PA2，可以使用另外一块普中STM32开发板
	下载里面配套的一个脉冲发生程序进去测试，脉冲通过PC1口发送出来通过导线直接输入到示波器
	开发板上的PA2口即可检测到具体的波形，如果只有一块普中STM32开发板的朋友可以使用信号
	发生器产生信号输入到PA2口。程序只是做了一个简单的采集和显示调节，采集的精度和准确度
	还是比较高的。*/

#include "system.h"
#include "SysTick.h"
#include "usart.h"
#include "led.h"
#include "button.h"
#include "tftlcd.h"
#include "gui.h"
#include "tim.h"
#include "stm32f10x_it.h"
#include "adc.h"

#include "String.h"


extern u32 count;
	//当前应该进入中断类别
extern u8       u8EXIT_Type;

//通道
extern u8      u8Channel;

extern u16     u8Counter[2];
// 存储 CLK 间隔的 
extern u16     u16CLK[2000][2];
//当前CLKNumber
extern uint64_t u64CurCLK;
//之前CLKNumber
extern uint64_t u64PreCLK;


#if 0


void clear_point(u16 hang)
{
	u8 index_clear_lie = 0;
	FRONT_COLOR = DARKBLUE;
	for (index_clear_lie = 0; index_clear_lie < 201; index_clear_lie++)
	{
		//	lcd_huadian(hang,index_clear_lie,FRONT_COLOR);
	}
	FRONT_COLOR = RED;
}
void ShowCLK2TFT(u16 u16CLK)
{
	u8 clk_buf[6];

	clk_buf[u16Digit2Ascii(u16CLK, clk_buf)] = '\0';

	GUI_Show12ASCII(60, 20, clk_buf, FRONT_COLOR, WHITE);

	GUI_Show12ASCII(100, 20, "kHz", FRONT_COLOR, WHITE);

}

#else

u16 lCurY;

void LCD_Dislay_Init()
{
	//初始化设备
	TFTLCD_Init();
	
//	FRONT_COLOR = YELLOW;
	LCD_Clear(BLACK);
	FRONT_COLOR = RED;
	lCurY = 20;

}



void LCD_Dislay_Printf(uint8_t *p)
{

	GUI_Show12ASCII(10, lCurY, p, FRONT_COLOR, BLACK);

	lCurY += 20;

	if (lCurY > 480)
	{
		lCurY = 20;
	}
	
	delay_ms(2000);

}
#endif




u8 u8Digit2Ascii(u8 u8Digit,u8* u8Ascii)
{

	u8 u8temp[3];
	u8 u8TDigit = u8Digit;
	u8 i;

	for ( i = 3; i > 0; i--)
	{
		u8temp[i-1]= u8TDigit % 10 + 0x30;
		u8TDigit = u8TDigit / 10;
	}

	for (i = 0; i < 2; i++)
	{
		if (u8temp[i] != 0x30)
			break;
	}

	memcpy(u8Ascii, u8temp+i, 3 - i);

	return 3 - i;

}

u8 u16Digit2Ascii(u16 u16Digit, u8* u8Ascii)
{

	u8 u8temp[5];
	u16 TDigit = u16Digit;
	u8 i;

	for (i = 5; i > 0; i--)
	{
		u8temp[i - 1] = TDigit % 10 + 0x30;
		TDigit = TDigit / 10;
	}


	for (i = 0; i < 4; i++)
	{
		if (u8temp[i] != 0x30)
			break;
	}

	memcpy(u8Ascii, u8temp + i, 5 - i);

	return 5 - i;

}


//void nvic_init(void)
//{
//	NVIC_InitTypeDef    NVIC_InitTypeStruct;
//	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
////	NVIC_InitTypeStruct.NVIC_IRQChannel = EXTI0_IRQn;
////	NVIC_InitTypeStruct.NVIC_IRQChannelPreemptionPriority =	2;
////	NVIC_InitTypeStruct.NVIC_IRQChannelSubPriority = 0;
////	NVIC_InitTypeStruct.NVIC_IRQChannelCmd = ENABLE;
////	NVIC_Init(&NVIC_InitTypeStruct);

//	/*NVIC_InitTypeStruct.NVIC_IRQChannel = EXTI3_IRQn;
//	NVIC_InitTypeStruct.NVIC_IRQChannelPreemptionPriority =	2;
//	NVIC_InitTypeStruct.NVIC_IRQChannelSubPriority = 1;
//	NVIC_InitTypeStruct.NVIC_IRQChannelCmd = ENABLE;
//	NVIC_Init(&NVIC_InitTypeStruct);

//	NVIC_InitTypeStruct.NVIC_IRQChannel = EXTI4_IRQn;
//	NVIC_InitTypeStruct.NVIC_IRQChannelPreemptionPriority =	2;
//	NVIC_InitTypeStruct.NVIC_IRQChannelSubPriority = 2;
//	NVIC_InitTypeStruct.NVIC_IRQChannelCmd = ENABLE;
//	NVIC_Init(&NVIC_InitTypeStruct);*/

//	NVIC_InitTypeStruct.NVIC_IRQChannel = TIM2_IRQn;  		   //配置中断优先级
//	NVIC_InitTypeStruct.NVIC_IRQChannelPreemptionPriority =	0;
//	NVIC_InitTypeStruct.NVIC_IRQChannelSubPriority = 0;
//	NVIC_InitTypeStruct.NVIC_IRQChannelCmd = ENABLE;
//	NVIC_Init(&NVIC_InitTypeStruct);

////	NVIC_InitTypeStruct.NVIC_IRQChannel = TIM3_IRQn; 
////	NVIC_InitTypeStruct.NVIC_IRQChannelPreemptionPriority =	2;
////	NVIC_InitTypeStruct.NVIC_IRQChannelSubPriority = 2;
////	NVIC_InitTypeStruct.NVIC_IRQChannelCmd = ENABLE;
////	NVIC_Init(&NVIC_InitTypeStruct);

//	NVIC_InitTypeStruct.NVIC_IRQChannel = TIM4_IRQn;
//	NVIC_InitTypeStruct.NVIC_IRQChannelPreemptionPriority = 2;
//	NVIC_InitTypeStruct.NVIC_IRQChannelSubPriority = 2;
//	NVIC_InitTypeStruct.NVIC_IRQChannelCmd = ENABLE;
//	NVIC_Init(&NVIC_InitTypeStruct);
//	
//	NVIC_InitTypeStruct.NVIC_IRQChannel = EXTI2_IRQn;
//	NVIC_InitTypeStruct.NVIC_IRQChannelPreemptionPriority =	2;
//	NVIC_InitTypeStruct.NVIC_IRQChannelSubPriority = 0;
//	NVIC_InitTypeStruct.NVIC_IRQChannelCmd = ENABLE;
//	NVIC_Init(&NVIC_InitTypeStruct);

//	NVIC_InitTypeStruct.NVIC_IRQChannel = EXTI3_IRQn;
//	NVIC_InitTypeStruct.NVIC_IRQChannelPreemptionPriority = 2;
//	NVIC_InitTypeStruct.NVIC_IRQChannelSubPriority = 0;
//	NVIC_InitTypeStruct.NVIC_IRQChannelCmd = ENABLE;
//	NVIC_Init(&NVIC_InitTypeStruct);
//}

//void rcc_init(void)
//{
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE, ENABLE);
//	//RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1,ENABLE);
//	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
//	//RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
////	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);

//	//RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOE|RCC_APB2Periph_AFIO, ENABLE);
//	////RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);
//	//RCC_ADCCLKConfig(RCC_PCLK2_Div6);
//	//RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1,ENABLE);
//}

//void gpio_init(void)
//{
//	GPIO_InitTypeDef GPIO_InitTypeStruct;
//
//
//	GPIO_InitTypeStruct.GPIO_Pin = GPIO_Pin_0;
//	GPIO_InitTypeStruct.GPIO_Speed = GPIO_Speed_50MHz;		 		//外部时钟的，用来测频率的，
//	GPIO_InitTypeStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
//	GPIO_Init(GPIOA, &GPIO_InitTypeStruct);
//
//
//
//	GPIO_InitTypeStruct.GPIO_Pin = GPIO_Pin_2;
//	GPIO_InitTypeStruct.GPIO_Speed = GPIO_Speed_50MHz;		 		//IO 口下沿中断
//	GPIO_InitTypeStruct.GPIO_Mode = GPIO_Mode_IPU; 
//	GPIO_Init(GPIOE, &GPIO_InitTypeStruct);
//	
//
////	GPIO_InitTypeStruct.GPIO_Pin = GPIO_Pin_2;
////	GPIO_InitTypeStruct.GPIO_Speed = GPIO_Speed_50MHz;				 //外部时钟的，用来测频率的，
////	GPIO_InitTypeStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
////	GPIO_Init(GPIOD, &GPIO_InitTypeStruct);
////
////	GPIO_InitTypeStruct.GPIO_Pin = GPIO_Pin_2;
////	GPIO_InitTypeStruct.GPIO_Speed = GPIO_Speed_50MHz;		 		 //adc输入引脚
////	GPIO_InitTypeStruct.GPIO_Mode = GPIO_Mode_AIN;
////	GPIO_Init(GPIOA, &GPIO_InitTypeStruct);
////
//////	GPIO_InitTypeStruct.GPIO_Pin = GPIO_Pin_3 | GPIO_Pin_4;
//////	GPIO_InitTypeStruct.GPIO_Speed = GPIO_Speed_50MHz;		 		 //外部中断的io配置
//////	GPIO_InitTypeStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
//////	GPIO_Init(GPIOE, &GPIO_InitTypeStruct);
////
////	GPIO_InitTypeStruct.GPIO_Pin = GPIO_Pin_0;
////	GPIO_InitTypeStruct.GPIO_Speed = GPIO_Speed_50MHz;		 		//外部中断的io配置
////	GPIO_InitTypeStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
////	GPIO_Init(GPIOA, &GPIO_InitTypeStruct);
//
//	//GPIO_InitTypeStruct.GPIO_Pin = GPIO_Pin_8;					 //定时器1触发ad转换的输出的那个口
//	//GPIO_InitTypeStruct.GPIO_Speed = GPIO_Speed_50MHz;
//	//GPIO_InitTypeStruct.GPIO_Mode = GPIO_Mode_AF_PP;
//	//GPIO_Init(GPIOA, &GPIO_InitTypeStruct);
//
//	//GPIO_InitTypeStruct.GPIO_Pin = GPIO_Pin_3;
//	//GPIO_InitTypeStruct.GPIO_Speed = GPIO_Speed_50MHz;		 		// adc3
//	//GPIO_InitTypeStruct.GPIO_Mode = GPIO_Mode_Out_PP;
//	//GPIO_Init(GPIOA, &GPIO_InitTypeStruct);
//
//	//GPIO_InitTypeStruct.GPIO_Pin = GPIO_Pin_4;
//	//GPIO_InitTypeStruct.GPIO_Speed = GPIO_Speed_50MHz;		 		//	adc4
//	//GPIO_InitTypeStruct.GPIO_Mode = GPIO_Mode_Out_PP;
//	//GPIO_Init(GPIOA, &GPIO_InitTypeStruct);
//
//	//GPIO_InitTypeStruct.GPIO_Pin = GPIO_Pin_5;
//	//GPIO_InitTypeStruct.GPIO_Speed = GPIO_Speed_50MHz;		 		//	adc5
//	//GPIO_InitTypeStruct.GPIO_Mode = GPIO_Mode_Out_PP;
//	//GPIO_Init(GPIOA, &GPIO_InitTypeStruct);
//
//	//GPIO_InitTypeStruct.GPIO_Pin = GPIO_Pin_6;
//	//GPIO_InitTypeStruct.GPIO_Speed = GPIO_Speed_50MHz;		 		//	adc6
//	//GPIO_InitTypeStruct.GPIO_Mode = GPIO_Mode_Out_PP;
//	//GPIO_Init(GPIOA, &GPIO_InitTypeStruct);
//
//	//GPIO_InitTypeStruct.GPIO_Pin = GPIO_Pin_7;
//	//GPIO_InitTypeStruct.GPIO_Speed = GPIO_Speed_50MHz;		 		// adc7
//	//GPIO_InitTypeStruct.GPIO_Mode = GPIO_Mode_Out_PP;
//	//GPIO_Init(GPIOA, &GPIO_InitTypeStruct);
//
//
//}





void SendCharData(char cData)
{
	USART_SendData(USART1, cData);
	while (USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);

}
void Send64Data(uint64_t u64Data)
{
	uint64_t temp;
	u8 ii;
	char Data[8];

	temp = u64Data;

	for (ii = 8 ; ii > 0 ; ii--)
	{
		Data[ii - 1] = temp % 0x100;
		temp = temp / 0x100;
	}
	for (ii = 0; ii < 8; ii++)
	{
		SendCharData(Data[ii]);
			
	}

}

void Send16Data(u16 u16Data)
{

	SendCharData(u16Data/0x100);
	SendCharData(u16Data %0x100);
}


void SendChannelData(uint8_t      _Channel)
{
	u16 ii;
	u8 Len;
	u8 jj;
	

	for (ii = 0; ii < u8Counter[_Channel]; ii++)
	{
		
		SendCharData(0xFE);
		Len = u16CLK[ii][_Channel]/0x2000 ;
		
		for(jj = 0 ; jj <= Len; jj++)
			Send16Data(u16CLK[ii+jj][_Channel]);
		
		ii = ii+ Len;
	



	}

	u8Counter[_Channel] = 0;

}




void  Initialize_Module(void)
{
	//初始化时钟
	SysTick_Init(72);

	//定义中断优先级
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);  //中断优先级分组分2组

	//USART1 115200
	USART1_Init(115200);

	//显示屏
	LCD_Dislay_Init();

	LCD_Dislay_Printf("Initialize LCD finished!");
	

	//初始化计时器
	Tim_Init();		
	LCD_Dislay_Printf("Initialize TIM finished!");

	//IO口使用外部中断
	IO_Init();

	LCD_Dislay_Printf("Initialize Exit IO finished!");

}

void  Initialize_Global_variable(void)
{
	//设置CLK计数器0
	memset(u8Counter, 0, sizeof(u8Counter));
	//设置通道0
	u8Channel = 0;
	memset(u16CLK, 0, sizeof(u16CLK));

	//CLK总数
	count = 0;

	u8EXIT_Type = EXIT_ALL;

	  u64CurCLK = 0;
	  u64PreCLK = 0;

//	  u8Counter =



}

int main(void)
{	
	u8 SendEmpty = 0;

	//初始化各个模块
	Initialize_Module();

	Initialize_Global_variable();

	Tim_Enable();			//同步开始计数
	


	while(1)
	{	


  //  printf("%llu",count * 0xFFFF + TIM_GetCounter(TIM2));
		if (u8Counter[u8Channel] != 0)
		{
			if (u8Channel == 0)
			{
				u8Channel = 1;
				SendChannelData(0);
			}
			else
			{
				u8Channel = 0;
				SendChannelData(1);

			}
			SendEmpty = 0;
		}
		else if(	SendEmpty == 0)
		{
			//SendEmpty = 1;
			//SendCharData(0xFF);
			//SendCharData(GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_2));
			//Send64Data(count * 0xFFFF + TIM_GetCounter(TIM2));
			
		//	printf("Empty");

			delay_ms(1000);

		}


		
	
	}
}





