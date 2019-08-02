#ifndef _tim_H
#define _tim_H
#include "system.h"
#include "SysTick.h"

extern u32 count;
extern u32 frequency;



void Tim3_Init(void);
//void Tim4_Init();
void Collect_Init(void);
void Collect_Enable(void);
void Collect_Disable(void);

#endif
