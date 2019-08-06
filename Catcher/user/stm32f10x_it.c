#include "stm32f10x_it.h"
#include "gui.h"
#include "system.h"
#include "SysTick.h"
#include "tim.h"
//#include "button.h"
//#include "led.h"
#include "stdio.h"
#include "var.h"
#include "adc.h"
#include "sram.h"
#include "var.h"
#include "usb_int.h"
#include "usb_istr.h"







#define _MODE2 1


void GetTim2Second()
{
	
	
}

void GetClearTim3Count()
{


    CurTIM3CLK   = (TIM3->CNT);
    CurTIM3Count = TIM3Count;

    if(CurTIM3Count >= preTIM3Count)
        DeltaTIM3Count = CurTIM3Count - preTIM3Count;
    else
    {
        DeltaTIM3Count = 0;
        CurTIM3Count = preTIM3Count;
    }

    if(CurTIM3CLK < preTIM3CLK)
    {
        DeltaTIM3CLK = 0xFFFF - preTIM3CLK + CurTIM3CLK;
        if(DeltaTIM3Count > 0)
            DeltaTIM3Count -= 1 ;
        else
            CurTIM3Count +=1;
    }
    else
        DeltaTIM3CLK = CurTIM3CLK - preTIM3CLK;





    preTIM3CLK   = CurTIM3CLK;
    preTIM3Count = CurTIM3Count;

//	 DeltaTIM3CLK;
//   DeltaTIM3Count;
//	TIM3CLK   = (TIM3->CNT)+1;
//	TIM3->CNT    = 0;
//	TIM3Count    = 0;

}


void Excute_EXTI(u32 EXTI_Line, u8 u8Pin,u8 u8Mode)
{


    // dang TIM8 和TIm3 为DISABLE 则表示没有开始捕获
    if((TIMxStatue&0x84) == 0x84)
    {

        GetClearTim3Count();

        _Cur_Pin_Statue = GetPinValue();

        // 判断是升还是就降,此处主要消除电压抖动
        //if((_Cur_Pin_Statue&u8Pin) == (u8Pin&u8Mode))
        SaveCurrentStatue(_Cur_Pin_Statue);

    }
//    else if(u8Mode == Pin_VCC)
//    {
//        Collect_Enable();
//    }



    EXTI_ClearITPendingBit(EXTI_Line);
//	if ((_Cur_Pin_Statue&u8Pin) != (_Pre_Pin_Statue&u8Pin))
//	{
//		SaveCurrentStatue(_Cur_Pin_Statue);
//		_Pre_Pin_Statue = _Cur_Pin_Statue;
//	}
}


//VCC Raising
void EXTI1_IRQHandler(void)
{
   // printf("EX1\n");
    Excute_EXTI(EXTI_Line1, Pin_VCC,Pin_VCC);
	  NVIC_DisableIRQ(EXTI1_IRQn);
  	NVIC_EnableIRQ(EXTI2_IRQn);
	 

	// printf("EEE\n");
	 //View_Data_VCC(Get_Vcc_Value());

}

//VCC Falling
void EXTI2_IRQHandler(void)
{

    //printf("VCC Down!");
  
 

	if(GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_1) == 0)
	{
		Excute_EXTI(EXTI_Line2, Pin_VCC,0);
	//	Collect_Disable();
	  TIM3->CNT      = 0;
    TIM3Count      = 0;
    CurTIM3CLK     = 0;
    CurTIM3Count   = 0;
    preTIM3CLK     = 0;
    preTIM3Count   = 0;

    DeltaTIM3CLK   = 0;
    DeltaTIM3Count = 0;
  	NVIC_EnableIRQ(EXTI1_IRQn);
		NVIC_DisableIRQ(EXTI2_IRQn);
	}
	else
		 EXTI_ClearITPendingBit(EXTI_Line2);



}
//RESET Raising
void EXTI3_IRQHandler(void)
{


    Excute_EXTI(EXTI_Line3, Pin_RST,Pin_RST);
  	NVIC_DisableIRQ(EXTI3_IRQn);
	  NVIC_EnableIRQ(EXTI4_IRQn);
//	ADC_SoftwareStartConvCmd(ADC1, ENABLE);

}
//RESET FALING
void EXTI4_IRQHandler(void)
{
    Excute_EXTI(EXTI_Line4, Pin_RST,0);
	  NVIC_DisableIRQ(EXTI4_IRQn);
	  NVIC_EnableIRQ (EXTI3_IRQn);
}



void SaveLimitStatue(u8 _Pin)
{
    u32 u32TempLen = u32CLKLen;
    u8 __Temp[4] = {0x02,0xFF,0xFF,0x00};
//    u8 __ClkLen=0;



    u32CLKLen += 3;
    __Temp[0] = 	_Pin+ __Temp[0];
    FSMC_SRAM_WriteBuffer(__Temp,u32TempLen,3);


//

}

