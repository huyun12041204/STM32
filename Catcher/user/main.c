/* 程序下载后D1指示灯闪烁表示程序正常运行，按键K_UP切换频率显示控制和电压控制调节，
	K_DOWN按键减，K_RIGHT按键加，AD输入端口采用PA2，可以使用另外一块普中STM32开发板
	下载里面配套的一个脉冲发生程序进去测试，脉冲通过PC1口发送出来通过导线直接输入到示波器
	开发板上的PA2口即可检测到具体的波形，如果只有一块普中STM32开发板的朋友可以使用信号
	发生器产生信号输入到PA2口。程序只是做了一个简单的采集和显示调节，采集的精度和准确度
	还是比较高的。*/

#include "system.h"
#include "SysTick.h"
#include "usart.h"
//#include "led.h"
//#include "button.h"
#include "tftlcd.h"
#include "gui.h"
#include "tim.h"
#include "stm32f10x_it.h"
#include "sram.h" 
#include "String.h"
//#include "malloc.h" 
#include "sd.h"

#include "var.h"


//移植USB时候的头文件
//#include "mass_mal.h"
#include "usb_lib.h"
#include "hw_config.h"
#include "usb_pwr.h"


#include "usbio.h"
extern volatile uint32_t EP1_ReceivedCount;
u8 SendIndex = 0;

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

	if (lCurY > 300)
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
		if (lCurY > 300)	
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




//USB使能连接/断线
//enable:0,断开
//       1,允许连接	   
void USB_Port_Set(u8 enable)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);    //使能PORTA时钟		 
	if(enable)_SetCNTR(_GetCNTR()&(~(1<<1)));//退出断电模式
	else
	{	  
		_SetCNTR(_GetCNTR()|(1<<1));  // 断电模式
		GPIOA->CRH&=0XFFF00FFF;
		GPIOA->CRH|=0X00033000;
		PAout(12)=0;	    		  
	}
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
	//USART1_Init(864000);

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
		LCD_Dislay_Printf("SD Card Error!");
	}
	LCD_Dislay_Printf("SD Card OK!");
	
  FSMC_SRAM_Init();
	
	printf("Initialize Sram!\n"); 

	PINx_Level_Conversion_Init();

	printf("Level conversion finish!\n");
	
	
	delay_ms(100);
	USB_Port_Set(0); 	//USB先断开
	delay_ms(700);
	USB_Port_Set(1);	//USB再次连接
	USB_Interrupts_Config();
	Set_USBClock();
	USB_Init();

	printf("USB Finish...\n");

}

void  Initialize_Global_variable(void)
{

	//当前CLKNumber
 u64CurCLK = 0;
//之前CLKNumber
 u64PreCLK = 0;
	
 u32CLKLen  = 0;
 u32SendLen = 0;
 u32SaveLen = 0;

//TIM2 的计数器
 count = 0;
	
	
 Tim5Count = 0;



}



u8 SendData_USB(uint8_t bEpNum,uint8_t *data,uint32_t dataNum)
{

	if(dataNum > 64)
		dataNum = 64;

	return USB_SendData(ENDP1,data,dataNum);
}



u8 SendChannelData_USB(void)
{
	u32 u32CurCount = u32CLKLen;
	
	u32 u32WillSend;

	u8 u8Ret = 0;
	if (GetEPTxStatus(ENDP1) != EP_TX_NAK)
		return 1;
	


	u32WillSend = u32CurCount - u32SendLen;
	

	if(u32WillSend > 64)
		u32WillSend = 64;
	
	FSMC_SRAM_ReadBuffer(_USB_SendBuf, u32SendLen ,u32WillSend);		
	
	u8Ret = SendData_USB(ENDP1,_USB_SendBuf,u32WillSend );

	u32SendLen = u32SendLen+ u8Ret;


	return 0;

}


u8 SendChannelData_SD_USB(void)
{
	u32 u32CurCount = u32SaveLen;
	
	u32 u32WillSend;
	
	u8 u8Ret = 0;
	if (GetEPTxStatus(ENDP1) != EP_TX_NAK)
		return 1;
	
		
	if(((u32SendLen%512) == 0)||((u32SendLen%64) != 0))
		SD_ReadDisk(_USB_SendBuf,u32SendLen/512 +_StartSector,1);


	u32WillSend = (u32SendLen/512+1)*512 - u32SendLen;
	
	if(u32WillSend>64)
		u32WillSend = 64;

	u8Ret = SendData_USB(ENDP1,_USB_SendBuf +u32SendLen%512 ,u32WillSend );

	u32SendLen = u32SendLen+ u8Ret;


	return 0;

}




u8 SaveChannelData_SD(void)
{
	u32 u32willSave;
	u8 __Count;

	u32willSave = u32CLKLen - u32SaveLen;
	
	if(u32willSave>0x2000)
		__Count = 0x20;
	else
		__Count = u32willSave/512;
	
	u32willSave = __Count*512;

	FSMC_SRAM_ReadBuffer(_SD_SaveBuf, u32SaveLen, u32willSave);
	
	if (SD_WriteDisk(_SD_SaveBuf, (u32SaveLen / 512) +_StartSector, __Count)!=0) 
		SD_WriteDisk(_SD_SaveBuf, (u32SaveLen / 512) +_StartSector, __Count);

	u32SaveLen += u32willSave;

}


