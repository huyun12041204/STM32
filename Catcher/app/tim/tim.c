#include "tim.h"
#include "var.h"
#include "STM32F10x_it.h"


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
	TIM_TimeBaseInitTypeStruct.TIM_Period = 0xFFFF;
	TIM_TimeBaseInitTypeStruct.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseInitTypeStruct);

	TIM_ITConfig(TIM3, TIM_IT_Update, DISABLE);
	TIM_Cmd(TIM3, DISABLE);	  //失能

	NVIC_InitTypeStruct.NVIC_IRQChannel = TIM3_IRQn;  		   //配置中断优先级
	NVIC_InitTypeStruct.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitTypeStruct.NVIC_IRQChannelSubPriority = 1;
	NVIC_InitTypeStruct.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitTypeStruct);


}

void TIM3_IRQHandler(void)
{

	if (TIM_GetITStatus(TIM3, TIM_IT_Update))
	{
		TIM_ClearITPendingBit(TIM3, TIM_IT_Update);
		SaveLimitStatue(GetPinValue());
		//TIM3Count +=1;

	}

}






void TIM8_Init()
{
	TIM_ICInitTypeDef TIM_ICInitStructure;
//	TIM_TimeBaseInitTypeDef    TIM_TimeBaseInitStructure;
	GPIO_InitTypeDef  GPIO_InitStructure;
	NVIC_InitTypeDef  NVIC_InitTypeStruct;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM8,ENABLE);//使能TIM5时钟

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 		
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;
	GPIO_Init(GPIOC, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_Init(GPIOC, &GPIO_InitStructure);

	TIM_DeInit(TIM8);

	//TIM_ICInitStructure.TIM_ICMode = TIM_ICMode_ICAP;    
	TIM_ICInitStructure.TIM_Channel = TIM_Channel_1;
	TIM_ICInitStructure.TIM_ICFilter = 0x01;
	TIM_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;
	TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;
	TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI;
	TIM_ICInit(TIM8, &TIM_ICInitStructure);
	
	TIM_ICInitStructure.TIM_Channel = TIM_Channel_3;
	TIM_ICInitStructure.TIM_ICFilter = 0x01;
	TIM_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Falling;
	TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;
	TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI;
	TIM_ICInit(TIM8, &TIM_ICInitStructure);

	TIM_ITConfig(TIM8, TIM_IT_CC1 | TIM_IT_CC3, DISABLE);
	
	
	NVIC_InitTypeStruct.NVIC_IRQChannel = TIM8_CC_IRQn;  		   //配置中断优先级
	NVIC_InitTypeStruct.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitTypeStruct.NVIC_IRQChannelSubPriority = 1;
	NVIC_InitTypeStruct.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitTypeStruct);
	
	TIM_Cmd(TIM5, DISABLE); //使能定时器




}

void TIM8_CC_IRQHandler(void)
{

	GetClearTim3Count();


	if(TIM_GetITStatus(TIM8,TIM_IT_CC1)) //发生捕获中断
	{

		SaveCurrentStatue(GetPinValue());
		TIM_ClearITPendingBit(TIM8, TIM_IT_CC1);

	}
	else// if (TIM_GetITStatus(TIM8, TIM_IT_CC3)) //发生捕获中断
	{

		SaveCurrentStatue(GetPinValue());
		TIM_ClearITPendingBit(TIM8, TIM_IT_CC3);
	}

 
//	TEST2 = TIM3->CNT ;
	
	//printf("D--- %d \n",TEST2-0 );
	
}


void Tim_Init(void)
{
	Tim3_Init();
	TIM8_Init();
}
void Tim_Enable(void)
{
	TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE);
	TIM_Cmd(TIM3, ENABLE);
	TIM_ITConfig(TIM8, TIM_IT_CC1|TIM_IT_CC3, ENABLE);
	TIM_Cmd(TIM8, ENABLE);
}






