#include "operation.h"
#include "var.h"

#include "usb_device.h"
/* USER CODE BEGIN Includes */
#include "usbd_conf.h"
#include "usbd_cdc.h"
#include "usbd_desc.h"
#include "usbd_ctlreq.h"

extern USBD_HandleTypeDef hUsbDeviceFS;

	void GetCLKNumber (u8 bReset)
	{
		
		DeltaCLKLow  = TIM4->CNT;
		DeltaCLKHigh = uCLKHigh;
		
		if(bReset)
		{
			TIM4->CNT = 0;
			uCLKHigh  = 0;
		}
		
		
	}
	
	void SetCLKBuff(u8 __buff,u32 __offset)
	{
		u8CLKBuff[__offset&0x3FFFF] = __buff;	
	}
	

	void SaveCLkNumber(u8 __Pin)
	{

	   u8 __ClkLen  = 0;

		
		 if(DeltaCLKHigh == 0)
		 { 
			  if(DeltaCLKLow<0x100)      __ClkLen =1;
			  else                       __ClkLen =2; 
		 }	
		 else if(DeltaCLKHigh<0x100 )  __ClkLen =3;
		 else if(DeltaCLKHigh<0x10000 )__ClkLen =4;
		 else                          __ClkLen =5;
		 
		 
		 
		 SetCLKBuff(__Pin|__ClkLen,u32CLKLen); 
		 SetCLKBuff(DeltaCLKLow&0xFF,u32CLKLen+1);
		 
		 if(__ClkLen > 1) SetCLKBuff(DeltaCLKLow>>8        ,u32CLKLen+2);
		 if(__ClkLen > 2) SetCLKBuff(DeltaCLKHigh&0xFF     ,u32CLKLen+3);
		 if(__ClkLen > 3) SetCLKBuff((DeltaCLKHigh>>8)&0xFF,u32CLKLen+4);	 
		 if(__ClkLen > 4) SetCLKBuff(DeltaCLKHigh>>16      ,u32CLKLen+5);	 	 
		 
		 u32CLKLen += (__ClkLen+1);
		 
		
	}
	
	
	
	u8   GetPinValue  (void)
	{   u8 __Pin = 0;
		
		 if( HAL_GPIO_ReadPin(GPIOE ,GPIO_PIN_9))__Pin |= Pin_IO;
		 if( HAL_GPIO_ReadPin(GPIOA ,GPIO_PIN_1))__Pin |= Pin_VCC;
		 if( HAL_GPIO_ReadPin(GPIOA ,GPIO_PIN_3))__Pin |= Pin_RST;
		
		return __Pin;		
	}
	
	
	void USB_Send(u8* __buff,u32 __Len)
	{

		  USBD_LL_Transmit(&hUsbDeviceFS,
                             CDC_IN_EP,
                             __buff,
                             __Len);
		 

		
	}
	
	
	void _CLKBuff_Send()
	{
		
		u32 __Len = u32CLKLen - u32SendLen;
		if(__Len >64) __Len = 64;
		
		USB_Send(u8CLKBuff+u32SendLen,__Len);
		
	  u32SendLen += __Len;
	}
	
	
	