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
#include "flash.h"
//#include "sd.h"
//#include "SD_OP.h"
#include "stm32_eval_sdio_sd.h"
#include "var.h"


//移植USB时候的头文件
//#include "mass_mal.h"
#include "usb_lib.h"
#include "hw_config.h"
#include "usb_pwr.h"


#include "usbio.h"

#define _Text_X  10

#define _Windows_S_X  5
#define _Windows_S_Y  5
#define _Windows_E_X  230
#define _Windows_E_Y  390

#define _Title_E_Y (_Windows_S_Y+_Win_Height*2)

//连接状态栏
#define _Connect_E_Y (_Title_E_Y+_Win_Height*3)


//当前连接类型
#define _Connect_TYPE_E_Y (_Connect_E_Y)
#define _Connect_TYPE_E_X (_Windows_S_X+120)

#define _Text_X  10

#define _Data_SS_E_Y (_Connect_E_Y+_Win_Height*4)

#define _PIN_SS_E_Y (_Data_SS_E_Y+_Win_Height*4)

#define _Output_Text_Y  _PIN_SS_E_Y+5
#define _Output_Text_X  _Text_X
#define _Windows_Outpu_S_Y  _Data_SS_E_Y


#define _Windows_Color  LGRAY
#define _Windows_Sub_Color  LGRAYBLUE

#define _Win_Height  18
#define _Row_Height  16
extern volatile uint32_t EP1_ReceivedCount;
u8 SendIndex = 0;



u16 lCurY;
u16 lCurX;


u8 tempbuff[512];



/* Private typedef -----------------------------------------------------------*/
typedef enum {FAILED = 0, PASSED = !FAILED} TestStatus;

/* Private define ------------------------------------------------------------*/
#define BLOCK_SIZE            512 /* Block Size in Bytes */

#define NUMBER_OF_BLOCKS      32  /* For Multi Blocks operation (Read/Write) */
#define MULTI_BUFFER_SIZE    (BLOCK_SIZE * NUMBER_OF_BLOCKS)   //?????	 

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
uint8_t Buffer_Block_Tx[BLOCK_SIZE], Buffer_Block_Rx[BLOCK_SIZE];
uint8_t readbuff[BLOCK_SIZE];
uint8_t Buffer_MultiBlock_Tx[MULTI_BUFFER_SIZE], Buffer_MultiBlock_Rx[MULTI_BUFFER_SIZE];
volatile TestStatus EraseStatus = FAILED, TransferStatus1 = FAILED, TransferStatus2 = FAILED;



extern SD_CardInfo SDCardInfo;	


int i;



/* Private function prototypes -----------------------------------------------*/  
void SD_EraseTest(void);
void SD_SingleBlockTest(void);
void SD_MultiBlockTest(void);
void Fill_Buffer(uint8_t *pBuffer, uint32_t BufferLength, uint32_t Offset);
TestStatus Buffercmp(uint8_t* pBuffer1, uint8_t* pBuffer2, uint32_t BufferLength);
TestStatus eBuffercmp(uint8_t* pBuffer, uint32_t BufferLength);




