#ifndef _tim_H
#define _tim_H
#include "system.h"
#include "SysTick.h"

extern u32 count;
extern u32 frequency;

//void time_init(void);
//void time_enable(void);
//
//void time1_init(void);

void Tim3_Init(void);
//void Tim4_Init();
void Tim_Init(void);
void Tim_Enable(void);
#endif
