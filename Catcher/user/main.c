/* �������غ�D1ָʾ����˸��ʾ�����������У�����K_UP�л�Ƶ����ʾ���ƺ͵�ѹ���Ƶ��ڣ�
	K_DOWN��������K_RIGHT�����ӣ�AD����˿ڲ���PA2������ʹ������һ������STM32������
	�����������׵�һ�����巢�������ȥ���ԣ�����ͨ��PC1�ڷ��ͳ���ͨ������ֱ�����뵽ʾ����
	�������ϵ�PA2�ڼ��ɼ�⵽����Ĳ��Σ����ֻ��һ������STM32����������ѿ���ʹ���ź�
	�����������ź����뵽PA2�ڡ�����ֻ������һ���򵥵Ĳɼ�����ʾ���ڣ��ɼ��ľ��Ⱥ�׼ȷ��
	���ǱȽϸߵġ�*/

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

//��ֲUSBʱ���ͷ�ļ�
#include "mass_mal.h"
#include "usb_lib.h"
#include "hw_config.h"
#include "usb_pwr.h"
#include "memory.h"	    
#include "usb_bot.h"


#include "flash.h"
#include "ff.h" 
#include "fatfs_app.h"


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

	lCurY += 20;

	if (lCurY > 380)
	{
		lCurY = 10;
	}
	
	delay_ms(10);

}
#endif


int fputc(int ch,FILE *p)  //����Ĭ�ϵģ���ʹ��printf����ʱ�Զ�����
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




void USB_Port_Set(u8 enable)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);    //ʹ��PORTAʱ��		 
	if (enable)_SetCNTR(_GetCNTR()&(~(1 << 1)));//�˳��ϵ�ģʽ
	else
	{
		_SetCNTR(_GetCNTR() | (1 << 1));  // �ϵ�ģʽ
		GPIOA->CRH &= 0XFFF00FFF;
		GPIOA->CRH |= 0X00033000;
		PAout(12) = 0;
	}
}



void  Initialize_Module(void)
{


	//��ʼ��ʱ��
	SysTick_Init(72);

	//�����ж����ȼ�
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);  //�ж����ȼ������2��

	//USART1 115200
	USART1_Init(864000);

	//��ʾ��
	LCD_Dislay_Init();

	LCD_Dislay_Printf("Initialize LCD finished!");
	

	//��ʼ����ʱ��
	//Tim_Init();		
	LCD_Dislay_Printf("Initialize TIM finished!");

	//IO��ʹ���ⲿ�ж� , CLK �ⲿ�ж� 
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
}

void  Initialize_Global_variable(void)
{
	//����CLK������0

    uCLKCount     = 0 ;
    uSendCLKCOunt = 0 ;

#ifndef _2Channel
	memset(u8CLK, 0, sizeof(u8CLK));
#else
	memset(u8CLKT, 0, sizeof(u8CLKT));
	memset(uCount, 0, sizeof(uCount));
	u8Channel = 0;
#endif
	


	//CLK����
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
	//Ram�ڴ���δ�洢��SD�ڵ����ݣ���Ҫ�ȴ洢

	if (u16Save2SDTempLen != 0) 
	{
		u32SavedLen = _MaxSectorSize - u16Save2SDTempLen;

	    //����������ݺʹ洢���ݻ��ǲ���512 �����SDTemp
		if (uLen < u32SavedLen)
		{
			memcpy(SDTemp+ u16Save2SDTempLen, u8Data, uLen);
			u16Save2SDTempLen = u16Save2SDTempLen + uLen;
			return u8Ret;
		}
		//�����ȴ�һ������
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


	//���send ���� ���е� ˵���Ѿ��ع���
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


	//���send ���� ���е� ˵���Ѿ��ع���
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



//USBʹ������/����
//enable:0,�Ͽ�
//       1,��������	   


int main(void)
{
//	u8 SendEmpty = 0;

	//��ʼ������ģ��
	Initialize_Module();

	Initialize_Global_variable();
	
	DMA_Init_(DMA1_Channel4,(u32)&USART1->DR,(u32)u8UsartSendBuf,_MaxUsartSendSize);
	
	_SendBuf_Init();
	_Command_Init();
	
	//my_mem_init(SRAMIN);		//��ʼ���ڲ��ڴ��
	//SramOffset = 0;
	//�˴���Ҫ�ȶ�ȡ��ǰ�����˿�״̬,VCC RST IO
	_Pre_Pin_Statue = GetPinValue();





	

	delay_ms(1800);
	USB_Port_Set(0); 	//USB�ȶϿ�
	delay_ms(300);
	USB_Port_Set(1);	//USB�ٴ�����	   

	printf("USB Connecting...\n");//��ʾ���ڽ������� 	 
	
	//USB����
	USB_Interrupts_Config();
	Set_USBClock(); 
	USB_Init();
	printf("USB Finish...\n");//��ʾ���ڽ������� 	 
	delay_ms(1800);

	Tim_Enable();			//ͬ����ʼ����


	printf("Start ...!\n"); 
	while(1)
	{	
		if(uSendCLKCOunt != uCLKCount)
		{

			SaveChannelData();	
		}
		else if (DMA_GetFlagStatus(DMA1_FLAG_TC4) != 0)//�ж�ͨ��4�������
		{
			USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
			DMA_ClearFlag(DMA1_FLAG_TC4);
			
		}
				

	
	}
}