void View_Init(void)
{

	LCD_DrawRectangleex( _Windows_S_X , _Windows_S_Y , _Windows_E_X , _Windows_E_Y ,_Windows_Color );
	LCD_DrawRectangleex(_Windows_S_X+1,_Windows_S_Y+1,_Windows_E_X-1,_Windows_E_Y-1,_Windows_Sub_Color);

	//标题栏
	GUI_Line(_Windows_S_X,_Title_E_Y,_Windows_E_X,_Title_E_Y,_Windows_Color);	
	
	//连接状态
	
	//连接类型
//	GUI_Line(_Connect_TYPE_E_X,_Title_E_Y,_Connect_TYPE_E_X,_Connect_TYPE_E_Y,_Windows_Color);
	
	GUI_Show12ASCII(_Text_X, _Title_E_Y+1,"Connect", FRONT_COLOR,  BLACK);
	
	GUI_Show12ASCII(_Text_X+60, _Title_E_Y+_Win_Height  ,"Type  :", FRONT_COLOR,  BLACK);
	GUI_Show12ASCII(_Text_X+60, _Title_E_Y+_Win_Height*2,"Statue:", FRONT_COLOR,  BLACK);	
	
	GUI_Show12ASCII(_Text_X+120, _Title_E_Y+_Win_Height  ,"None", FRONT_COLOR,  BLACK);
	GUI_Show12ASCII(_Text_X+120, _Title_E_Y+_Win_Height*2,"Unknow", FRONT_COLOR,  BLACK);	
	
	GUI_Line(_Windows_S_X,_Connect_E_Y,_Windows_E_X,_Connect_E_Y,_Windows_Color);
	
	GUI_Show12ASCII(_Text_X, _Connect_E_Y+1,"Data", FRONT_COLOR,  BLACK);
	
	GUI_Show12ASCII(_Text_X+60, _Connect_E_Y+_Win_Height  ,"Get   :", FRONT_COLOR,  BLACK);
	GUI_Show12ASCII(_Text_X+60, _Connect_E_Y+_Win_Height*2,"Save  :", FRONT_COLOR,  BLACK);	
	GUI_Show12ASCII(_Text_X+60, _Connect_E_Y+_Win_Height*3,"Send  :", FRONT_COLOR,  BLACK);	
	
	GUI_Show12ASCII(_Text_X+120, _Connect_E_Y+_Win_Height  ,"0", FRONT_COLOR,  BLACK);
	GUI_Show12ASCII(_Text_X+120, _Connect_E_Y+_Win_Height*2,"0", FRONT_COLOR,  BLACK);	
	GUI_Show12ASCII(_Text_X+120, _Connect_E_Y+_Win_Height*3,"0", FRONT_COLOR,  BLACK);	
	
	GUI_Line(_Windows_S_X,_Data_SS_E_Y ,_Windows_E_X,_Data_SS_E_Y,_Windows_Color);
	
	
	GUI_Show12ASCII(_Text_X, _Data_SS_E_Y+1,"Pin", FRONT_COLOR,  BLACK);
	
	GUI_Show12ASCII(_Text_X, _Data_SS_E_Y+_Win_Height  ,"VCC:",FRONT_COLOR,  BLACK);
	GUI_Show12ASCII(_Text_X, _Data_SS_E_Y+_Win_Height*2,"RST:", FRONT_COLOR,  BLACK);	
	GUI_Show12ASCII(_Text_X, _Data_SS_E_Y+_Win_Height*3,"GND:", FRONT_COLOR,  BLACK);	
	
	GUI_Show12ASCII(_Text_X+40, _Data_SS_E_Y+_Win_Height  ,"----mv",FRONT_COLOR,  BLACK);
	GUI_Show12ASCII(_Text_X+40, _Data_SS_E_Y+_Win_Height*2,"XXXXmv", FRONT_COLOR,  BLACK);	
	GUI_Show12ASCII(_Text_X+40, _Data_SS_E_Y+_Win_Height*3,"XXXXmv", FRONT_COLOR,  BLACK);	
	
	GUI_Show12ASCII(_Text_X+100, _Data_SS_E_Y+_Win_Height  ,"CLK:",FRONT_COLOR,  BLACK);
	GUI_Show12ASCII(_Text_X+100, _Data_SS_E_Y+_Win_Height*2,"I/O:", FRONT_COLOR,  BLACK);	
	GUI_Show12ASCII(_Text_X+100, _Data_SS_E_Y+_Win_Height*3,"VDD:", FRONT_COLOR,  BLACK);	
	
	GUI_Show12ASCII(_Text_X+140, _Data_SS_E_Y+_Win_Height  ,"----khz",FRONT_COLOR,  BLACK);
	GUI_Show12ASCII(_Text_X+140, _Data_SS_E_Y+_Win_Height*2,"XXXXmv", FRONT_COLOR,  BLACK);	
	GUI_Show12ASCII(_Text_X+140, _Data_SS_E_Y+_Win_Height*3,"XXXXmv", FRONT_COLOR,  BLACK);	

	GUI_Line(_Windows_S_X,_PIN_SS_E_Y ,_Windows_E_X,_PIN_SS_E_Y,_Windows_Color);

//	GUI_Show12ASCII(_Text_X, _Title_E_Y+1,"Connect Type", FRONT_COLOR,  BLACK);
	
	//GUI_Line(_Windows_S_X,_Title_E_Y+_Win_Height,_Windows_E_X,_Title_E_Y+_Win_Height,_Windows_Color);	
	
//	GUI_Show12ASCII(_Text_X, _Title_E_Y+_Row_Height+1,"Connect Statue", FRONT_COLOR,  BLACK);	

//	GUI_Line(_Windows_S_X,_Data_SS_E_Y,_Windows_E_X,_Data_SS_E_Y,_Windows_Color);	

	
	
	
	//GUI_Line(_Windows_S_X,_Windows_Outpu_S_Y,_Windows_E_X,_Windows_Outpu_S_Y,_Windows_Color);
	
}


