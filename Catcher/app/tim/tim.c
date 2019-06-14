#include "tim.h"

u32 count = 0;
u32 frequency = 0;

//u8	bTimEnable;

//void time2_init(void)
//{					 
//	TIM_TimeBaseInitTypeDef    TIM_TimeBaseInitTypeStruct;		 
//
//	TIM_TimeBaseInitTypeStruct.TIM_Prescaler = 7199;  //tim2  72000000 10us
//	TIM_TimeBaseInitTypeStruct.TIM_CounterMode = TIM_CounterMode_Up;//增计数
//	TIM_TimeBaseInitTypeStruct.TIM_Period =	9999+1;		//10000  100ms					  
//	TIM_TimeBaseInitTypeStruct.TIM_ClockDivision = TIM_CKD_DIV1;
//	TIM_TimeBaseInit(TIM2,&TIM_TimeBaseInitTypeStruct);	 		   
//
//	TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE);	 //TIM2初始化	   
//	TIM_Cmd(TIM2,DISABLE);
//}
//
//void time3_init(void)
//{
//	TIM_TimeBaseInitTypeDef    TIM_TimeBaseInitTypeStruct;
//	//配置 TIMx 外部时钟模式 2
//	TIM_ETRClockMode2Config(TIM3,TIM_ExtTRGPSC_OFF,TIM_ExtTRGPolarity_NonInverted,0);
//	
//	TIM_TimeBaseInitTypeStruct.TIM_Prescaler = 0;
//	TIM_TimeBaseInitTypeStruct.TIM_CounterMode = TIM_CounterMode_Up;
//	TIM_TimeBaseInitTypeStruct.TIM_Period =	65535;							  
//	TIM_TimeBaseInitTypeStruct.TIM_ClockDivision = TIM_CKD_DIV1;
//	TIM_TimeBaseInit(TIM3,&TIM_TimeBaseInitTypeStruct);
//
//	TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE);
//	TIM_Cmd(TIM3,DISABLE);	  //失能
//
//}
//
//void time1_init(void)
//{					 //用来触发ad转换，TIM1触发ADC
//	TIM_TimeBaseInitTypeDef    TIM_TimeBaseInitTypeStruct;
//	TIM_OCInitTypeDef TIM_OCInitTypeStruct;		 
//
//	TIM_TimeBaseInitTypeStruct.TIM_Prescaler = 71; //72分频
//	TIM_TimeBaseInitTypeStruct.TIM_CounterMode = TIM_CounterMode_Up; //增计数
//	TIM_TimeBaseInitTypeStruct.TIM_Period =	1;	//自动重装值，1us触发一次						  
//	TIM_TimeBaseInitTypeStruct.TIM_ClockDivision = TIM_CKD_DIV1;//时钟不分频
//	TIM_TimeBaseInit(TIM1,&TIM_TimeBaseInitTypeStruct);	//TIM1初始化 		   	 	   
//	TIM_Cmd(TIM1,DISABLE);	 //TIM1不使能
//
//	TIM_OCInitTypeStruct.TIM_OCMode = TIM_OCMode_PWM1; 					   //这个也是必须配置成pwm模式 
//	TIM_OCInitTypeStruct.TIM_OutputState = TIM_OutputState_Enable; 
//	TIM_OCInitTypeStruct.TIM_Pulse = 1;
//	TIM_OCInitTypeStruct.TIM_OCPolarity = TIM_OCPolarity_High;
//	TIM_OC1Init(TIM1, &TIM_OCInitTypeStruct);
//
//	TIM_CtrlPWMOutputs(TIM1, ENABLE);				  //这个是必须有的
//}
////TIM2:PA0 TIM2 ETR
//void Tim2_Init()
//{
//	TIM_TimeBaseInitTypeDef    TIM_TimeBaseInitTypeStruct;
//	//配置 TIMx 外部时钟模式 2
//	TIM_ETRClockMode2Config(TIM2, TIM_ExtTRGPSC_OFF, TIM_ExtTRGPolarity_NonInverted, 0);
//
//	TIM_TimeBaseInitTypeStruct.TIM_Prescaler = 0;
//	TIM_TimeBaseInitTypeStruct.TIM_CounterMode = TIM_CounterMode_Down;
//	TIM_TimeBaseInitTypeStruct.TIM_Period = 0;
//	TIM_TimeBaseInitTypeStruct.TIM_ClockDivision = TIM_CKD_DIV1;
//	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseInitTypeStruct);
//
//	TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);
//	TIM_Cmd(TIM2, DISABLE);	  //失能
//
//}
//
////TIM3:PD2 TIM3 ETR
//void Tim3_Init()
//{
//	TIM_TimeBaseInitTypeDef    TIM_TimeBaseInitTypeStruct;
//	//配置 TIMx 外部时钟模式 2
//	TIM_ETRClockMode2Config(TIM3, TIM_ExtTRGPSC_OFF, TIM_ExtTRGPolarity_NonInverted, 0);
//
//	TIM_TimeBaseInitTypeStruct.TIM_Prescaler = 0;
//	TIM_TimeBaseInitTypeStruct.TIM_CounterMode = TIM_CounterMode_Up;
//	TIM_TimeBaseInitTypeStruct.TIM_Period = 65535;
//	TIM_TimeBaseInitTypeStruct.TIM_ClockDivision = TIM_CKD_DIV1;
//	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseInitTypeStruct);
//
//	TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE);
//	TIM_Cmd(TIM3, DISABLE);	  //失能
//
//
//}




