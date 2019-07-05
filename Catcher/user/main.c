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
#include "sram.h" 
#include "String.h"
#include "malloc.h" 
#include "sd.h"
//#include "flash.h"
//#include "ff.h" 
//#include "fatfs_app.h"
//#include "flash.h"
#include "Command.h"
#include "var.h"
#include "dma.h"





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
	USART1_Init(864000);

	//显示屏
	LCD_Dislay_Init();

	LCD_Dislay_Printf("Initialize LCD finished!");
	

	//初始化计时器
	Tim_Init();		
	LCD_Dislay_Printf("Initialize TIM finished!");

	//IO口使用外部中断 , CLK 外部中断 
	PINx_EXIT_Init();

	LCD_Dislay_Printf("Initialize Exit IO finished!");
	
	
	
	////EN25QXX_Init();				//初始化EN25Q128	  
	//
	//LCD_Dislay_Printf("Initialize flash finished!");
	//

	if (SD_Init())
	{
		LCD_Dislay_Printf("SD Card Error!");
	}
	LCD_Dislay_Printf("SD Card OK!");


 // if(SD_Type == 0x06)
	//{
	//	LCD_Dislay_Printf((u8*)"SDV2HC OK!");
	//}
	//else if(SD_Type == 0x04)
	//{
	//	LCD_Dislay_Printf((u8*)"SDV2 OK!");
	//}
	//else if(SD_Type == 0x02)
	//{
	//	LCD_Dislay_Printf((u8*)"SDV1 OK!");
	//}
	//else if(SD_Type == 0x01)
	//{
	//	LCD_Dislay_Printf((u8*)"MMC OK!");
	//}
	//
	////LCD_Dislay_Printf("SD Card Size:");
	//
	////sd_size=SD_GetSectorCount;//得到扇区数
	//
	//printf(("SD Total Size:%ld MB\n"),(long)(SD_GetSectorCount()>>11));
	//
  FSMC_SRAM_Init();
	
	printf("Initialize Sram!\n"); 

	PINx_Level_Conversion_Init();

	printf("Level conversion finish!\n");
}

void  Initialize_Global_variable(void)
{
	//设置CLK计数器0

    uCLKCount     = 0 ;
    uSendCLKCOunt = 0 ;

#ifndef _2Channel
	memset(u8CLK, 0, sizeof(u8CLK));
#else
	memset(u8CLKT, 0, sizeof(u8CLKT));
	memset(uCount, 0, sizeof(uCount));
	u8Channel = 0;
#endif
	


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


u8 Save2SD(u8* u8Data,u32 uLen)
{

	u8 SaveCount;
	u8 u8Ret = 0;
	u32 u32SavedLen = 0;


  // printf("%d",uLen);
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
		if(u8Ret != 0) 
				printf("L%d",u8Ret);
			//printf("1%d",u8Ret);

		
	
		u32SavedSector += 1;
	}

	SaveCount = (uLen - u32SavedLen) / _MaxSectorSize;

	if (SaveCount != 0)
	{	
//		for(ii = 0 ; ii < 10 ; ii ++)
//		{
		  u8Ret = SD_WriteDisk(u8Data+ u32SavedLen, u32SavedSector, SaveCount);
			if(u8Ret != 0) 
				printf("2L%d",u8Ret);
		//	u8Ret = SD_WriteDisk(u8Data+ u32SavedLen, u32SavedSector, SaveCount);
				printf("2%d",u8Ret);
		//}
		u32SavedSector += SaveCount;
	}


	u32SavedLen       = u32SavedLen + SaveCount * _MaxSectorSize;
	u16Save2SDTempLen = uLen - u32SavedLen;
	memcpy(SDTemp , u8Data + u32SavedLen, u16Save2SDTempLen);



	return u8Ret;

}


u8 SendChannelData()
{
	
	u16 u16CurCLKCount;
	u8 u8Ret = 0;
	u16CurCLKCount = uCLKCount;


	//如果send 大于 现有的 说明已经回滚了
	if (uSendCLKCOunt > u16CurCLKCount)
	{

		u8Ret = Save2SD(u8CLK + uSendCLKCOunt, _MaxCLKCount - uSendCLKCOunt);
		if (u8Ret == 0)
			u8Ret = Save2SD(u8CLK, u16CurCLKCount);

	}
	else
	{
		u8Ret = Save2SD(u8CLK + uSendCLKCOunt, u16CurCLKCount - uSendCLKCOunt);
	}


	uSendCLKCOunt = u16CurCLKCount;

	
	return u8Ret;
	
	
	
}


u8 SaveChannelData()
{

#ifndef _2Channel
	u16 u16CurCLKCount;
	u8 u8Ret = 0;
	u16CurCLKCount = uCLKCount;


	//如果send 大于 现有的 说明已经回滚了
	if (uSendCLKCOunt > u16CurCLKCount)
	{

		u8Ret = Save2SD(u8CLK + uSendCLKCOunt, _MaxCLKCount - uSendCLKCOunt);
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

#else
	u8 u8Ret = 0;
	u8 u8Cur = u8Channel;


	if (uCount[u8Cur]!=0)
	{
		if (u8Channel == 0)
			u8Channel = 1;
		else
			u8Channel = 0;
		u8Ret = Save2SD(u8CLKT[u8Cur], uCount[u8Cur]);
		uCount[u8Cur] = 0;
	}




	return u8Ret;

#endif




}


void Test_SD(void)
{
	 u32 i;
	u8 u8Ret;
	 memset(u8CLK , 0x55 ,1024);
	
	 printf("Start Write SD\n"); 
	for(i = 0 ; i < 20000 ; i++)
	{
		u8Ret = SD_WriteDisk(u8CLK,i,1);
		
		if(u8Ret!=0)
			printf("%d,%d!!\n",i,u8Ret);
			
	}
	
	printf("End Write SD\n"); 
	
	
		printf("Start Read SD\n"); 
		for(i = 0 ; i < 20000 ; i++)
	{
		u8Ret =SD_ReadDisk(u8CLK+1024,i,1);
		
		if(u8Ret!=0)
			printf("%d,%d!!\n",i,u8Ret);
		
		if(memcmp(u8CLK+1024,u8CLK,512) != 0)
			printf("%d^^\n",i);
					
	}
	
		printf("End Read SD\n"); 
}

int main(void)
{
//	u8 SendEmpty = 0;

	//初始化各个模块
	Initialize_Module();

	Initialize_Global_variable();
	
	DMA_Init_(DMA1_Channel4,(u32)&USART1->DR,(u32)u8UsartSendBuf,_MaxUsartSendSize);
	
	_SendBuf_Init();
	_Command_Init();
	
	//SramOffset = 0;
	//此处需要先读取当前各个端口状态,VCC RST IO
	_Pre_Pin_Statue = GetPinValue();

	Tim_Enable();			//同步开始计数
	
 // Test_SD();
	printf("Start ...!\n"); 
	while(1)
	{	
		//SendChannelData();

		if(uSendCLKCOunt != uCLKCount)
		{
			//delay_us()
			SaveChannelData();	
		}
		else if (DMA_GetFlagStatus(DMA1_FLAG_TC4) != 0)//判断通道4传输完成
		{
		//	printf("Enable USART IT\n"); 
			USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
		//	USART_ITConfig(USART1, USART_IT_RXNE, DISABLE);
			DMA_ClearFlag(DMA1_FLAG_TC4);
			
		}
				

	
	}
}