void View_Connect_Information(u8 u8Type,u8 u8Statue)
{

	if(u8Type == 0)
		GUI_Show12ASCII(_Text_X+120, _Title_E_Y+_Win_Height,"None",FRONT_COLOR,  BLACK);
	else if(u8Type == 1)
	{
		GUI_Show12ASCII(_Text_X+120, _Title_E_Y+_Win_Height,"USB", FRONT_COLOR,  BLACK);
		if(u8Statue == 0)
	  	GUI_Show12ASCII(_Text_X+120, _Title_E_Y+_Win_Height*2,"None",FRONT_COLOR,  BLACK);
	  else if(u8Statue == 1)
	  	GUI_Show12ASCII(_Text_X+120, _Title_E_Y+_Win_Height*2,"Connect", FRONT_COLOR,  BLACK);
  	else if(u8Statue == 2)
	  	GUI_Show12ASCII(_Text_X+120, _Title_E_Y+_Win_Height*2,"Diconect", FRONT_COLOR,  BLACK);
	  else
	  	GUI_Show12ASCII(_Text_X+120, _Title_E_Y+_Win_Height*2,"Other", FRONT_COLOR,  BLACK);
	}
	else if(u8Type == 2)
	{
		GUI_Show12ASCII(_Text_X+120, _Title_E_Y+_Win_Height,"COM", FRONT_COLOR,  BLACK);
	  GUI_Show12ASCII(_Text_X+120, _Title_E_Y+_Win_Height+_Win_Height,"Unknow", FRONT_COLOR,  BLACK);	
	}
	else
		GUI_Show12ASCII(_Text_X+120, _Title_E_Y+_Win_Height,"Other", FRONT_COLOR,  BLACK);
}


u8 u32Digit2Ascii(u32 u32Digit, u8* u8Ascii)
{

	u8 u8temp[10];
	u32 TDigit = u32Digit;
	int i;

	for (i = 9; i >= 0; i--)
	{
		u8temp[i] = TDigit % 10 + 0x30;
		TDigit = TDigit / 10;
		if(TDigit == 0)
			break;
	}


	memcpy(u8Ascii, u8temp+i, 10-i);
	u8Ascii[10 - i] = '\0';
	


	return 10 - i;

}

void View_Data_Information(u32 u8Get,u32 u32Save,u32 u32Send)
{
	u8 u8temp[11];
	
	u32Digit2Ascii(u8Get,u8temp);
	GUI_Show12ASCII(_Text_X+120, _Connect_E_Y+_Win_Height  ,u8temp, FRONT_COLOR,  BLACK);

	u32Digit2Ascii(u32Save,u8temp);
	GUI_Show12ASCII(_Text_X+120, _Connect_E_Y+_Win_Height*2,u8temp, FRONT_COLOR,  BLACK);	
	
	u32Digit2Ascii(u32Save,u8temp);
	GUI_Show12ASCII(_Text_X+120, _Connect_E_Y+_Win_Height*3,u8temp, FRONT_COLOR,  BLACK);	
	
}

void View_Data_Get_Information(u32 u8Get)
{
	u8 u8temp[11];
	
	u32Digit2Ascii(u8Get,u8temp);
	GUI_Show12ASCII(_Text_X+120, _Connect_E_Y+_Win_Height  ,u8temp, FRONT_COLOR,  BLACK);

	
}

void View_Data_Save_Information(u32 u32Save)
{
	u8 u8temp[11];


	u32Digit2Ascii(u32Save,u8temp);
	GUI_Show12ASCII(_Text_X+120, _Connect_E_Y+_Win_Height*2,u8temp, FRONT_COLOR,  BLACK);	

	
}

void View_Data_Send_Information(u32 u32Send)
{
	u8 u8temp[11];

	u32Digit2Ascii(u32Send,u8temp);
	GUI_Show12ASCII(_Text_X+120, _Connect_E_Y+_Win_Height*3,u8temp, FRONT_COLOR,  BLACK);	
	
}

