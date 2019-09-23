#include "operation.h"


#include "usb_device.h"
#include "usbd_cdc_if.h"
extern USBD_HandleTypeDef hUsbDeviceHS;
extern SD_HandleTypeDef hsd1;


	void GetCLKNumber (u8 bReset)
	{
		
		DeltaCLKLow  = TIM4->CNT;
		DeltaCLKHigh = uCLKHigh;
		
		if(bReset)
		{
			//此处是1的原因是 尝试很多次,发现初始化过程基本都差1
			//由于初始化过程需要时间,此处使用400MHZ 所以此处设置为1 可能不需要1 
			TIM4->CNT = 1;
			uCLKHigh  = 0;
		}
		
		
	}
	
	void SetCLKBuff(u8 __buff,u32 __offset)
	{
		u8CLKBuff[__offset&_Max_CLK_Buff] = __buff;	
	}
	u8 GetCLKBuff(u32 __offset)
	{
		return  u8CLKBuff[__offset&_Max_CLK_Buff];	
	}



	//************************************
	// Method:    __GetDeltaCLKBufferLen
	// FullName:  获取当前DeltaCLK 需要占用的BUFFER 长度
	// Access:    public 
	// Returns:   u8
	// Qualifier:
	// Parameter: u32 _DeltaH
	// Parameter: u16 _DeltaL
	//************************************
	u8 __GetDeltaCLKBufferLen(u32 _DeltaH,u16 _DeltaL)
	{

		u8 __ClkLen  = 0;

		if(_DeltaH == 0)
		{ 
			if(_DeltaL<0x100)      __ClkLen =1;
			else                   __ClkLen =2; 
		}	
		else if(_DeltaH<0x100 )  __ClkLen =3;
		else if(_DeltaH<0x10000 )__ClkLen =4;
		else                     __ClkLen =5;
		return __ClkLen;

	}
	


	void SaveCLkNumber(u8 __Pin)
	{
	  //   u8 __ClkLen  = 0;

		 //if(DeltaCLKHigh == 0)
		 //{ 
			//  if(DeltaCLKLow<0x100)      __ClkLen =1;
			//  else                       __ClkLen =2; 
		 //}	
		 //else if(DeltaCLKHigh<0x100 )  __ClkLen =3;
		 //else if(DeltaCLKHigh<0x10000 )__ClkLen =4;
		 //else                          __ClkLen =5;
		u32 __CurOffset;
		u8  __ClkLen   = __GetDeltaCLKBufferLen(DeltaCLKHigh,DeltaCLKLow);
		
		
		__CurOffset    = u32CLKLen;

		//此处需要预先流出 但前计算出的长度,避免 不同中断里面的冲突
		u32CLKLen     += (__ClkLen+1);	 
		
		//保存当前各个PIN 的状态,和后续CLK buffer 长度
		SetCLKBuff(__Pin|__ClkLen,__CurOffset); 

		//保存当前第一位最低位长度;
		SetCLKBuff(DeltaCLKLow&0xFF,__CurOffset+1);
  
		if(__ClkLen > 1) SetCLKBuff(DeltaCLKLow>>8        ,__CurOffset+2); 
		else return;
		if(__ClkLen > 2) SetCLKBuff(DeltaCLKHigh&0xFF     ,__CurOffset+3);
		else return;
		if(__ClkLen > 3) SetCLKBuff((DeltaCLKHigh>>8)&0xFF,__CurOffset+4);	 
		else return;
		if(__ClkLen > 4) SetCLKBuff(DeltaCLKHigh>>16      ,__CurOffset+5);	
		else return;
		 	 
			
	}



	
	void SaveEmptyCLK(void)
	{
		u8  __Pin       = GetPinValue();
		u32 __CurOffset = u32CLKLen;	
		u32CLKLen += 3;	
		SetCLKBuff(__Pin|02,__CurOffset);
		SetCLKBuff(0xFF,__CurOffset+1);
		SetCLKBuff(0xFF,__CurOffset+2);

	}
	
	
	
	u8   GetPinValue  (void)
	{   u8 __Pin = 0;
		
		
		 if((GPIOE->IDR & GPIO_PIN_9) != 0x00)__Pin |= Pin_IO ;
		 if((GPIOA->IDR & GPIO_PIN_15) != 0x00)__Pin|= Pin_VCC;
		 if((GPIOB->IDR & GPIO_PIN_4) != 0x00)__Pin |= Pin_RST;
		
		return __Pin;		
	}
	

	
	void _CLKBuff_Send()
	{
	
		u8 i;
		u8 TempBufer[_MAX_Buffer_Send];


		u32 __Len = u32CLKLen - u32SendLen;
		if(__Len >_MAX_Buffer_Send) __Len = _MAX_Buffer_Send;

		for (i = 0 ; i< __Len ; i++)
			TempBufer[i] = GetCLKBuff(u32SendLen + i);

		//此处内部会判断USB是否发送完成.如果没有返回 USBD_BUSY
		if (CDC_Transmit_HS(TempBufer, __Len) == USBD_OK) u32SendLen += __Len;

	
		 
	}
	
	void PrintfSDInformation()
	{
//		switch(hsd1.SdCard.CardType)
//		{
//		case STD_CAPACITY_SD_CARD_V1_1:printf("Card Type:SDSC V1.1\r\n");break;
//		case STD_CAPACITY_SD_CARD_V2_0:printf("Card Type:SDSC V2.0\r\n");break;
//		case HIGH_CAPACITY_SD_CARD:printf("Card Type:SDHC V2.0\r\n");break;
//		case MULTIMEDIA_CARD:printf("Card Type:MMC Card\r\n");break;
//		}
		
		if(hsd1.State !=  0)
		{
			uint64_t uSize = hsd1.SdCard.LogBlockNbr*hsd1.SdCard.LogBlockSize;
			uSize          = uSize / (1024*1024);
			printf("SD Size : %d MB\n " ,(u32)uSize);
		}
			

		
	
		
	}
	
