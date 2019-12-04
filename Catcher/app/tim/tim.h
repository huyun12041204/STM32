#ifndef _tim_H
#define _tim_H
#include "system.h"
#include "SysTick.h"

extern u32 count;
extern u32 frequency;



void Tim3_Init(void);
//void Tim4_Init();
void Tim_Init(void);
void Tim_Enable(void);
//u8 GetTIM4_Statue();
void Enable_TIM4(FunctionalState NewState);

#endif
