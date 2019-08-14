#ifndef _OPERATION_H
#define _OPERATION_H
#include "sys.h"


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

	void GetCLKNumber (u8 bReset);
	void SaveCLkNumber(u8 __Pin);
	u8   GetPinValue  (void);
	
	void _CLKBuff_Send(void);

#endif
