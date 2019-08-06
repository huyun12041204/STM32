#include "tim.h"
#include "var.h"
#include "STM32F10x_it.h"




void Tim1_Init(void)
{					 //用来触发ad转换，TIM1触发ADC
	TIM_TimeBaseInitTypeDef    TIM_TimeBaseInitTypeStruct;
	TIM_OCInitTypeDef TIM_OCInitTypeStruct;		 
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1,ENABLE);//使能TIM8时钟
 
	TIM_TimeBaseInitTypeStruct.TIM_Prescaler = 71; //72分频
	TIM_TimeBaseInitTypeStruct.TIM_CounterMode = TIM_CounterMode_Up; //增计数
	TIM_TimeBaseInitTypeStruct.TIM_Period =	1;	//自动重装值，1us触发一次						  
	TIM_TimeBaseInitTypeStruct.TIM_ClockDivision = TIM_CKD_DIV1;//时钟不分频
	TIM_TimeBaseInit(TIM1,&TIM_TimeBaseInitTypeStruct);	//TIM1初始化 		   	 	   
	TIM_Cmd(TIM1,DISABLE);	 //TIM1不使能

	TIM_OCInitTypeStruct.TIM_OCMode = TIM_OCMode_PWM1; 					   //这个也是必须配置成pwm模式 
	TIM_OCInitTypeStruct.TIM_OutputState = TIM_OutputState_Enable; 
	TIM_OCInitTypeStruct.TIM_Pulse = 1;
	TIM_OCInitTypeStruct.TIM_OCPolarity = TIM_OCPolarity_High;
	TIM_OC1Init(TIM1, &TIM_OCInitTypeStruct);

	TIM_CtrlPWMOutputs(TIM1, ENABLE);				  //这个是必须有的
	
	TIM_SetCounter(TIM1,0);	 
	TIM_PrescalerConfig(TIM1,71,TIM_PSCReloadMode_Immediate);
	TIM_SetCompare1(TIM1,   1);
	TIM_SetAutoreload(TIM1, 1); 
}



void Tim2_Init(void)
{				
  NVIC_InitTypeDef           NVIC_InitTypeStruct;	
	TIM_TimeBaseInitTypeDef    TIM_TimeBaseInitTypeStruct;		 
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
	TIM_TimeBaseInitTypeStruct.TIM_Prescaler = 7199;  //tim2  72000000 100us
	TIM_TimeBaseInitTypeStruct.TIM_CounterMode = TIM_CounterMode_Up;//Ôö¼ÆÊý
	TIM_TimeBaseInitTypeStruct.TIM_Period =	9999+1;		//10000  1000ms					  
	TIM_TimeBaseInitTypeStruct.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInit(TIM2,&TIM_TimeBaseInitTypeStruct);	 		   

	TIM_ITConfig(TIM2,TIM_IT_Update,DISABLE);	
	TIM_Cmd(TIM2,DISABLE);
	
	NVIC_InitTypeStruct.NVIC_IRQChannel = TIM2_IRQn;  		   //配置中断优先级
  NVIC_InitTypeStruct.NVIC_IRQChannelPreemptionPriority =1;
  NVIC_InitTypeStruct.NVIC_IRQChannelSubPriority = 1;
  NVIC_InitTypeStruct.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitTypeStruct);

}


void TIM2_IRQHandler(void)
{
	
	u32Second ++;
	
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
    TIM_TimeBaseInitTypeStruct.TIM_Period = 0xFFFF;
    TIM_TimeBaseInitTypeStruct.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseInit(TIM3, &TIM_TimeBaseInitTypeStruct);

    TIM_ITConfig(TIM3, TIM_IT_Update, DISABLE);
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
        TIM3Count += 1;

        if((TIM3Count - preTIM3Count) == 2)
            SaveLimitStatue(GetPinValue());

        //SaveLimitStatue(GetPinValue());
        //TIM3Count +=1;

    }

}






void TIM8_Init()
{
    TIM_ICInitTypeDef TIM_ICInitStructure;
//	TIM_TimeBaseInitTypeDef    TIM_TimeBaseInitStructure;
    GPIO_InitTypeDef  GPIO_InitStructure;
    NVIC_InitTypeDef  NVIC_InitTypeStruct;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM8,ENABLE);//使能TIM8时钟

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

    TIM_Cmd(TIM8, DISABLE); //使能定时器




}

void TIM8_CC_IRQHandler(void)
{

    GetClearTim3Count();



    if(TIM_GetITStatus(TIM8,TIM_IT_CC1)) //发生捕获中断
    {

        SaveCurrentStatue(GetPinValue());
        TIM_ClearITPendingBit(TIM8, TIM_IT_CC1);

    }
    else if (TIM_GetITStatus(TIM8, TIM_IT_CC3)) //发生捕获中断
    {

        SaveCurrentStatue(GetPinValue());
        TIM_ClearITPendingBit(TIM8, TIM_IT_CC3);
    }

// TIM_ClearITPendingBit(TIM8, TIM_IT_CC1|TIM_IT_CC3);
//	TEST2 = TIM3->CNT ;
//
//	printf("D--- %d \n",TEST2-0 );

}


//void TIM8_UP_IRQHandler(void)
//{
//
//}

void Collect_Init(void)
{
	  Tim1_Init();
	  Tim2_Init();	
    Tim3_Init();
    TIM8_Init();
}



void Collect_Enable(void)
{
	
	  TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);
    TIM_Cmd(TIM2, ENABLE);
	
    TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE);
    TIM_Cmd(TIM3, ENABLE);
	
    TIM_ITConfig(TIM8, TIM_IT_CC1|TIM_IT_CC3, ENABLE);
    TIM_Cmd(TIM8, ENABLE);


    //修改TIM3状态标示，
    TIMxStatue|= 0x04;

    //修改TIM8状态标示，
    TIMxStatue|= 0x80;

}


void Collect_Disable(void)
{
    TIM_ITConfig(TIM3, TIM_IT_Update, DISABLE);
    TIM_Cmd(TIM3, DISABLE);

    //清除TIM3的数据
    TIM3->CNT = 0;
    TIM3Count = 0;
    CurTIM3CLK     =0;
    CurTIM3Count   =0;
    preTIM3CLK     =0;
    preTIM3Count   =0;

    DeltaTIM3CLK   =0;
    DeltaTIM3Count =0;

    TIM_ITConfig(TIM8, TIM_IT_CC1|TIM_IT_CC3, DISABLE);
    TIM_Cmd(TIM8, DISABLE);


    //修改TIM3状态标示，
    TIMxStatue&= 0xFB;

    //修改TIM8状态标示，
    TIMxStatue&= 0x7F;

}



