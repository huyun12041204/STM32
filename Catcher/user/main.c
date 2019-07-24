/* �������غ�D1ָʾ����˸��ʾ�����������У�����K_UP�л�Ƶ����ʾ���ƺ͵�ѹ���Ƶ��ڣ�
	K_DOWN��������K_RIGHT�����ӣ�AD����˿ڲ���PA2������ʹ������һ������STM32������
	�����������׵�һ�����巢�������ȥ���ԣ�����ͨ��PC1�ڷ��ͳ���ͨ������ֱ�����뵽ʾ����
	�������ϵ�PA2�ڼ��ɼ�⵽����Ĳ��Σ����ֻ��һ������STM32����������ѿ���ʹ���ź�
	�����������ź����뵽PA2�ڡ�����ֻ������һ���򵥵Ĳɼ�����ʾ���ڣ��ɼ��ľ��Ⱥ�׼ȷ��
	���ǱȽϸߵġ�*/

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
#include "sd.h"
#include "SD_OP.h"

#include "var.h"


//��ֲUSBʱ���ͷ�ļ�
//#include "mass_mal.h"
#include "usb_lib.h"
#include "hw_config.h"
#include "usb_pwr.h"


#include "usbio.h"
extern volatile uint32_t EP1_ReceivedCount;
u8 SendIndex = 0;



u16 lCurY;
u16 lCurX;

void LCD_Dislay_Init()
{
	//��ʼ���豸
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

	//GUI_Show12Char(10,lCurY,p,FRONT_COLOR, BLACK);

	lCurY += 20;

	if (lCurY > 300)
	{
		lCurY = 10;
	}
	
	delay_ms(10);

}

int fputc(int ch,FILE *p)  //����Ĭ�ϵģ���ʹ��printf����ʱ�Զ�����
{
	u8 Empty[30] = {0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,
	0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,
	0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,};

	if(lCurX == 10)
		 GUI_Show12ASCII(lCurX, lCurY,Empty,FRONT_COLOR, BLACK);

 
	
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




//USBʹ������/����
//enable:0,�Ͽ�
//       1,��������	   
void USB_Port_Set(u8 enable)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);    //ʹ��PORTAʱ��		 
	if(enable)_SetCNTR(_GetCNTR()&(~(1<<1)));//�˳��ϵ�ģʽ
	else
	{	  
		_SetCNTR(_GetCNTR()|(1<<1));  // �ϵ�ģʽ
		GPIOA->CRH&=0XFFF00FFF;
		GPIOA->CRH|=0X00033000;
		PAout(12)=0;	    		  
	}
} 


void  Initialize_Module(void)
{

	//��ʼ��ʱ��
	SysTick_Init(72);

	//�����ж����ȼ�
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);  //�ж����ȼ������2��

	//USART1 115200
	//USART1_Init(864000);

	//��ʾ��
	LCD_Dislay_Init();

	LCD_Dislay_Printf("Initialize LCD finished!");
	

	//��ʼ����ʱ��
	Tim_Init();		
	LCD_Dislay_Printf("Initialize TIM finished!");

	//IO��ʹ���ⲿ�ж� , CLK �ⲿ�ж� 
	
	PINx_EXIT_Init();
  LCD_Dislay_Printf("Initialize Exit IO finished!");
	
	


	if (SD_Init())
	{
		LCD_Dislay_Printf("SD Card Error!");
	}
	LCD_Dislay_Printf("SD Card OK!");
	
	EN25QXX_Init();				//��ʼ��EN25Qxx  
	
	if(EN25QXX_ReadID()!=EN25Q64)
	{
		LCD_Dislay_Printf("EN25QXX Error!          ");	
		printf("%x \n",EN25QXX_ReadID());
	}
	else
		LCD_Dislay_Printf("FLASH OK!          ");	
	
  FSMC_SRAM_Init();
	
	printf("Initialize Sram!\n"); 

	PINx_Level_Conversion_Init();

	printf("Level conversion finish!\n");
	
	
	delay_ms(100);
	USB_Port_Set(0); 	//USB�ȶϿ�
	delay_ms(700);
	USB_Port_Set(1);	//USB�ٴ�����
	USB_Interrupts_Config();
	Set_USBClock();
	USB_Init();

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



u8 SendChannelData_SD_USB(u8 bMustRead)
{
	u32 u32CurCount = u32SaveLen;
	
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




int main(void)
{
	

	u8 bSwitch = 1;
	
	

	u32 NewSend = 0;
	//��ʼ������ģ��
	Initialize_Module();

	Initialize_Global_variable();
	
	//�˴���Ҫ�ȶ�ȡ��ǰ�����˿�״̬,VCC RST IO
	_Pre_Pin_Statue = GetPinValue();

	Tim_Enable();			//ͬ����ʼ����

	
	printf("Start ...!\n"); 
	//TEST__SD();
	u32SendLen = 0;
	u32CLKLen  = 0;
	u32SaveLen = 0;
 
	while(1)
	{	

	
		if((u32CLKLen - u32SaveLen )>512)
			 SaveChannelData_SD();
		

		if(u32SendLen != u32SaveLen)
		{
			if (GetEPTxStatus(ENDP1) != EP_TX_NAK)
				continue;
			
//			if((u32CLKLen-u32SendLen)>0x10000)
//			{
				//printf(".111");
	  	  SendChannelData_SD_USB(bSwitch);
			 
				bSwitch = 0;
//			}
//			else
//			{
//				bSwitch = 1;
//			  SendChannelData_USB();
//			}
			
	
		}
		else if(	NewSend != u32SendLen)
		{
				printf("Data:%x.Save:%x,Send:%x\n",u32CLKLen,u32SaveLen,u32SendLen);
		  	NewSend = u32SendLen;
		
		}
	
	
	
	
	}
}