void SaveCurrentStatue(u8 _Pin)
{
    u8 __Temp[6];
    u8 __ClkLen = 0;

    __Temp[1] = 	DeltaTIM3CLK&0xFF;
    __Temp[2] = 	DeltaTIM3CLK>>8;
    __Temp[3] = 	DeltaTIM3Count&0xFF;
	  __Temp[4] = 	(DeltaTIM3Count>>8)&0xFF;
	  __Temp[5] = 	(DeltaTIM3Count>>16)&0xFF;

    if(DeltaTIM3Count > 0)
		{
      if( DeltaTIM3Count <0x100 )
				__ClkLen = 3;
			else if( DeltaTIM3Count < 0x10000 )
				__ClkLen = 4;
			else 
				__ClkLen = 3;
			
    }
		else if(__Temp[2]>0)
        __ClkLen = 2;
    else
        __ClkLen = 1;
    __Temp[0] = 	_Pin+ __ClkLen;


    __ClkLen+=1;

    FSMC_SRAM_WriteBuffer(__Temp,u32CLKLen,__ClkLen);

    u32CLKLen += 	__ClkLen;


}



void PINx_EXIT_Init(void)
{
    EXTI_InitTypeDef   EXTI_InitTypeStruct;
    NVIC_InitTypeDef   NVIC_InitTypeStruct;
    GPIO_InitTypeDef   GPIO_InitTypeStruct;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);

    NVIC_InitTypeStruct.NVIC_IRQChannel = EXTI1_IRQn;
    NVIC_InitTypeStruct.NVIC_IRQChannelPreemptionPriority = 2;
    NVIC_InitTypeStruct.NVIC_IRQChannelSubPriority = 0;
    NVIC_InitTypeStruct.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitTypeStruct);

    NVIC_InitTypeStruct.NVIC_IRQChannel = EXTI2_IRQn;
    NVIC_InitTypeStruct.NVIC_IRQChannelPreemptionPriority = 2;
    NVIC_InitTypeStruct.NVIC_IRQChannelSubPriority = 1;
    NVIC_InitTypeStruct.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitTypeStruct);

    NVIC_InitTypeStruct.NVIC_IRQChannel = EXTI3_IRQn;
    NVIC_InitTypeStruct.NVIC_IRQChannelPreemptionPriority = 2;
    NVIC_InitTypeStruct.NVIC_IRQChannelSubPriority = 2;
    NVIC_InitTypeStruct.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitTypeStruct);

    NVIC_InitTypeStruct.NVIC_IRQChannel = EXTI4_IRQn;
    NVIC_InitTypeStruct.NVIC_IRQChannelPreemptionPriority = 2;
    NVIC_InitTypeStruct.NVIC_IRQChannelSubPriority = 2;
    NVIC_InitTypeStruct.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitTypeStruct);

    GPIO_InitTypeStruct.GPIO_Pin = GPIO_Pin_1;
    GPIO_InitTypeStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitTypeStruct.GPIO_Mode = GPIO_Mode_IPD;
    GPIO_Init(GPIOC, &GPIO_InitTypeStruct);

    GPIO_InitTypeStruct.GPIO_Pin = GPIO_Pin_2;
    GPIO_InitTypeStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitTypeStruct.GPIO_Mode = GPIO_Mode_IPD;
    GPIO_Init(GPIOC, &GPIO_InitTypeStruct);

    GPIO_InitTypeStruct.GPIO_Pin = GPIO_Pin_3;
    GPIO_InitTypeStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitTypeStruct.GPIO_Mode = GPIO_Mode_IPD;
    GPIO_Init(GPIOC, &GPIO_InitTypeStruct);

    GPIO_InitTypeStruct.GPIO_Pin = GPIO_Pin_4;
    GPIO_InitTypeStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitTypeStruct.GPIO_Mode = GPIO_Mode_IPD;
    GPIO_Init(GPIOC, &GPIO_InitTypeStruct);


    GPIO_EXTILineConfig(GPIO_PortSourceGPIOC, GPIO_PinSource1);
    EXTI_InitTypeStruct.EXTI_Line = EXTI_Line1;
    EXTI_InitTypeStruct.EXTI_Mode = EXTI_Mode_Interrupt;
    EXTI_InitTypeStruct.EXTI_Trigger = EXTI_Trigger_Rising;
    EXTI_InitTypeStruct.EXTI_LineCmd = ENABLE;
    EXTI_Init(&EXTI_InitTypeStruct);

    GPIO_EXTILineConfig(GPIO_PortSourceGPIOC, GPIO_PinSource2);
    EXTI_InitTypeStruct.EXTI_Line = EXTI_Line2;
    EXTI_InitTypeStruct.EXTI_Mode = EXTI_Mode_Interrupt;
    EXTI_InitTypeStruct.EXTI_Trigger = EXTI_Trigger_Falling;
    EXTI_InitTypeStruct.EXTI_LineCmd = ENABLE;
    EXTI_Init(&EXTI_InitTypeStruct);


    GPIO_EXTILineConfig(GPIO_PortSourceGPIOC, GPIO_PinSource3);
    EXTI_InitTypeStruct.EXTI_Line = EXTI_Line3;
    EXTI_InitTypeStruct.EXTI_Mode = EXTI_Mode_Interrupt;
    EXTI_InitTypeStruct.EXTI_Trigger = EXTI_Trigger_Rising;
    EXTI_InitTypeStruct.EXTI_LineCmd = ENABLE;
    EXTI_Init(&EXTI_InitTypeStruct);

    GPIO_EXTILineConfig(GPIO_PortSourceGPIOC, GPIO_PinSource4);
    EXTI_InitTypeStruct.EXTI_Line = EXTI_Line4;
    EXTI_InitTypeStruct.EXTI_Mode = EXTI_Mode_Interrupt;
    EXTI_InitTypeStruct.EXTI_Trigger = EXTI_Trigger_Falling;
    EXTI_InitTypeStruct.EXTI_LineCmd = ENABLE;
    EXTI_Init(&EXTI_InitTypeStruct);




}


