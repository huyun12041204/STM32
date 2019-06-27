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
//#include "sram.h" 
#include "String.h"
//#include "malloc.h" 
#include "sd.h"
//#include "flash.h"
//#include "ff.h" 
//#include "fatfs_app.h"
//#include "flash.h"
#include "Command.h"
#include "var.h"






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
u16 lCurX;

void LCD_Dislay_Init()
{
	//初始化设备
	TFTLCD_Init();
	
//	FRONT_COLOR = YELLOW;
	LCD_Clear(BLACK);
	FRONT_COLOR = RED;
	lCurY = 10;
    lCurX = 10;
}



void LCD_Dislay_Printf(u8 *p)
{

	GUI_Show12ASCII(10, lCurY, p, FRONT_COLOR, BLACK);

	lCurY += 20;

	if (lCurY > 380)
	{
		lCurY = 10;
	}
	
	delay_ms(10);

}
#endif


int fputc(int ch,FILE *p)  //函数默认的，在使用printf函数时自动调用
{
		

 
	
	if(ch == '\n')
	{
		lCurX  = 10;
		lCurY += 20;
		if (lCurY > 480)	
			lCurY = 10;
	}
	else
	{
		 GUI_Show12ASCII(lCurX, lCurY, (uint8_t*)&ch, FRONT_COLOR, BLACK);
			lCurX += 8;
	}
		
	

	
//     	USART_SendData(USART1,(u8)ch);	
//	while(USART_GetFlagStatus(USART1,USART_FLAG_TXE)==RESET);

	return ch;
}



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





//void SendCharData(char cData)
//{
//	USART_SendData(USART1, cData);
//	while (USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);

//}
//void Send64Data(uint64_t u64Data)
//{
//	uint64_t temp;
//	u8 ii;
//	char Data[8];

//	temp = u64Data;

//	for (ii = 8 ; ii > 0 ; ii--)
//	{
//		Data[ii - 1] = temp % 0x100;
//		temp = temp / 0x100;
//	}
//	for (ii = 0; ii < 8; ii++)
//	{
//		SendCharData(Data[ii]);
//			
//	}

//}

//void Send16Data(u16 u16Data)
//{

//	SendCharData(u16Data/0x100);
//	SendCharData(u16Data %0x100);
//}


void SendChannelData()
{

	u16 ii;
	u16 u16CurCLKCount;
	
	u16CurCLKCount = uCLKCount;
	if (uSendCLKCOunt > u16CurCLKCount)
	{
		u16CurCLKCount = u16CurCLKCount +_MaxCLKCount;
	}
	
	
	for (ii = uSendCLKCOunt; ii < u16CurCLKCount; ii+= 1)
	{
		if(ii >= _MaxCLKCount)
			SendCharData(u8CLK[ii -_MaxCLKCount]);
		else
			SendCharData(u8CLK[ii]);
	}
	if(ii >= _MaxCLKCount)
		uSendCLKCOunt = ii -_MaxCLKCount;
	else
		uSendCLKCOunt = ii;

}




