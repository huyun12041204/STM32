#include "tim.h"
#include "var.h"
#include "STM32F10x_it.h"


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
	GPIO_InitTypeDef           GPIO_InitTypeStruct;
	NVIC_InitTypeDef           NVIC_InitTypeStruct;




	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
	//配置 TIMx 外部时钟模式 2
	TIM_ETRClockMode2Config(TIM3, TIM_ExtTRGPSC_OFF, TIM_ExtTRGPolarity_NonInverted, 0);

	GPIO_InitTypeStruct.GPIO_Pin = GPIO_Pin_2;
	GPIO_InitTypeStruct.GPIO_Speed = GPIO_Speed_50MHz;		 		//外部时钟的，用来测频率的，
	GPIO_InitTypeStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOD, &GPIO_InitTypeStruct);

	TIM_TimeBaseInitTypeStruct.TIM_Prescaler = 0;
	TIM_TimeBaseInitTypeStruct.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInitTypeStruct.TIM_Period = 65535;
	TIM_TimeBaseInitTypeStruct.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseInitTypeStruct);

	TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE);
	TIM_Cmd(TIM3, DISABLE);	  //失能

	NVIC_InitTypeStruct.NVIC_IRQChannel = TIM3_IRQn;  		   //配置中断优先级
	NVIC_InitTypeStruct.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitTypeStruct.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitTypeStruct.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitTypeStruct);


}

void TIM3_IRQHandler(void)
{

	if (TIM_GetITStatus(TIM3, TIM_IT_Update))
	{
		TIM_ClearITPendingBit(TIM3, TIM_IT_Update);
		count++;

	}

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

void TIM5_Init()
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	TIM_ICInitTypeDef TIM_ICInitStructure;
	NVIC_InitTypeDef  NVIC_InitTypeStruct;
	GPIO_InitTypeDef  GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5,ENABLE);//使能TIM5时钟
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 		
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	TIM_TimeBaseInitStructure.TIM_Period= 0xFFFF;   //自动装载值
	TIM_TimeBaseInitStructure.TIM_Prescaler=71;  //分频系数
	TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1;
	TIM_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up; //设置向上计数模式
	TIM_TimeBaseInit(TIM5,&TIM_TimeBaseInitStructure);	
	
	TIM_ICInitStructure.TIM_Channel=TIM_Channel_1; //通道1
	TIM_ICInitStructure.TIM_ICFilter=0x02;  //滤波
	TIM_ICInitStructure.TIM_ICPolarity=TIM_ICPolarity_Rising;//捕获极性
	TIM_ICInitStructure.TIM_ICPrescaler=TIM_ICPSC_DIV1; //分频系数
	TIM_ICInitStructure.TIM_ICSelection=TIM_ICSelection_DirectTI;//直接映射到TI1
	TIM_ICInit(TIM5,&TIM_ICInitStructure);

	TIM_ICInitStructure.TIM_Channel = TIM_Channel_3; //通道3
	TIM_ICInitStructure.TIM_ICFilter = 0x02;  //滤波
	TIM_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Falling;//捕获极性
	TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1; //分频系数
	TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI;//直接映射到TI3
	TIM_ICInit(TIM5, &TIM_ICInitStructure);

	TIM_ITConfig(TIM5,TIM_IT_Update|TIM_IT_CC1| TIM_IT_CC3,DISABLE);
	
	
	NVIC_InitTypeStruct.NVIC_IRQChannel = TIM5_IRQn;  		   //配置中断优先级
	NVIC_InitTypeStruct.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitTypeStruct.NVIC_IRQChannelSubPriority = 1;
	NVIC_InitTypeStruct.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitTypeStruct);
	TIM_Cmd(TIM5, DISABLE); //使能定时器

}

void TIM5_IRQHandler(void)
{
	u64CurCLK = GetCLKNumber();
	if(TIM_GetITStatus(TIM5,TIM_IT_CC1)) //发生捕获中断
	{
		_Cur_Pin_Statue = GetPinValue()| Pin_IO_Rising;
		SaveCurrentStatue(_Cur_Pin_Statue);
		//if (((_Cur_Pin_Statue&Pin_IO) == Pin_IO) ||
		//  	((_Pre_Pin_Statue&Pin_IO)== 0))
		//{
		//		SaveCurrentStatue(_Cur_Pin_Statue);
  //		    TIM_ITConfig(TIM5, TIM_IT_CC1, DISABLE);
	 //   	TIM_ITConfig(TIM5, TIM_IT_CC3, ENABLE);	
		//}

	}
	if (TIM_GetITStatus(TIM5, TIM_IT_CC3)) //发生捕获中断
	{

		_Cur_Pin_Statue = GetPinValue();
		_Cur_Pin_Statue = _Cur_Pin_Statue & Pin_IO_Falling;
		SaveCurrentStatue(_Cur_Pin_Statue);
		//if (((_Cur_Pin_Statue&Pin_IO) == 0) ||
		//  	((_Pre_Pin_Statue&Pin_IO)== Pin_IO))
		//{
		//		SaveCurrentStatue(_Cur_Pin_Statue);
  //		  TIM_ITConfig(TIM5, TIM_IT_CC3, DISABLE);
	 //   	TIM_ITConfig(TIM5, TIM_IT_CC1, ENABLE);	
		//}
	}
	_Pre_Pin_Statue = _Cur_Pin_Statue;
	TIM_ClearITPendingBit(TIM5, TIM_IT_Update|TIM_IT_CC1|TIM_IT_CC3);
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

	//TIM_ITConfig(TIM8, TIM_IT_Update|TIM_IT_CC1|TIM_IT_CC3, ENABLE);

	TIM_ITConfig(TIM8, TIM_IT_CC1 | TIM_IT_CC3, ENABLE);


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
	Tim3_Init();
	TIM5_Init();
}
void Tim_Enable(void)
{
	TIM_Cmd(TIM3, ENABLE);
	TIM_ITConfig(TIM5, TIM_IT_CC1|TIM_IT_CC3, ENABLE);
	TIM_Cmd(TIM5, ENABLE);
}


void Clear_Tim5_Time(void)
{
	
	TIM_ITConfig(TIM5, TIM_IT_Update, DISABLE);
	TIM_SetCounter(TIM5,0);
	Tim5Count = 0;
	TIM_ITConfig(TIM5, TIM_IT_Update, ENABLE);
	
}
//u8Uint =   0 :us
//           1 :ms
//           2 :s
u32 Get_Tim5_Time(u8 u8Uint)
{
	u8 ii;
	u32 u32time = Tim5Count*0x10000 + TIM_GetCounter(TIM5);;
	
	for(ii = 0 ; ii< u8Uint ; ii++)
		u32time = u32time/1000;
	
	return u32time;
}


u32 Get_Tim3_Clock()
{
	u32 Clock;
	//TIM_ITConfig(TIM3, TIM_IT_Update, DISABLE);

	Clock = TIM_GetCounter(TIM3) + count * 0x100000;
	TIM_SetCounter(TIM3, 0);
	count = 0;
	//TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE);

	return Clock;
}