//u8 ReadBufer_SD()
//{
//
//
//
//}


void Test_Sram(void)

{
	u32 ii = 0;
	u8 jj;
	u8 Put[64];
	u8 Inp[64];
	printf("Start Test Sram...!\n"); 
	printf("Start Write Sram...!\n"); 
//	for (ii = 0 ; ii < _MaxSram ; ii+=64)
//	{

//	  memset(Put,0x00,64);
//		FSMC_SRAM_WriteBuffer(Put, ii, 64);
//	}
//	
//		printf("Start Read Sram...!\n"); 
//	for (ii = _MaxSram ; ii > 0 ; ii-=4)
//	{
//	
//		Put[0] = (ii>>24)&0xFF;
//		Put[1] = (ii>>16)&0xFF;
//		Put[2] = (ii>>8)&0xFF;
//    Put[3]= ii&0xFF;
//		
//		FSMC_SRAM_ReadBuf(Inp,ii-4,4);
//		
//		if((Put[0]!=Inp[0])  ||
//			(Put[1]!=Inp[1])  ||
//	   	(Put[2]!=Inp[2])  ||
//		  (Put[03]!=Inp[3]) )
//		{
//			printf("Error in SRAM %x\n",ii);
//			printf("Read  in SRAM %x\n",Inp[0]*0x1000000+Inp[1]*0x10000+Inp[2]*0x100+Inp[3]);
//			printf("Read  in SRAM %x\n",Put[0]*0x1000000+Put[1]*0x10000+Put[2]*0x100+Put[3]);
//			return;
//		}
//		
//	}

//  for (ii = 0 ; ii < _MaxSram ; ii+=64)
//	{
//	  	memset(Put,64%19,64);
//			FSMC_SRAM_WriteBuf(Put, ii, 64);	
//	}
//	
  Put[0] = 0x55;
  FSMC_SRAM_WriteBuffer(Put, 00, 1);	
	
	FSMC_SRAM_ReadBuffer(Inp, 1, 1);	
	printf("  SRAM in %x\n",Inp[0]);	
		FSMC_SRAM_ReadBuffer(Inp, 2, 1);	
	printf("  SRAM in %x\n",Inp[0]);	
		FSMC_SRAM_ReadBuffer(Inp, 3, 1);	
	printf("  SRAM in %x\n",Inp[0]);	
		FSMC_SRAM_ReadBuffer(Inp, 4, 1);	
	printf("  SRAM in %x\n",Inp[0]);	
	
//	for (ii = 0 ; ii < _MaxSram ; ii += 1)
//	{
//		FSMC_SRAM_ReadBuffer(Inp, ii, 1);		
//		if(Inp[0] == 0x55)
//			printf("Error in SRAM %x\n",ii);
//			
//	}

	
		printf("Test finish!");
}

int main(void)
{
	

	u8 Sended = 0;
    u8 SendInf = 0;
	u8 USB_Res[2];

	u32 u32Detal = 0;
	//初始化各个模块
	Initialize_Module();

	Initialize_Global_variable();
	
	//此处需要先读取当前各个端口状态,VCC RST IO
	_Pre_Pin_Statue = GetPinValue();

	Tim_Enable();			//同步开始计数

	
	printf("Start ...!\n"); 
	
 
	while(1)
	{	

			
		if((u32CLKLen - u32SaveLen )>512)
			 SaveChannelData_SD();

		if(u32SendLen != u32SaveLen)
		{
			if (GetEPTxStatus(ENDP1) != EP_TX_NAK)
				continue;
			
	//		if((u32CLKLen-u32SendLen)>0x3F0000)
	  	  SendChannelData_SD_USB();
//			else
//			  SendChannelData_USB();
	
		}
		

		

//		if(u32SendLen != u32CLKLen)
//		{
//	
//			if (GetEPTxStatus(ENDP1) != EP_TX_NAK)
//				continue;
//			
//		 	SendChannelData_USB();	
//			
//		
//      if((u32CLKLen-u32SendLen)>u32Detal)
//			{
//				u32Detal = (u32CLKLen-u32SendLen);
//				
//			//	printf("Detal %x -\n",u32Detal);
//			}
//			
//			if(u32Detal>0x3FFFFF)
//			{
//				printf("Detal %x -\n",u32Detal);
//				printf("Size : %x \n",u32CLKLen);
//			}
//				
//				
////			if(SendInf < 4)
////			{		
////				  SendChannelData_USB();		
////				   SendInf += 1;	
////			}
////			else if (SendInf == 0)
////			{
////				//printf("Send %x - %x\n",u32SendLen,u32CLKLen);
////				printf("No Send: %x -\n",u32CLKLen-u32SendLen);
////				SendInf = 1;
////			}
////			
//			Sended = 0;
//
//		}
//		else if(Sended == 0)
//		{
//				Sended = 1; 
//				printf("Size : %x \n",u32CLKLen);
//				printf("Detal %x -\n",u32Detal);
//
//		}
	
	}
}