void LCD_Dislay_Init()
{
	//初始化设备
	TFTLCD_Init();
	
//	FRONT_COLOR = YELLOW;
	LCD_Clear(BLACK);
	FRONT_COLOR = RED;
	lCurY = _Output_Text_Y;
  lCurX = _Output_Text_X;
	
	View_Init();
	
	
	
}



void LCD_Dislay_Printf(u8 *p)
{

	GUI_Show12ASCII(_Output_Text_X, lCurY, p, FRONT_COLOR, BLACK);

	//GUI_Show12Char(10,lCurY,p,FRONT_COLOR, BLACK);

	lCurY += _Row_Height;

	if (lCurY >= 374)	
			lCurY = _Output_Text_Y;
	
}

int fputc(int ch,FILE *p)  //函数默认的，在使用printf函数时自动调用
{
	u8 Empty[30] = {0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,
	0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,
	0x20,0x20,0x20,0x20,0x20,0x20,0x20};

	if(lCurX == _Output_Text_X)
		 GUI_Show12ASCII(lCurX, lCurY,Empty,FRONT_COLOR, BLACK);

 
	
	if(ch == '\n')
	{
		lCurX  = _Output_Text_X;
		lCurY += _Row_Height;
		if (lCurY >= 374)	
			lCurY = _Output_Text_Y;
	}
	else
	{
		 GUI_Show12ASCII(lCurX, lCurY, (uint8_t*)&ch, FRONT_COLOR, BLACK);
		 lCurX += 8;
	}
	

	
  //   	USART_SendData(USART1,(u8)ch);	
	//while(USART_GetFlagStatus(USART1,USART_FLAG_TXE)==RESET);

	return ch;
}


#define _TEST
#ifdef _TEST

u8 SD_WriteDisk(u8*buf,u32 sector,u8 cnt)
{
	
	if (Status != SD_OK)
		return Status;
	
	if(cnt == 1)
	{
	
    Status = SD_WriteBlock(buf, sector* 512, BLOCK_SIZE);
    Status = SD_WaitWriteOperation();	   //??dma????
    while(SD_GetStatus() != SD_TRANSFER_OK); //??sdio?sd?????
		
		
		
		
		
	}
  else
	{
		
    Status = SD_WriteMultiBlocks(buf, sector* 512, BLOCK_SIZE, cnt);
    Status = SD_WaitWriteOperation();
    while(SD_GetStatus() != SD_TRANSFER_OK);
		
		


	}		
	return 0;
}



u8 SD_ReadDisk(u8*buf,u32 sector,u8 cnt)
{
 if (Status != SD_OK)
		return Status;

	
 printf("111");
	if(cnt == 1)
	{
    Status = SD_ReadBlock(buf, sector*512, BLOCK_SIZE);//????
    /* Check if the Transfer is finished */
    Status = SD_WaitReadOperation();
    while(SD_GetStatus() != SD_TRANSFER_OK);
  printf("222");
	}
	
	else
	{
    Status = SD_ReadMultiBlocks(buf, sector*512, BLOCK_SIZE, cnt);
    Status = SD_WaitReadOperation();
    while(SD_GetStatus() != SD_TRANSFER_OK);
		
	}
		
	Status = SD_OK;
	return Status;
	
}
#endif

/*

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

*/


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

	//初始化时钟
	SysTick_Init(72);

	//定义中断优先级
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);  //中断优先级分组分2组

//	USART1 115200
	//USART1_Init(115200);

	//显示屏
	LCD_Dislay_Init();

	//LCD_Dislay_Printf("LCD ok!");
	

	//初始化计时器
	Tim_Init();		
	LCD_Dislay_Printf("TIM ok!");

	//IO口使用外部中断 , CLK 外部中断 
	
	PINx_EXIT_Init();
  LCD_Dislay_Printf("Exit IO ok!");
	
	


//	if (SD_Init())
//	{
//		LCD_Dislay_Printf("SD Card Error!");
//	}
//	LCD_Dislay_Printf("SD Card OK!");
	
//	EN25QXX_Init();				//初始化EN25Qxx  
//	
//	if(EN25QXX_ReadID()!=EN25Q64)
//	{
//		LCD_Dislay_Printf("EN25QXX Error! ");	
//		printf("%x \n",EN25QXX_ReadID());
//	}
//	else
//		LCD_Dislay_Printf("FLASH OK! ");	
	
	
	//TEST SD
	Status = SD_Init();
