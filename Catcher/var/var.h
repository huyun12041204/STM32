

#ifndef _Var_H
#define _Var_H

#define _USE_USB

#include "System.h"
#include "stm32_eval_sdio_sd.h"
#define _StartSector 1

#define _Max_SD_Save 0x2000

extern u16 TIM2CLK;
extern u16 TIM2Count;

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

extern u8 bSramRead;

extern SD_Error Status;

#endif
