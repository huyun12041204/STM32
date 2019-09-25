#ifndef _OPERATION_H
#define _OPERATION_H

//#define __Test_FATFS

#include "sys.h"
#include "var.h"
#include "lcd.h"


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


#define _MAX_Buffer_Send   64
	void GetCLKNumber (u8 bReset);
	void SaveCLkNumber(u8 __Pin );
	void SaveEmptyCLK(void);
	u8   GetPinValue  (void);
	void _CLKBuff_Send(void);
	void PrintfSDInformation(void);
    u8 SDIsReadForSave(void);


#ifdef __Test_FATFS


  void Test_FATFS1(void);
	void Test_FATFS(void);

#endif

#endif
