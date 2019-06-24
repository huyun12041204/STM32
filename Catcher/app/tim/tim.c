#include "tim.h"

#ifdef _ORI

//u32 count = 0;
//u32 frequency = 0;

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


#else

//TIM2:PA0 TIM2 ETR
void Tim2_Init()
{
	TIM_TimeBaseInitTypeDef    TIM_TimeBaseInitTypeStruct;
	GPIO_InitTypeDef           GPIO_InitTypeStruct;
	NVIC_InitTypeDef           NVIC_InitTypeStruct;


	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);


	GPIO_InitTypeStruct.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitTypeStruct.GPIO_Speed = GPIO_Speed_50MHz;		 		//外部时钟的，用来测频率的，
	GPIO_InitTypeStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOA, &GPIO_InitTypeStruct);


	//配置 TIMx 外部时钟模式 2
	TIM_ETRClockMode2Config(TIM2, TIM_ExtTRGPSC_OFF, TIM_ExtTRGPolarity_NonInverted, 0);



	TIM_TimeBaseInitTypeStruct.TIM_Prescaler = 0;
	TIM_TimeBaseInitTypeStruct.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInitTypeStruct.TIM_Period = 65535;
	TIM_TimeBaseInitTypeStruct.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseInitTypeStruct);

	TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);
	TIM_Cmd(TIM2, DISABLE);	  //失能

	NVIC_InitTypeStruct.NVIC_IRQChannel = TIM2_IRQn;  		   //配置中断优先级
	NVIC_InitTypeStruct.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitTypeStruct.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitTypeStruct.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitTypeStruct);

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


void TIM8_Init()
{
	TIM_ICInitTypeDef TIM_ICInitStructure;
	TIM_TimeBaseInitTypeDef    TIM_TimeBaseInitStructure;
	//配置 TIMx 外部时钟模式 2
	TIM_ETRClockMode2Config(TIM8, TIM_ExtTRGPSC_OFF, TIM_ExtTRGPolarity_NonInverted, 0);



	TIM_TimeBaseInitStructure.TIM_Prescaler = 0;
	TIM_TimeBaseInitStructure.TIM_Period = 0xFFFF;
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM8, &TIM_TimeBaseInitStructure);


	TIM_ICInitStructure.TIM_Channel = TIM_Channel_1;
	TIM_ICInitStructure.TIM_ICFilter = 0x00;
	TIM_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;
	TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;
	TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI;
	TIM_ICInit(TIM8, &TIM_ICInitStructure);

	//TIM_ITConfig(TIM8, TIM_IT_Update|TIM_IT_CC1|TIM_IT_CC2, ENABLE);

	TIM_ITConfig(TIM8, TIM_IT_CC1 | TIM_IT_CC2, ENABLE);


	////	TIM_ICInitTypeDef  TIM_ICInitStructure;
	//	TIM_ICInitTypeDef TIM_ICInitStructure;
	//
	//
	//
	//	//TIM_ICInitStructure.TIM_ICMode
	//	TIM_DeInit(TIM8);
	//	//TIM_ICInitStructure.TIM_ICMode = TIM_ICMode_ICAP;                 //配置为输入捕获模式           
	//	TIM_ICInitStructure.TIM_Channel = TIM_Channel_1;                     //选择通道1 
	//	TIM_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;       //输入上升沿捕获   
	//	TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI;   // 通道方向选择    
	//	TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;               //每次检测到捕获输入就触发一次捕获 
	//	TIM_ICInitStructure.TIM_ICFilter = 0x4;                            // 
	//	TIM_ICInit(TIM8, &TIM_ICInitStructure);
	//
	//	//TIM_PWMIConfig(TIM8,)
	//
	//	TIM_PrescalerConfig(TIM8, 71, TIM_PSCReloadMode_Immediate);//72M/72=1M
	//
	//	 /* Select the TIM8 Input Trigger: TI2FP2 【输入触发源选择】*/
	//	TIM_SelectInputTrigger(TIM8, TIM_TS_TI2FP2);                      //参考TIM结构图选择滤波后的TI2输入    寄存器SMCR 
	//
	//   /* Select the slave Mode: Reset Mode */
	//	TIM_SelectSlaveMode(TIM8, TIM_SlaveMode_Reset);          //复位模式-选中的触发输入（TRGI）的上升沿初始化计数器，并且产生一个更新线号 
	//
	//	/* Enable the Master/Slave Mode */
	//	TIM_SelectMasterSlaveMode(TIM8, TIM_MasterSlaveMode_Enable);        //启动定时器的被动触发. 
	//
	//	TIM_ITConfig(TIM8, TIM_IT_CC1, ENABLE);        //打开中断 
	//
	//	TIM_Cmd(TIM8, ENABLE);                         //启动TIM8 
	//
	//	//Tim8_SetupNVIC();



}

void Tim_Init(void)
{
	Tim2_Init();

}
void Tim_Enable(void)
{
	TIM_Cmd(TIM2, ENABLE);
	//TIM_Cmd(TIM4, ENABLE);
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



#endif
