
/*
使用PC1，PC2 连接 VCC
    PC3, PC4 连接 RST
    以上为外部中断使用

		PC6 ，PC7 连接IO
		使用 TIM8 输入捕获

		PD2 连接CLK
		使用TIM3 记数

		PA2 连接IC VCC
		使用AD1, Channel2 测量电压


*/

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
//#include "flash.h"
#include "sd.h"
#include "SD_OP.h"

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

#define _PIN_SS_E_Y  (_Data_SS_E_Y+_Win_Height*4)

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

extern u16 ADCConvertedValue[30];//????ADC????,



void View_Init(void)
{

    LCD_DrawRectangleex( _Windows_S_X, _Windows_S_Y, _Windows_E_X, _Windows_E_Y,_Windows_Color );
    LCD_DrawRectangleex(_Windows_S_X+1,_Windows_S_Y+1,_Windows_E_X-1,_Windows_E_Y-1,_Windows_Sub_Color);

    //标题栏
    GUI_Line(_Windows_S_X,_Title_E_Y,_Windows_E_X,_Title_E_Y,_Windows_Color);

    //连接状态

    //连接类型
//	GUI_Line(_Connect_TYPE_E_X,_Title_E_Y,_Connect_TYPE_E_X,_Connect_TYPE_E_Y,_Windows_Color);

    GUI_Show12ASCII(_Text_X, _Title_E_Y+1,"Connect", FRONT_COLOR,  BLACK);

    GUI_Show12ASCII(_Text_X+60, _Title_E_Y+_Win_Height,"Type  :", FRONT_COLOR,  BLACK);
    GUI_Show12ASCII(_Text_X+60, _Title_E_Y+_Win_Height*2,"Statue:", FRONT_COLOR,  BLACK);

    GUI_Show12ASCII(_Text_X+120, _Title_E_Y+_Win_Height,"None", FRONT_COLOR,  BLACK);
    GUI_Show12ASCII(_Text_X+120, _Title_E_Y+_Win_Height*2,"Unknow", FRONT_COLOR,  BLACK);

    GUI_Line(_Windows_S_X,_Connect_E_Y,_Windows_E_X,_Connect_E_Y,_Windows_Color);

    GUI_Show12ASCII(_Text_X, _Connect_E_Y+1,"Data", FRONT_COLOR,  BLACK);

    GUI_Show12ASCII(_Text_X+60, _Connect_E_Y+_Win_Height,"Get   :", FRONT_COLOR,  BLACK);
    GUI_Show12ASCII(_Text_X+60, _Connect_E_Y+_Win_Height*2,"Save  :", FRONT_COLOR,  BLACK);
    GUI_Show12ASCII(_Text_X+60, _Connect_E_Y+_Win_Height*3,"Send  :", FRONT_COLOR,  BLACK);

    GUI_Show12ASCII(_Text_X+120, _Connect_E_Y+_Win_Height,"0", FRONT_COLOR,  BLACK);
    GUI_Show12ASCII(_Text_X+120, _Connect_E_Y+_Win_Height*2,"0", FRONT_COLOR,  BLACK);
    GUI_Show12ASCII(_Text_X+120, _Connect_E_Y+_Win_Height*3,"0", FRONT_COLOR,  BLACK);

    GUI_Line(_Windows_S_X,_Data_SS_E_Y,_Windows_E_X,_Data_SS_E_Y,_Windows_Color);

    GUI_Show12ASCII(_Text_X, _Data_SS_E_Y+1,"Pin", FRONT_COLOR,  BLACK);

    GUI_Show12ASCII(_Text_X, _Data_SS_E_Y+_Win_Height,"VCC:",FRONT_COLOR,  BLACK);
    GUI_Show12ASCII(_Text_X, _Data_SS_E_Y+_Win_Height*2,"RST:", FRONT_COLOR,  BLACK);
    GUI_Show12ASCII(_Text_X, _Data_SS_E_Y+_Win_Height*3,"GND:", FRONT_COLOR,  BLACK);

    GUI_Show12ASCII(_Text_X+40, _Data_SS_E_Y+_Win_Height,"----mv",FRONT_COLOR,  BLACK);
    GUI_Show12ASCII(_Text_X+40, _Data_SS_E_Y+_Win_Height*2,"XXXXmv", FRONT_COLOR,  BLACK);
    GUI_Show12ASCII(_Text_X+40, _Data_SS_E_Y+_Win_Height*3,"XXXXmv", FRONT_COLOR,  BLACK);

    GUI_Show12ASCII(_Text_X+100, _Data_SS_E_Y+_Win_Height,"CLK:",FRONT_COLOR,  BLACK);
    GUI_Show12ASCII(_Text_X+100, _Data_SS_E_Y+_Win_Height*2,"I/O:", FRONT_COLOR,  BLACK);
    GUI_Show12ASCII(_Text_X+100, _Data_SS_E_Y+_Win_Height*3,"VDD:", FRONT_COLOR,  BLACK);

    GUI_Show12ASCII(_Text_X+140, _Data_SS_E_Y+_Win_Height,"----khz",FRONT_COLOR,  BLACK);
    GUI_Show12ASCII(_Text_X+140, _Data_SS_E_Y+_Win_Height*2,"XXXXmv", FRONT_COLOR,  BLACK);
    GUI_Show12ASCII(_Text_X+140, _Data_SS_E_Y+_Win_Height*3,"XXXXmv", FRONT_COLOR,  BLACK);

    GUI_Line(_Windows_S_X,_PIN_SS_E_Y,_Windows_E_X,_PIN_SS_E_Y,_Windows_Color);


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
    GUI_Show12ASCII(_Text_X+120, _Connect_E_Y+_Win_Height,u8temp, FRONT_COLOR,  BLACK);

    u32Digit2Ascii(u32Save,u8temp);
    GUI_Show12ASCII(_Text_X+120, _Connect_E_Y+_Win_Height*2,u8temp, FRONT_COLOR,  BLACK);

    u32Digit2Ascii(u32Save,u8temp);
    GUI_Show12ASCII(_Text_X+120, _Connect_E_Y+_Win_Height*3,u8temp, FRONT_COLOR,  BLACK);

}

