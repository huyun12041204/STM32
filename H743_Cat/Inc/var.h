

#ifndef _VAR_H
#define _VAR_H

#define TIM5_CLK 1

#include "sys.h"
#include "stdio.h"	
#include "fatfs.h"
#include "sdmmc.h"


#define  _Max_CLK_Buff 0x3FFFF
#define  _Max_Bits_Buff 256


//�洢ʹ��
#define FileIsRead        0
#define SDNotExist        1
#define MountFaild        2
#define OpenFileFaild     3
#define WriteFileFaild    4
#define WriteDirFaild     5


extern u8 u8CLKBuff[_Max_CLK_Buff];
extern u32 u32CLKLen;

extern u32 u32ReadLen;
extern u32 u32SendLen;
extern u32 u32SaveLen;


extern u8 FileStatue;

extern FATFS fs;                 // Work area (file system object) for logical drive 
extern FIL fil;                  // file objects 
extern uint32_t Bytes; 


extern u8  _GetBitsOff;
extern u16 _GetBitsLen;
extern u8  _GetBitsBuf[_Max_Bits_Buff];

extern u8 iExtCLK;
extern u32 uInterHigh;


extern u16    ADC_DATA[100];

extern u32    VCCEvent;
extern u8     VCCSaved;


extern uint32_t TIMECNT;
 

#endif


