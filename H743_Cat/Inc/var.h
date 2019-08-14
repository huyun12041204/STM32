

#ifndef _VAR_H
#define _VAR_H



#include "sys.h"
#include "stdio.h"	



#define _Max_CLK_Buff 1024*256

extern u8 u8CLKBuff[_Max_CLK_Buff];
extern u32 u32CLKLen;
extern u32 u32SendLen;


extern u16 DeltaCLKLow;
extern u32 DeltaCLKHigh;

extern u32 uCLKHigh ;

#endif
