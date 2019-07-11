

#ifndef _Var_H
#define _Var_H

#define _USE_USB

#include "System.h"


//#define  _2Channel 
#define __2Sram

#define _MaxCLKCount 10000
#define _MaxCommandLen 0x15

#define _MaxSectorSize  512
#define _MaxUsartSendSize 600

//��ǰCLKNumber
extern uint64_t u64CurCLK;
//֮ǰCLKNumber
extern uint64_t u64PreCLK;

//TIM2 �ļ�����
extern uint32_t count;



extern u32 u32CLKLen;
extern u32 u32SendLen;



extern u8 _USB_SendBuf[64];


extern u8 _Pre_Pin_Statue;
extern u8 _Cur_Pin_Statue;

extern u8 Sended ;

#endif
