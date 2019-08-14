#ifndef _TIM_H
#define _TIM_H
#include "sys.h"


extern TIM_HandleTypeDef htim1;
extern TIM_HandleTypeDef htim2;
extern TIM_HandleTypeDef htim4;

void MX_TIM1_Init(void);
void MX_TIM2_Init(void);
void MX_TIM4_Init(void);


#endif

