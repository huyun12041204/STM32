

#ifndef _VAR_H
#define _VAR_H



#include "sys.h"
#include "stdio.h"	
#include "fatfs.h"
#include "sdmmc.h"


#define _Max_CLK_Buff 0x3FFFF

//¥Ê¥¢ π”√
#define FileIsRead        0
#define SDNotExist        1
#define MountFaild        2
#define OpenFileFaild     3
#define WriteFileFaild    4
#define WriteDirFaild     5

extern u8 u8CLKBuff[_Max_CLK_Buff];
extern u32 u32CLKLen;
extern u32 u32SendLen;
extern u32 u32SaveLen;

extern u16 DeltaCLKLow;
extern u32 DeltaCLKHigh;

extern u32 uCLKHigh ;

extern u8 FileStatue;

extern FATFS fs;                 // Work area (file system object) for logical drive 
extern FIL fil;                  // file objects 
extern uint32_t Bytes; 


#endif
