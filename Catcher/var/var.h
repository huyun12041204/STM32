

#ifndef _Var_H
#define _Var_H

#define _USE_USB

#include "System.h"


//#define  _2Channel 
#define __2Sram

#define _StartSector 01

#define _MaxCLKCount 10000
#define _MaxCommandLen 0x15

#define _MaxSectorSize  512
#define _MaxUsartSendSize 600

#define  _MaxSram   0x3FFFFF

//当前CLKNumber
extern uint64_t u64CurCLK;
//之前CLKNumber
extern uint64_t u64PreCLK;

//TIM2 的计数器
extern uint32_t count;

extern uint32_t Tim5Count;


extern u32 u32CLKLen;
extern u32 u32SendLen;
extern u32 u32SaveLen;


extern u8 _USB_SendBuf[512];
extern u8 _SD_SaveBuf[0x2000];
extern u8 _Pre_Pin_Statue;
extern u8 _Cur_Pin_Statue;

extern u8 Sended ;

#endif
