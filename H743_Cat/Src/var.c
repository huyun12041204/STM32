

#include "var.h"




u8 u8CLKBuff[_Max_CLK_Buff];
u32 u32CLKLen  = 0;
u32 u32SendLen = 0;
u32 u32SaveLen = 0;

u16 DeltaCLKLow;
u32 DeltaCLKHigh;

u32 uCLKHigh = 0;

u8 FileStatue= SDNotExist;

FATFS fs;                 // Work area (file system object) for logical drive 
FIL fil;                  // file objects 
uint32_t Bytes; 

u8  _GetBitsOff = 0;
u16 _GetBitsLen = 0;
u8  _GetBitsBuf[_Max_Bits_Buff];

u8 iExtCLK      = 0;
u32 uInterHigh  = 0;


#if TIM5_CLK
u32 uPreCLk   = 0;
u32 uDeltaCLk = 0;

#endif
  

 u32    VCCEvent = 0;
 u8     VCCSaved = 0;
 
 //__attribute__((section(".ARM.__at_0x24000500")));
 

//uint32_t ADC_DATA[ADC_CONVERTED_DATA_BUFFER_SIZE] __attribute__((section(".ARM.__at_0x24000000")));