//TIM2:PA0 TIM2 ETR
void Tim2_Init()
{
	TIM_TimeBaseInitTypeDef    TIM_TimeBaseInitTypeStruct;
	//配置 TIMx 外部时钟模式 2
	TIM_ETRClockMode2Config(TIM2, TIM_ExtTRGPSC_OFF, TIM_ExtTRGPolarity_NonInverted, 0);

	//TIM_TimeBaseInitTypeStruct.TIM_Prescaler = 0;
	//TIM_TimeBaseInitTypeStruct.TIM_CounterMode = TIM_CounterMode_Up;
	//TIM_TimeBaseInitTypeStruct.TIM_Period = 65535;
	//TIM_TimeBaseInitTypeStruct.TIM_ClockDivision = TIM_CKD_DIV1;


	TIM_TimeBaseInitTypeStruct.TIM_Prescaler = 0;
	TIM_TimeBaseInitTypeStruct.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInitTypeStruct.TIM_Period = 65535;
	TIM_TimeBaseInitTypeStruct.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseInitTypeStruct);

	TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);
	TIM_Cmd(TIM2, DISABLE);	  //失能

}
//TIM3:PD2 TIM3 ETR
void Tim3_Init()
{
	TIM_TimeBaseInitTypeDef    TIM_TimeBaseInitTypeStruct;
	//配置 TIMx 外部时钟模式 2
	TIM_ETRClockMode2Config(TIM3, TIM_ExtTRGPSC_OFF, TIM_ExtTRGPolarity_NonInverted, 0);

	//TIM_TimeBaseInitTypeStruct.TIM_Prescaler = 0;
	//TIM_TimeBaseInitTypeStruct.TIM_CounterMode = TIM_CounterMode_Up;
	//TIM_TimeBaseInitTypeStruct.TIM_Period = 65535;
	//TIM_TimeBaseInitTypeStruct.TIM_ClockDivision = TIM_CKD_DIV1;


	TIM_TimeBaseInitTypeStruct.TIM_Prescaler = 0;
	TIM_TimeBaseInitTypeStruct.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInitTypeStruct.TIM_Period = 65535;
	TIM_TimeBaseInitTypeStruct.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseInitTypeStruct);

	TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE);
	TIM_Cmd(TIM3, DISABLE);	  //失能


}

//TIM4：1S计时
void Tim4_Init()
{

	TIM_TimeBaseInitTypeDef    TIM_TimeBaseInitTypeStruct;

	TIM_TimeBaseInitTypeStruct.TIM_Prescaler = 7199;  //tim2  72000000 10us
	TIM_TimeBaseInitTypeStruct.TIM_CounterMode = TIM_CounterMode_Up;//增计数
	TIM_TimeBaseInitTypeStruct.TIM_Period = 9999 + 1;		//10000  100ms					  
	TIM_TimeBaseInitTypeStruct.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseInitTypeStruct);

	TIM_ITConfig(TIM4, TIM_IT_Update, ENABLE);
	TIM_Cmd(TIM4, DISABLE);


}


void Tim_Init(void)
{


	GPIO_InitTypeDef GPIO_InitTypeStruct;

	GPIO_InitTypeStruct.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitTypeStruct.GPIO_Speed = GPIO_Speed_50MHz;		 		//外部时钟的，用来测频率的，
	GPIO_InitTypeStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOA, &GPIO_InitTypeStruct);

	Tim2_Init();
	Tim4_Init();
}
void Tim_Enable(void)
{
	TIM_Cmd(TIM2, ENABLE);
	TIM_Cmd(TIM4, ENABLE);
//	TIM_Cmd(TIM3,ENABLE);	
//	TIM_Cmd(TIM4, ENABLE);
//	TIM_Cmd(TIM3, ENABLE);
	//Enable_TIM4(ENABLE);
}



//void Enable_TIM4(FunctionalState NewState)
//{
//	TIM_Cmd(TIM4, NewState);
//	bTimEnable = ((u8)NewState<<4) | bTimEnable;
//}


void IO_Init(void)
{
	EXTI_InitTypeDef   EXTI_InitTypeStruct;

	GPIO_InitTypeDef GPIO_InitTypeStruct;

	GPIO_InitTypeStruct.GPIO_Pin = GPIO_Pin_2;
	GPIO_InitTypeStruct.GPIO_Speed = GPIO_Speed_50MHz;		 		//IO 口下沿中断
	GPIO_InitTypeStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOE, &GPIO_InitTypeStruct);

	GPIO_InitTypeStruct.GPIO_Pin = GPIO_Pin_3;
	GPIO_InitTypeStruct.GPIO_Speed = GPIO_Speed_50MHz;		 		//IO 口下沿中断
	GPIO_InitTypeStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOE, &GPIO_InitTypeStruct);


	GPIO_EXTILineConfig(GPIO_PortSourceGPIOE, GPIO_PinSource2);	 
	EXTI_InitTypeStruct.EXTI_Line = EXTI_Line2;
	EXTI_InitTypeStruct.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitTypeStruct.EXTI_Trigger = EXTI_Trigger_Falling;
	EXTI_InitTypeStruct.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EXTI_InitTypeStruct);


	GPIO_EXTILineConfig(GPIO_PortSourceGPIOE, GPIO_PinSource3);
	EXTI_InitTypeStruct.EXTI_Line = EXTI_Line3;
	EXTI_InitTypeStruct.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitTypeStruct.EXTI_Trigger = EXTI_Trigger_Rising;
	EXTI_InitTypeStruct.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EXTI_InitTypeStruct);

}
