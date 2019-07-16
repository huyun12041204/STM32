#ifndef _sram_H
#define _sram_H

#include "system.h"
//#include "delay.h"
#define Bank1_SRAM3_ADDR    ((u32)(0x68000000))	
void FSMC_SRAM_Init(void);
void FSMC_SRAM_WriteBuffer(u8* pBuffer,u32 WriteAddr,u32 NumHalfwordToWrite);
void FSMC_SRAM_ReadBuffer(u8* pBuffer,u32 ReadAddr,u32 NumHalfwordToRead);






#endif