void View_Data_Get_Information(u32 u8Get)
{
    u8 u8temp[11];

    u32Digit2Ascii(u8Get,u8temp);
    GUI_Show12ASCII(_Text_X+120, _Connect_E_Y+_Win_Height,u8temp, FRONT_COLOR,  BLACK);


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







void View_Data_VCC(u16 u32Vcc)
{
    u8 u8temp[5];
    u32Digit2Ascii(u32Vcc,u8temp);
    GUI_Show12ASCII(_Text_X+40, _Data_SS_E_Y+_Win_Height,"    ",FRONT_COLOR,  BLACK);
    GUI_Show12ASCII(_Text_X+40, _Data_SS_E_Y+_Win_Height,u8temp,FRONT_COLOR,  BLACK);
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
                    0x20,0x20,0x20,0x20,0x20,0x20,0x20
                   };

    if(lCurX == _Output_Text_X)
        GUI_Show12ASCII(lCurX, lCurY,Empty,FRONT_COLOR, BLACK);



    if(ch == '\n')
    {
        lCurX  = _Output_Text_X;
        lCurY += _Row_Height;
        if (lCurY >= 374)
            lCurY = _Output_Text_Y;
				delay_ms(20);
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

    //USART1 115200
    //USART1_Init(864000);

    //显示屏
    LCD_Dislay_Init();

    LCD_Dislay_Printf("LCD ok!");


    //初始化计时器
    Collect_Init();
    LCD_Dislay_Printf("TIM ok!");

    //IO口使用外部中断 , CLK 外部中断
    PINx_EXIT_Init();
    LCD_Dislay_Printf("Exit IO ok!");





    if (SD_Init())
    {
        LCD_Dislay_Printf("SD Card Error!");
    }
    LCD_Dislay_Printf("SD Card OK!");

//	EN25QXX_Init();				//初始化EN25Qxx
//
//	if(EN25QXX_ReadID()!=EN25Q64)
//	{
//		LCD_Dislay_Printf("EN25QXX Error! ");
//		printf("%x \n",EN25QXX_ReadID());
//	}
//	else
//		LCD_Dislay_Printf("FLASH OK! ");

    FSMC_SRAM_Init();

    printf("Initialize Sram!\n");

//	PINx_Level_Conversion_Init();

//	printf("Level conversion ok!\n");


  //  DMA1_Init();
 //   Adc_Init();


    delay_ms(100);
    USB_Port_Set(0); 	//USB先断开
    delay_ms(700);
    USB_Port_Set(1);	//USB再次连接
    USB_Interrupts_Config();
    Set_USBClock();
    USB_Init();

    View_Connect_Information(1,1);
    printf("USB Finish...\n");
		
		Adc_Init(); 



}

void  Initialize_Global_variable(void)
{


    u32CLKLen  = 0;
    u32SendLen = 0;
    u32SaveLen = 0;

    preTIM3CLK     = 0;
    preTIM3Count   = 0;

    DeltaTIM3CLK   = 0;
    DeltaTIM3Count = 0;
	
	  u32Second = 0;

	  GPIO_ResetBits(GPIOA, GPIO_Pin_2);
	   
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

    FSMC_SRAM_ReadBuffer(_USB_SendBuf, u32SendLen,u32WillSend);

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

    u8Ret = SendData_USB(ENDP1,_USB_SendBuf +u32SendLen%512,u32WillSend );

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
    {
        SD_WriteDisk(_SD_SaveBuf, (u32SaveLen / 512) +_StartSector, __Count);
    }

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
    } else if(u32SendLen <u32CLKLen)
    {
        SendChannelData_USB();
        bSramRead = 1;
    }
    else
        return _Send_NoData;

    return _Send_Success;

}


