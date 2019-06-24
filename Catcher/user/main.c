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
//#include "adc.h"
#include "sd.h"
#include "sram.h" 
#include "String.h"


extern u32 count;
	//当前应该进入中断类别
extern u16       u16EXIT_Type;
extern u8         u8Clk_EXIT_TYPE;

//通道
extern u8      u8Channel;

extern u16     u8Counter[2];
// 存储 CLK 间隔的 
extern u16     u16CLK[100000][2];
//当前CLKNumber
extern uint64_t u64CurCLK;
//之前CLKNumber
extern uint64_t u64PreCLK;

u8 u8CurSDData[512];
u32 u32CurSDDataLen;

u32 u32SaveSDLen;
u32 u32SavedSector;


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
	

	for (ii = 0; ii < u8Counter[_Channel]; ii+= Len)
	{
		
		//SendCharData(0xFE);
		Len = (u16CLK[ii][_Channel]>>8)&0x7;
		
		for(jj = 0 ; jj < Len; jj++)
			Send16Data(u16CLK[ii+jj][_Channel]);

	}

	u8Counter[_Channel] = 0;

}




void  Initialize_Module(void)
{
		//FSMC_SRAM_Init();

	u8 i = 0;
	u32 sd_size;
	u8 sd_buf[6];

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

	//IO口使用外部中断 , CLK 外部中断 
	PINx_EXIT_Init();

	LCD_Dislay_Printf("Initialize Exit IO finished!");

	if (SD_Init())
	{
		LCD_Dislay_Printf("Initialize SD failed!");
	}
	LCD_Dislay_Printf("Initialize SD finished!");
	
	

    if(SD_Type == 0x06)
	{
		LCD_Dislay_Printf("SDV2HC OK!");
	}
	else if(SD_Type == 0x04)
	{
		LCD_Dislay_Printf("SDV2 OK!");
	}
	else if(SD_Type == 0x02)
	{
		LCD_Dislay_Printf("SDV1 OK!");
	}
	else if(SD_Type == 0x01)
	{
		LCD_Dislay_Printf("MMC OK!");
	}
	
	LCD_Dislay_Printf("SD Card Size:");
	
	sd_size=SD_GetSectorCount();//得到扇区数
	sd_size=sd_size>>11;  //显示SD卡容量   MB

	sd_buf[0] = sd_size / 10000 + 0x30;
	sd_buf[1] = sd_size % 10000 / 1000 + 0x30;
	sd_buf[2] = sd_size % 10000 % 1000 / 100 + 0x30;
	sd_buf[3] = sd_size % 10000 % 1000 % 100 / 10 + 0x30;
	sd_buf[4] = sd_size % 10000 % 1000 % 100 % 10 + 0x30;
	sd_buf[5] = '\0';
	LCD_Dislay_Printf(sd_buf);


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

	u16EXIT_Type    = EXIT_ALL;
	u8Clk_EXIT_TYPE = CLK_EXITT_ALL;

	u64CurCLK = 0;
    u64PreCLK = 0;

    u32SavedSector  = 20;
	u32CurSDDataLen = 0;
	u32SaveSDLen    = 0;


}

void SendEmptyData()
{

	uint64_t u64CurClk;
	uint64_t u64Diff;
	u16      uCurDiff[8];
	u16      u16DiffLen;
	u16      u16CurStatue;
	u8       jj;

	u16DiffLen   = 0;
	u16CurStatue = 0;
	u64CurClk    = count * 0xFFFF + TIM_GetCounter(TIM2);
	u64Diff      = u64CurClk - u64PreCLK;
	u16CurStatue = GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_2);
	if (u16CurStatue)
		u16CurStatue = EXIT_RAISE;

	_ConverntClkDif(u64Diff, u16CurStatue, Pin_IO, uCurDiff, &u16DiffLen);

	for (jj = 0; jj < u16DiffLen; jj++)
		Send16Data(uCurDiff[jj]);
	
	u64PreCLK = u64CurClk;


}

void SendRamData(u8* SendEmpty)
{

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
			*SendEmpty = 0;
		}
		else if(*SendEmpty == 0)
		{
			//SendEmpty = 1;
			//SendCharData(0xFF);
			//SendCharData(GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_2));
			//Send64Data(count * 0xFFFF + TIM_GetCounter(TIM2));
			
		  //printf("Empty");

			//Send16Data(0x4);
		  
	//	_ConverntClkDif()
	//		SendEmptyData();
			*SendEmpty = 1;
		//	delay_ms(100);

		}
}

void Save2SD(u8* u8Data,u32 uLen)
{

	u8 SaveCount;
	u32 uCurLen;
	//u32 Countl

	uCurLen = u32CurSDDataLen + uLen;

	SaveCount = uCurLen / 512;

	SD_WriteDisk(u8Data, u32SavedSector, SaveCount);

	u32CurSDDataLen = uCurLen % 512;

	u32SavedSector += SaveCount;


}

void SaveChannelData(u8 _Channel)
{

		u16 ii;
		u8 Len;
		u8 jj;


		for (ii = 0; ii < u8Counter[_Channel]; ii += Len)
		{

			//SendCharData(0xFE);
			Len = (u16CLK[ii][_Channel] >> 8) & 0x7;

			for (jj = 0; jj < Len; jj++)
				Send16Data(u16CLK[ii + jj][_Channel]);

		}

		u8Counter[_Channel] = 0;


}




void SaveRamData()
{

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



int main(void)
{	
	u8 SendEmpty = 0;

	//初始化各个模块
	Initialize_Module();

	Initialize_Global_variable();

	Tim_Enable();			//同步开始计数
	


	while(1)
	{	
		SendRamData(&SendEmpty);
		
	}
}





