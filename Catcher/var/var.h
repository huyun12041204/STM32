

#ifndef _Var_H
#define _Var_H

#define _USE_USB

#include "System.h"

#define _StartSector 20

#define _Max_SD_Save 512*0x20



extern u16 TIM3CLK;
extern u16 TIM3Count;


extern u32 u32CLKLen;
extern u32 u32SendLen;
extern u32 u32SaveLen;


extern u8 _USB_SendBuf[512];
extern u8 _SD_SaveBuf[_Max_SD_Save];
extern u8 _Pre_Pin_Statue;
extern u8 _Cur_Pin_Statue;

extern u8 Sended ;



#endif