int main(void)
{

    u8 ii;

    u32 NewSend = 0;
    u32 NewSave = 0;
    u32 NewGet  = 0;

    //初始化各个模块
    Initialize_Module();


    Initialize_Global_variable();

    //此处需要先读取当前各个端口状态,VCC RST IO
    //GetPinValue();
	// 

  
	 
    Collect_Enable();			//同步开始计数


    printf("Start ...!\n");
    Collect_Enable();
		
		DMA1_Init();

		
		TIM_CMD(TIM1,ENABLE);
		
		
		
	//	TIM_CMD(TIM1,ENABLE);

		
	//	View_Data_VCC(Get_Vcc_Value());
//	//	
//	memset(ADCConvertedValue,0,10);
//	 // Tim1_Init();
//  	Adc_Init(); 
//  	DMA1_Init();
//		
//		for(ii = 0; ii<30 ; ii++)
//		{
//					ADC_SoftwareStartConvCmd(ADC1, ENABLE);
//		delay_ms(10);
//		
//		}
		

 
   

	
    while(1)
    {
//   		if(DMA_GetFlagStatus(DMA1_FLAG_TE1))
//      {
//		     DMA_ClearFlag(DMA1_FLAG_TE1);
//				  View_Data_VCC(Get_Vcc_Value());
//		   //  ADC_Get_Value();
//	    }


        //	View_Data_Get_Information(u32CLKLen);
			
//			  if(!DMA_GetFlagStatus(DMA1_FLAG_TC2))
//			  {
//			    DMA1_Init();
//	        Adc_Init();
//	        ADC_SoftwareStartConvCmd(ADC1, ENABLE);
//					DMA_ClearFlag(DMA1_FLAG_TC2);
//				}

        if(SendChannelData() != _Send_NoData)
        {

            if(NewSend!=u32SendLen)
            {
                View_Data_Send_Information(u32SendLen);
                NewSend = u32SendLen;
                //	printf("%d ,%d ,%d\n",u32CLKLen,u32SaveLen,u32SendLen);
            }
        }

        if((u32CLKLen - u32SaveLen )>512)
        {
            SaveChannelData_SD();
            if(NewSave != u32SaveLen)
            {
                ADC_SoftwareStartConvCmd(ADC1, ENABLE);
                NewSave = u32SaveLen;
                View_Data_Get_Information(u32CLKLen);
                View_Data_Save_Information(u32SaveLen);
            }
        }
        else if(NewGet != u32CLKLen)
        {

            NewGet = NewGet;
            View_Data_Get_Information(u32CLKLen);
            //	printf("%d ,%d ,%d\n",u32CLKLen,u32SaveLen,u32SendLen);

        }



          //View_Data_VCC(Get_Vcc_Value());
        //	View_Data_VCC(Get_Vcc_Value());


    }
}