void  Initialize_Module(void)
{
		//FSMC_SRAM_Init();

	
//	u8 i=0;
//	u32 free,total;
//	u8 i = 0;
//	u32 sd_size;
//	u8 sd_buf[6];

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
	
	
	
	//EN25QXX_Init();				//初始化EN25Q128	  
	
	LCD_Dislay_Printf("Initialize flash finished!");
	

	if (SD_Init())
	{
		LCD_Dislay_Printf("SD Card Error!");
	}
	LCD_Dislay_Printf("SD Card OK!");
	
//	FATFS_Init();							//为fatfs相关变量申请内存				 
//	

//	
// 	f_mount(fs[0],"0:",1); 					//挂载SD卡 	
//	
//	while(FATFS_GetFree("0:",&total,&free))	//得到SD卡的总容量和剩余容量
//	{
//		LCD_Dislay_Printf("FATFS Error!");
//		delay_ms(200);
//	}
//	
//	
//	printf("SD Total Size:%ldMB\n",total>>10);
//	
//	printf("SD Total Size:%ldMB\n",free>>10);
	
//	LCD_Dislay_Printf("SD Total Size:");
	
	//LCD_Dislay_Printf("SD Free Size:");

  if(SD_Type == 0x06)
	{
		LCD_Dislay_Printf((u8*)"SDV2HC OK!");
	}
	else if(SD_Type == 0x04)
	{
		LCD_Dislay_Printf((u8*)"SDV2 OK!");
	}
	else if(SD_Type == 0x02)
	{
		LCD_Dislay_Printf((u8*)"SDV1 OK!");
	}
	else if(SD_Type == 0x01)
	{
		LCD_Dislay_Printf((u8*)"MMC OK!");
	}
	
	//LCD_Dislay_Printf("SD Card Size:");
	
	//sd_size=SD_GetSectorCount;//得到扇区数
	
	printf(("SD Total Size:%ld MB\n"),(long)(SD_GetSectorCount()>>11));
	
//	sd_size=sd_size>>11;  //显示SD卡容量   MB

//	sd_buf[0] = sd_size / 10000 + 0x30;
//	sd_buf[1] = sd_size % 10000 / 1000 + 0x30;
//	sd_buf[2] = sd_size % 10000 % 1000 / 100 + 0x30;
//	sd_buf[3] = sd_size % 10000 % 1000 % 100 / 10 + 0x30;
//	sd_buf[4] = sd_size % 10000 % 1000 % 100 % 10 + 0x30;
//	sd_buf[5] = '\0';
//	LCD_Dislay_Printf(sd_buf);


}

void  Initialize_Global_variable(void)
{
	//设置CLK计数器0

    uCLKCount     = 0 ;
    uSendCLKCOunt = 0 ;
	
	memset(u8CLK, 0, sizeof(u8CLK));

	//CLK总数
	count = 0;

	u16EXIT_Type    = EXIT_ALL;
	u8Clk_EXIT_TYPE = CLK_EXITT_ALL;

	u64CurCLK = 0;
    u64PreCLK = 0;

    u32SavedSector    = _Start_Sector;
	u16Save2SDTempLen = 0;
//	u32CurSDDataLen = 0;
//	u32SaveSDLen    = 0;
	
	



}

//void SendEmptyData()
//{

//	uint64_t u64CurClk;
//	uint64_t u64Diff;
//	u16      uCurDiff[8];
//	u16      u16DiffLen;
//	u16      u16CurStatue;
//	u8       jj;

//	u16DiffLen   = 0;
//	u16CurStatue = 0;
//	u64CurClk    = count * 0xFFFF + TIM_GetCounter(TIM2);
//	u64Diff      = u64CurClk - u64PreCLK;
//	u16CurStatue = GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_2);
//	if (u16CurStatue)
//		u16CurStatue = EXIT_RAISE;

//	_ConverntClkDif(u64Diff, u16CurStatue, Pin_IO, uCurDiff, &u16DiffLen);

//	for (jj = 0; jj < u16DiffLen; jj++)
//		Send16Data(uCurDiff[jj]);
//	
//	u64PreCLK = u64CurClk;


//}

void SendRamData(u8* SendEmpty)
{
	
	
	SendChannelData();

}