u8 GetPinValue(void)
{
    u8 u8Ret = 0;

    if (GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_2))
        u8Ret = u8Ret | Pin_VCC;
    if (GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_3))
        u8Ret = u8Ret | Pin_RST;
    if (GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_6))
        u8Ret = u8Ret | Pin_IO;
		if (GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_2))
        u8Ret = u8Ret | Pin_CLK;

    return u8Ret;
}

void PINx_Level_Conversion_Init(void)
{
//	GPIO_InitTypeDef   GPIO_InitTypeStruct;

//	//OE ,电平转换器使能管脚, 0 为使能, 1 为不使能
//	GPIO_InitTypeStruct.GPIO_Pin = GPIO_Pin_0;
//	GPIO_InitTypeStruct.GPIO_Speed = GPIO_Speed_2MHz;
//	GPIO_InitTypeStruct.GPIO_Mode = GPIO_Mode_Out_PP;
//	GPIO_Init(GPIOC, &GPIO_InitTypeStruct);

//	//DIR ,电平转换器方向管脚, 0 B->A, 1 A->B
//	GPIO_InitTypeStruct.GPIO_Pin = GPIO_Pin_1;
//	GPIO_InitTypeStruct.GPIO_Speed = GPIO_Speed_2MHz;
//	GPIO_InitTypeStruct.GPIO_Mode = GPIO_Mode_Out_PP;
//	GPIO_Init(GPIOC, &GPIO_InitTypeStruct);

//	GPIO_ResetBits(GPIOC, GPIO_Pin_0| GPIO_Pin_1);


}


void DMA1_Channel1_IRQHandler(void)
{

    printf("in DMA1 \n");
	 
    if(DMA_GetITStatus(DMA1_IT_TC1) != RESET)
    {
       View_Data_VCC(Get_Vcc_Value());
			 	TIM_Cmd(TIM1,DISABLE);
    }
		 DMA_ClearITPendingBit(DMA1_IT_TC1);

}



#ifdef _USE_USB


/**
  * @brief  This function handles NMI exception.
  * @param  None
  * @retval None
  */
void NMI_Handler(void)
{
}

/**
  * @brief  This function handles Hard Fault exception.
  * @param  None
  * @retval None
  */
//void HardFault_Handler(void)
//{
//  /* Go to infinite loop when Hard Fault exception occurs */
//  while (1)
//  {
//  }
//}

/**
  * @brief  This function handles Memory Manage exception.
  * @param  None
  * @retval None
  */
void MemManage_Handler(void)
{
    /* Go to infinite loop when Memory Manage exception occurs */
    while (1)
    {
    }
}

/**
  * @brief  This function handles Bus Fault exception.
  * @param  None
  * @retval None
  */
void BusFault_Handler(void)
{
    /* Go to infinite loop when Bus Fault exception occurs */
    while (1)
    {
    }
}

/**
  * @brief  This function handles Usage Fault exception.
  * @param  None
  * @retval None
  */
void UsageFault_Handler(void)
{
    /* Go to infinite loop when Usage Fault exception occurs */
    while (1)
    {
    }
}

/**
  * @brief  This function handles SVCall exception.
  * @param  None
  * @retval None
  */
void SVC_Handler(void)
{
}

/**
  * @brief  This function handles Debug Monitor exception.
  * @param  None
  * @retval None
  */
void DebugMon_Handler(void)
{
}

/**
  * @brief  This function handles PendSVC exception.
  * @param  None
  * @retval None
  */
void PendSV_Handler(void)
{
}

/**
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval None
  */
void SysTick_Handler(void)
{
}


/*******************************************************************************
* Function Name  : USB_HP_CAN_TX_IRQHandler
* Description    : This function handles USB High Priority or CAN TX interrupts
*                  requests.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void USB_HP_CAN1_TX_IRQHandler(void)
{
    CTR_HP();
}

/*******************************************************************************
* Function Name  : USB_LP_CAN_RX0_IRQHandler
* Description    : This function handles USB Low Priority or CAN RX0 interrupts
*                  requests.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void USB_LP_CAN1_RX0_IRQHandler(void)
{
    USB_Istr();
}

#endif
