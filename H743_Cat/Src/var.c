

#include "var.h"




u8 u8CLKBuff[_Max_CLK_Buff];
u32 u32CLKLen  = 0;
u32 u32ReadLen = 0;
u32 u32SendLen = 0;
u32 u32SaveLen = 0;


u8 FileStatue= SDNotExist;

FATFS fs;                 // Work area (file system object) for logical drive 
FIL fil;                  // file objects 
uint32_t Bytes; 

u8  _GetBitsOff = 0;
u16 _GetBitsLen = 0;
u8  _GetBitsBuf[_Max_Bits_Buff];

u8 iExtCLK      = 0;
u32 uInterHigh  = 0;

  
	
 u32    VCCEvent = 0;
 u8     VCCSaved = 0;
 
//获取时间的全局变量 
uint32_t TIMECNT = 0; 