//delay_ms(0x10000);
//	printf( "this is a microSD test\n " );
  if(Status == SD_OK)
	{    
		printf("SD_Init OK\n" );	


    Status = SD_ReadMultiBlocks(_SD_SaveBuf, 0x00, BLOCK_SIZE, 2);

    /* Check if the Transfer is finished */
    Status = SD_WaitReadOperation();  //????dma??????

    /* Wait until end of DMA transfer */
    while(SD_GetStatus() != SD_TRANSFER_OK);		
 }
  else
  {
	  	printf("SD_Init failed \n" );
    	printf("failed status is: %d\n",Status );
	}			  	
	    
	

	//delay_ms(10000);
 //	printf( "CardType is :%d \n", SDCardInfo.CardType );
//	printf( "CardCapacity is :%d \n", SDCardInfo.CardCapacity );
//	printf( "CardBlockSize is :%d \n", SDCardInfo.CardBlockSize );
//	printf( "RCA is :%d \n", SDCardInfo.RCA);
//	printf( "ManufacturerID is :%d \n", SDCardInfo.SD_cid.ManufacturerID );

	

	
	
//	while(1)
//	{
// 	printf( "CardType is :%d \n", SDCardInfo.CardType );
//	printf( "CardCapacity is :%d \n", SDCardInfo.CardCapacity );
//	printf( "CardBlockSize is :%d \n", SDCardInfo.CardBlockSize );
//	printf( "RCA is :%d \n", SDCardInfo.RCA);
//	printf( "ManufacturerID is :%d \n", SDCardInfo.SD_cid.ManufacturerID );

//	
//	printf("Erase Start!  \n" );
//	SD_EraseTest();	   //????  
//	printf("Erase finish!  \n" );
//	
//	
//	printf("Single Block Test Start!\n" );
//	SD_SingleBlockTest();  //??????
//	printf("Single Block Test Start!\n" );

// 	SD_MultiBlockTest();  //??????	
//	}
	
	
	
	
	
  FSMC_SRAM_Init();
	
	printf("Initialize Sram!\n"); 

	PINx_Level_Conversion_Init();
	printf("Level conversion ok!\n");
	
	
	delay_ms(100);
	USB_Port_Set(0); 	//USB先断开
	delay_ms(700);
	USB_Port_Set(1);	//USB再次连接
	USB_Interrupts_Config();
	Set_USBClock();
	USB_Init();

  View_Connect_Information(1,1);
	printf("USB Finish...\n");

}

