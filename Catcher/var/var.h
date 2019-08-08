

#ifndef _Var_H
#define _Var_H

#define _USE_USB

#include "System.h"

#define _StartSector 20

#define _Max_SD_Save 0x2000


extern u8 TIMxStatue;



extern u32 PreTIM2CLK;
extern u32 CurTIM2CLK;

extern u32 TIM3Count;

extern u16 CurTIM3CLK;
extern u32 CurTIM3Count;

extern u16 preTIM3CLK;
extern u32 preTIM3Count;

extern u16 DeltaTIM3CLK;
extern u32 DeltaTIM3Count;

////用来计算频率
//extern u16 TIM5Count;
//extern u8  u8CC1; // 用来捕获接受中断此处
//extern u32 u321st;
//extern u32 u322nd;

extern u32 u32CLKLen;
extern u32 u32SendLen;
extern u32 u32SaveLen;


extern u8 _USB_SendBuf[512];
extern u8 _SD_SaveBuf[_Max_SD_Save];



extern u8 _Cur_Pin_Statue;


extern u8 bSramRead;


extern u32 u32Second;


extern u16 u16Vol;
extern u16 u16Fre;
extern u16 u16TFre[10];


extern u16 u16DisVol;
extern u16 u16DisFre;

extern u8 u8FreTime;

#endif
