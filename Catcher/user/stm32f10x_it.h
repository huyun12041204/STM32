
#ifndef __STM32F10x_IT_H
#define __STM32F10x_IT_H

#ifdef __cplusplus
 extern "C" {
#endif 

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"

#ifndef EXIT_FALL
#define EXIT_FALL  0x0
#define EXIT_RAISE 0x8
#define EXIT_ALL   0xF
#endif


#ifndef CLK_EXITT_ALL 
#define CLK_EXITT_FALL  0x1
#define CLK_EXITT_RAISE  0x2
#define CLK_EXITT_ALL   0x3
#endif


#ifndef  Pin_ALL
#define  Pin_ALL 0xF8
#define  Pin_RST 0x10
#define  Pin_VCC 0x20
#define  Pin_IO  0x40 
#define  Pin_CLK 0x80 
//#define  Pin_GND 0x08 

#define  Pin_IO_Rising  0x8 
#define  Pin_IO_Falling  0xF7
#endif

#ifndef  Pin_ALL
#define  Pin_ALL 0x70
#define  Pin_VCC 0x10
#define  Pin_RES 0x20
#define  Pin_CLK 0x30
#define  Pin_IO  0x40 
#endif

#ifndef Bits_Number
#define Bits_Number 0x7
#define Bits_Len1   0x1
#define Bits_Len2   0x2
#define Bits_Len3   0x3
#define Bits_Len4   0x4
#define Bits_Len5   0x5
#define Bits_Len6   0x6
#define Bits_Len7   0x7
#endif 






	 uint64_t GetCLKNumber(void);
	 void SaveCurrentStatue(u8 _Pin);
	 void PINx_EXIT_Init(void);
	 u8   GetPinValue(void);
	 u32 Get_Tim3_Clock(void);


	 //************************************
	 // Method:    PINx_Level_Conversion_Init
	 // FullName:  PINx_Level_Conversion_Init
	 // Access:    public 
	 // Returns:   void
	 // Qualifier: 初始化电平转换模块
	 // Parameter: void
	 //************************************
	 void PINx_Level_Conversion_Init(void);
#ifdef __cplusplus
}
#endif

#endif /* __STM32F10x_IT_H */

/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