void  Initialize_Global_variable(void)
{


 u32CLKLen  = 0;
 u32SendLen = 0;
 u32SaveLen = 0;

	



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

/*
u8 SaveChannelData_SD_USB_V2(void)
{
	
	u32 u32willSave = u32CLKLen - u32SaveLen;
	if(u32willSave>0x2000)
		u32willSave = 0x2000;
	
	FSMC_SRAM_ReadBuffer(_SD_SaveBuf, u32SaveLen, u32willSave);
	
	SD_Write(_SD_SaveBuf,u32SaveLen,u32willSave);
	
	u32SaveLen += u32willSave;
	
}


u8 SendChannelData_SD_USB_V2()
{
	
	u32 u32CurCount = u32SaveLen;
	
	u32 u32WillSend;

	u8 u8Ret = 0;
	if (GetEPTxStatus(ENDP1) != EP_TX_NAK)
		return 1;
	
	u32WillSend = u32CurCount - u32SendLen;
	
	if(u32WillSend > 64)
		u32WillSend = 64;
	
	 SD_Read(_USB_SendBuf ,u32SendLen,u32WillSend);
	 SendData_USB(ENDP1,_USB_SendBuf,u32WillSend );
	 u32SendLen = u32SendLen+ u32WillSend;
		return 0;
	
	
}


u8 SendChannelData_SD2_USB()
{
	u32 u32CurCount = u32SaveLen;
	
	u32 u32WillSend = u32SaveLen - u32SendLen;
	
	if(u32WillSend>64)
		u32WillSend = 64;
	
	//printf("SD_Read %d %d \n" ,u32SendLen,u32WillSend );
	SD_Read(_USB_SendBuf,u32SendLen,u32WillSend); 

	SendData_USB(ENDP1,_USB_SendBuf ,u32WillSend);
	
	u32SendLen = u32SendLen+ u32WillSend;
	
	return 0;
	
}

u8 SaveChannelData_SD2(void)
{
	
	u32 u32willSave = u32CLKLen - u32SaveLen;
	if(u32willSave>0x1000)
		u32willSave = 0x1000;
	
	FSMC_SRAM_ReadBuffer(_SD_SaveBuf, u32SaveLen, u32willSave);
	
	//printf("SD_WRITE %d %d" ,u32SaveLen,u32willSave );
	SD_Write(_SD_SaveBuf,u32SaveLen,u32willSave);
	
	u32SaveLen += u32willSave;
	
}


u8 SendChannelData_FLASH_USB()
{
	u32 u32CurCount = u32SaveLen;
	
	u32 u32WillSend = u32SaveLen - u32SendLen;
	
	if(u32WillSend>64)
		u32WillSend = 64;
	
	EN25QXX_Read(_USB_SendBuf,u32SendLen,u32WillSend); 

	SendData_USB(ENDP1,_USB_SendBuf ,u32WillSend);
	
	u32SendLen = u32SendLen+ u32WillSend;
	
	return 0;
	
}

u8 SaveChannelData_FLASH(void)
{
	
	u32 u32willSave = u32CLKLen - u32SaveLen;
	if(u32willSave>0x1000)
		u32willSave = 0x1000;
	
	FSMC_SRAM_ReadBuffer(_SD_SaveBuf, u32SaveLen, u32willSave);
	
	EN25QXX_Write(_SD_SaveBuf,u32SaveLen,u32willSave);
	
	u32SaveLen += u32willSave;
	
}

*/

u8 SendChannelData_SD_USB(u8 bMustRead)
{
//	u32 u32CurCount = u32SaveLen;
	
	u32 u32WillSend;
	
	u8 u8Ret = 0;
	if (GetEPTxStatus(ENDP1) != EP_TX_NAK)
		return 1;
	
		
	if(((u32SendLen%512) == 0)||
		  ((u32SendLen%64) != 0)||
	    (bMustRead == 1))
	   	SD_ReadDisk(_USB_SendBuf,u32SendLen/512 +_StartSector,1);


	u32WillSend =  512 - u32SendLen%512;
	
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
		__Count = 0x10;
	else
		__Count = u32willSave/512;
	
	u32willSave = __Count*512;

	FSMC_SRAM_ReadBuffer(_SD_SaveBuf, u32SaveLen, u32willSave);
	
	if (SD_WriteDisk(_SD_SaveBuf, (u32SaveLen / 512) +_StartSector, __Count)!=0) 
		SD_WriteDisk(_SD_SaveBuf, (u32SaveLen / 512) +_StartSector, __Count);

	u32SaveLen += u32willSave;
	
	return 0;
}


/*

void 	TEST__SD(void)
{
	u32 ii,kk,jj;
	u32 u32Ser = 0;
	printf("Start SD Test!\n");
	
	
	for(ii = 0 ; ii<0x400; ii++)
	{
		for(kk = 1 ; kk< 0x400; kk++)
		{
			//printf("SD Test -- :%x Number :%x \n", ii,kk);
			
			memset(_SD_SaveBuf,kk+ii%101,kk);
			
			SD_WriteDisk(_SD_SaveBuf,ii, kk);
			
			SD_ReadDisk(_SD_SaveBuf+0x500,ii,1);
			
			for(jj = 0 ; jj<kk; jj++)
	  	{
			  if(_SD_SaveBuf[jj]!= _SD_SaveBuf[jj+0x500])
		  	{
				  printf("SD ERR In Ser:%x Number :%x \n", ii,jj);
				  return;
			  } 
			
		  }
			
			printf("add start:%x Length :%xx\n", ii,kk);
			
		
		}
		
		
		
	}
	
	
	printf("Finish SD Test!\n");
	
	
	
	
}


void 	TEST__SD_V2(void)
{
	u32 ii,jj;
	u32 u32Ser = 0;
	printf("Start SD Test!\n");
	u8 temp;
	u8 Ret;

  for	(ii = 0 ; ii<0xFFFF; ii++)
	{

		memset(_SD_SaveBuf,ii%0xFF,512);
	
		printf("Write SD! %d\n",ii);
		SD_Write(_SD_SaveBuf,ii,512);
			printf("Read SD! %d\n",ii);
		SD_Read (_SD_SaveBuf+512,ii,512);
		
		for(jj = 0 ; jj<512; jj++)
		{
			if(_SD_SaveBuf[jj]!= _SD_SaveBuf[jj+512])
			{
				printf("SD ERR In Ser:%x Number :%x \n", ii,jj);
				return;
			}
			
		}
		printf("SD Test! %d\n",ii);
	}
	printf("Finish SD Test!\n");
}

*/

#define _Send_Busy 0x10
#define _Send_Success 1
#define _Send_Failed  0
#define _Send_NoData  2
u8 SendChannelData()
{
	if (GetEPTxStatus(ENDP1) != EP_TX_NAK)
		return _Send_Busy;
	
	
	if(u32SendLen <u32SaveLen)
	{
		SendChannelData_SD_USB(bSramRead);
		bSramRead = 0;
	}
//	}else 
//	if(u32SendLen <u32CLKLen)
//	{
//		SendChannelData_USB();
//		bSramRead = 1; 
//	}
	else 
		return _Send_NoData;
	
	return _Send_Success;
	
}





int main(void)
{
	

	u8 bSwitch = 1;

	

	u32 NewSend = 0;
	u32 NewSave = 0;
	u32 NewGet  = 0;
	
	//初始化各个模块
	Initialize_Module();
	

	Initialize_Global_variable();
	
	//此处需要先读取当前各个端口状态,VCC RST IO
	_Pre_Pin_Statue = GetPinValue();
	

	
	//SD_EraseTest();	   //????  

//	SD_SingleBlockTest();  //??????

 //	SD_MultiBlockTest();  //??????	


	Tim_Enable();			//同步开始计数

	
	printf("Start ...!\n"); 
	//TEST__SD();
 
	while(1)
	{	

	  
	//	View_Data_Get_Information(u32CLKLen);
		
		if(SendChannelData() != _Send_NoData)
		{
			if(NewSend!=u32SendLen)
			{
				View_Data_Send_Information(u32SendLen);
		    NewSend = u32SendLen;	

			}
		}
			
		if((u32CLKLen - u32SaveLen )>512)
		{
			SaveChannelData_SD();
			if(NewSave != u32SaveLen)
			{		
				NewSave = u32SaveLen;
				View_Data_Get_Information(u32CLKLen);
				View_Data_Save_Information(u32SaveLen);
			}
		}
		else if(NewGet != u32CLKLen)
		{
			
			NewGet = NewGet;
			View_Data_Get_Information(u32CLKLen);
	
		}

	
	
	
	}
}


/*
 * ???:SD_EraseTest
 * ??  :??????
 * ??  :?
 * ??  :?
 */
void SD_EraseTest(void)
{
  /*------------------- Block Erase ------------------------------------------*/
//  if (Status == SD_OK)
//  {
//    /* Erase NumberOfBlocks Blocks of WRITE_BL_LEN(512 Bytes) */
//    Status = SD_Erase(0x00, (BLOCK_SIZE * NUMBER_OF_BLOCKS));//????????????,????????????
//  }

//  if (Status == SD_OK)
//  {			  //?????????
//    Status = SD_ReadMultiBlocks(Buffer_MultiBlock_Rx, 0x00, BLOCK_SIZE, NUMBER_OF_BLOCKS);

//    /* Check if the Transfer is finished */
//    Status = SD_WaitReadOperation();  //????dma??????

//    /* Wait until end of DMA transfer */
//    while(SD_GetStatus() != SD_TRANSFER_OK);
//  }

//  /* Check the correctness of erased blocks */
//  if (Status == SD_OK)
//  {				  //??????????
//    EraseStatus = eBuffercmp(Buffer_MultiBlock_Rx, MULTI_BUFFER_SIZE);
//  }
//  
//  if(EraseStatus == PASSED)
//  	printf("\r\n erase OK! " );
// 
//  else	  
//  	printf("\r\n Erase failed! " );
  
}

/*
 * ???:SD_SingleBlockTest
 * ??  :	?????????
 * ??  :?
 * ??  :?
 */
void SD_SingleBlockTest(void)
{
  /*------------------- Block Read/Write --------------------------*/
  /* Fill the buffer to send */
  Fill_Buffer(Buffer_Block_Tx, BLOCK_SIZE, 0x320F);

  if (Status == SD_OK)
  {
    /* Write block of 512 bytes on address 0 */
    Status = SD_WriteBlock(Buffer_Block_Tx, 0x00, BLOCK_SIZE);
    /* Check if the Transfer is finished */
    Status = SD_WaitWriteOperation();	   //??dma????
    while(SD_GetStatus() != SD_TRANSFER_OK); //??sdio?sd?????
  }

  if (Status == SD_OK)
  {
    /* Read block of 512 bytes from address 0 */
    Status = SD_ReadBlock(Buffer_Block_Rx, 0x00, BLOCK_SIZE);//????
    /* Check if the Transfer is finished */
    Status = SD_WaitReadOperation();
    while(SD_GetStatus() != SD_TRANSFER_OK);
  }

  /* Check the correctness of written data */
  if (Status == SD_OK)
  {
    TransferStatus1 = Buffercmp(Buffer_Block_Tx, Buffer_Block_Rx, BLOCK_SIZE);	//??
  }
  
  if(TransferStatus1 == PASSED)
    printf("\r\n single OK!" );
 
  else  
  	printf("\r\n single failed! " );  
}

/*
 * ???:SD_MultiBlockTest
 * ??  :	????????
 * ??  :?
 * ??  :?
 */
void SD_MultiBlockTest(void)
{
  /*--------------- Multiple Block Read/Write ---------------------*/
  /* Fill the buffer to send */
  Fill_Buffer(Buffer_MultiBlock_Tx, MULTI_BUFFER_SIZE, 0x0);

  if (Status == SD_OK)
  {
    /* Write multiple block of many bytes on address 0 */
    Status = SD_WriteMultiBlocks(Buffer_MultiBlock_Tx, 0x00, BLOCK_SIZE, NUMBER_OF_BLOCKS);
    /* Check if the Transfer is finished */
    Status = SD_WaitWriteOperation();
    while(SD_GetStatus() != SD_TRANSFER_OK);
  }

  if (Status == SD_OK)
  {
    /* Read block of many bytes from address 0 */
    Status = SD_ReadMultiBlocks(Buffer_MultiBlock_Rx, 0x00, BLOCK_SIZE, NUMBER_OF_BLOCKS);
    /* Check if the Transfer is finished */
    Status = SD_WaitReadOperation();
    while(SD_GetStatus() != SD_TRANSFER_OK);
  }

  /* Check the correctness of written data */
  if (Status == SD_OK)
  {
    TransferStatus2 = Buffercmp(Buffer_MultiBlock_Tx, Buffer_MultiBlock_Rx, MULTI_BUFFER_SIZE);
  }
  
  if(TransferStatus2 == PASSED)	  
  	printf("\r\n multi Ok! " );

  else 
  	printf("\r\n multi failed! " );  

}




/*
 * ???:Buffercmp
 * ??  :???????????????
 * ??  :-pBuffer1, -pBuffer2 : ??????????
 *         -BufferLength ?????
 * ??  :-PASSED ??
 *         -FAILED ??
 */
TestStatus Buffercmp(uint8_t* pBuffer1, uint8_t* pBuffer2, uint32_t BufferLength)
{
  while (BufferLength--)
  {
    if (*pBuffer1 != *pBuffer2)
    {
      return FAILED;
    }

    pBuffer1++;
    pBuffer2++;
  }

  return PASSED;
}


/*
 * ???:Fill_Buffer
 * ??  :?????????
 * ??  :-pBuffer ???????
 *         -BufferLength ??????
 *         -Offset ??????????
 * ??  :? 
 */
void Fill_Buffer(uint8_t *pBuffer, uint32_t BufferLength, uint32_t Offset)
{
  uint16_t index = 0;

  /* Put in global buffer same values */
  for (index = 0; index < BufferLength; index++ )
  {
    pBuffer[index] = index + Offset;
  }
}


/*
 * ???:eBuffercmp
 * ??  :???????????0
 * ??  :-pBuffer ???????
 *         -BufferLength ?????        
 * ??  :PASSED ????????0
 *         FAILED ?????????????0 
 */
TestStatus eBuffercmp(uint8_t* pBuffer, uint32_t BufferLength)
{
  while (BufferLength--)
  {
    /* In some SD Cards the erased state is 0xFF, in others it's 0x00 */
    if ((*pBuffer != 0xFF) && (*pBuffer != 0x00))//????0xff?0x00
    {
      return FAILED;
    }

    pBuffer++;
  }

  return PASSED;
}