u8 Save2SD(u8* u8Data,u32 uLen)
{

	u8 SaveCount;
	u8 u8Ret = 0;
	u32 u32SavedLen = 0;



	//Ram内存在未存储到SD内的数据，需要先存储

	if (u16Save2SDTempLen != 0) 
	{
		u32SavedLen = _MaxSectorSize - u16Save2SDTempLen;

	    //如果现有数据和存储数据还是不够512 则放在SDTemp
		if (uLen < u32SavedLen)
		{
			memcpy(SDTemp+ u16Save2SDTempLen, u8Data, uLen);
			u16Save2SDTempLen = u16Save2SDTempLen + uLen;
			return u8Ret;
		}
		//否则先存一个扇区
		memcpy(SDTemp+ u16Save2SDTempLen, u8Data, u32SavedLen);
		u8Ret = SD_WriteDisk(SDTemp, u32SavedSector, 1);
		if (u8Ret != 0)
			return u8Ret;
		u32SavedSector += 1;
	}

	SaveCount = (uLen - u32SavedLen) / _MaxSectorSize;

	if (SaveCount != 0)
	{
		u8Ret = SD_WriteDisk(u8Data+ u32SavedLen, u32SavedSector, SaveCount);
		if (u8Ret != 0)
			return u8Ret;
		u32SavedSector += SaveCount;
	}


	u32SavedLen       = u32SavedLen + SaveCount * _MaxSectorSize;
	u16Save2SDTempLen = uLen - u32SavedLen;
	memcpy(SDTemp , u8Data + u32SavedLen, u16Save2SDTempLen);



	return u8Ret;

}

u8 SaveChannelData()
{

	u16 u16CurCLKCount;
	u8 u8Ret = 0;
	u16CurCLKCount = uCLKCount;


	//如果send 大于 现有的 说明已经回滚了
	if (uSendCLKCOunt > u16CurCLKCount)
	{

		u8Ret = Save2SD(u8CLK+ uSendCLKCOunt, _MaxCLKCount - uSendCLKCOunt);
		if (u8Ret == 0)
			u8Ret = Save2SD(u8CLK, u16CurCLKCount);

	}
	else
	{
		u8Ret = Save2SD(u8CLK + uSendCLKCOunt, u16CurCLKCount - uSendCLKCOunt);
	}


	uSendCLKCOunt = u16CurCLKCount;
	
	//if(u8Ret == 0)
	//	printf("Save Success\n");
	//else
	//	printf("Save Failed %d\n",u8Ret);

	return u8Ret;


}

u8 ReadSDData(u32 u32Offset, u16 u16Len,u8* u8buf,u16 *u16bufLen)
{

	u16 u16OffSector;
	u16 uCurSectorOff;
	u8 u8Ret = 0;
	if ((u32Offset%512) != 0)
	{
		u16OffSector  = u32Offset / 512;
		uCurSectorOff = u32Offset % 512;
		u8Ret = SD_ReadDisk(u8buf, u16OffSector, 1);

		memcpy(u8buf, u8buf + uCurSectorOff, 512-uCurSectorOff);

		*u16bufLen = 512 - uCurSectorOff;
	}
	else
	{
		if ((u16Len % 512) != 0)
		{
			memcpy(u8buf, SDTemp, u16Save2SDTempLen);
			*u16bufLen = u16Save2SDTempLen;
		}
		else
		{
			u16OffSector = (u32Offset % 512) + 20;
			u8Ret = SD_ReadDisk(u8buf, u16OffSector, 1);
			*u16bufLen = 512;
		}
	}

	return u8Ret;
}


void ReadSendBuf()
{
	u8  ubuf[512];
	u16 uLen,ii;
	
	if(ReadSDData(0, 512,ubuf,&uLen) == 0)
	{
		printf("Read OK\n");
		
		for(ii = 0 ; ii <uLen;ii++ )
	   	SendCharData(ubuf[ii]);
		
	}
	else
	{
			printf("Read Error\n");
	}
	
	
	


}
int main(void)
{
//	u8 SendEmpty = 0;

	//初始化各个模块
	Initialize_Module();

	Initialize_Global_variable();
	
	_SendBuf_Init();
	_Command_Init();

	Tim_Enable();			//同步开始计数
	


	while(1)
	{	
		//SendChannelData();

		if(uSendCLKCOunt == uCLKCount)
		{
			
			continue;
		}
		if (SaveChannelData() == 0)
		{
				//	printf("Save successful\n");
		}
	
//		if(willSend == 1)
//		{		
//			ReadSendBuf();
//			willSend = 0;
//		}

		

	}
}
