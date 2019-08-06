
#ifndef __STM32F10x_IT_H
#define __STM32F10x_IT_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"




#ifndef  Pin_ALL
#define  Pin_ALL 0xF8

#define  Pin_VCC 0x10
#define  Pin_RST 0x20
#define  Pin_IO  0x40
#define  Pin_CLK 0x80
//#define  Pin_GND 0x08

#define  _Time_ms 0x08


#endif







void SaveLimitStatue(u8 _Pin);
void SaveCurrentStatue(u8 _Pin);
void PINx_EXIT_Init(void);
u8   GetPinValue(void);


void GetClearTim3Count(void);
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
