#include "stm32f10x_it.h"
#include "gui.h"
#include "system.h"
#include "SysTick.h"
#include "tim.h"
//#include "button.h"
//#include "led.h"
#include "stdio.h" 
#include "var.h"

#include "sram.h"
#include "var.h"



				




#define _MODE2 1







uint64_t GetCLKNumber(void)
{
	
	uint64_t temp = ((uint64_t)count*0x10000 + (uint64_t)TIM_GetCounter(TIM3));
	if(temp< u64PreCLK)
		temp = temp+0x10000;
	return  temp;
}




void Excute_EXTI(u32 EXTI_Line, u8 u8Pin)
{

	u64CurCLK = GetCLKNumber();
	EXTI_ClearITPendingBit(EXTI_Line);
	_Cur_Pin_Statue = GetPinValue();


	//printf("EXTI %X,Cur:%X,Pre%X\n", EXTI_Line, _Cur_Pin_Statue, _Pre_Pin_Statue);
	if ((_Cur_Pin_Statue&u8Pin) != (_Pre_Pin_Statue&u8Pin))
	{
		SaveCurrentStatue(_Cur_Pin_Statue);
		_Pre_Pin_Statue = _Cur_Pin_Statue;
	}
}

//RESET
void EXTI2_IRQHandler(void)
{

	Excute_EXTI(EXTI_Line2, Pin_RST);
}
//VCC
void EXTI3_IRQHandler(void)
{
	Excute_EXTI(EXTI_Line3, Pin_VCC);
}
//IO
void EXTI4_IRQHandler(void)
{
	Excute_EXTI(EXTI_Line4, Pin_IO);
}

void SaveCurrentStatue(u8 _Pin)
{
	uint64_t u64CLKDiff;
	u8 __ClkLen,__Temp;
	u8 ii;

	u64CLKDiff = u64CurCLK - u64PreCLK;

	if (u64CLKDiff < 0xFF)
		__ClkLen = Bits_Len1;
	else if (u64CLKDiff < 0xFFFFFF)
		__ClkLen = Bits_Len2;
	else if (u64CLKDiff < 0xFFFFFFFFFF)
		__ClkLen = Bits_Len3;
	else 
	{
		printf("ERROR in Save %lld\n",u64CLKDiff);
		printf("CurCLK %lld\n",u64CurCLK);
		printf("PreCLK %lld\n",u64PreCLK);	
	}
	__Temp = _Pin + __ClkLen;
	FSMC_SRAM_WriteBuf(&__Temp, u32CLKLen, 1);
	u32CLKLen += 1;

	for (ii = (__ClkLen * 2 - 1); ii > 0; ii -= 1)
	{
		__Temp = ((u64CLKDiff >> ((ii - 1) * 8)) & 0xFF);		
		FSMC_SRAM_WriteBuf(&__Temp, u32CLKLen, 1);
		u32CLKLen += 1;
		if(u32CLKLen== _MaxSram)
			u32CLKLen = 0;
	}
	u64PreCLK = u64CurCLK;

}

void PINx_EXIT_Init(void)
{
	EXTI_InitTypeDef   EXTI_InitTypeStruct;
	NVIC_InitTypeDef   NVIC_InitTypeStruct;
	GPIO_InitTypeDef   GPIO_InitTypeStruct;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE, ENABLE);

	NVIC_InitTypeStruct.NVIC_IRQChannel = EXTI2_IRQn;
	NVIC_InitTypeStruct.NVIC_IRQChannelPreemptionPriority = 2;
	NVIC_InitTypeStruct.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitTypeStruct.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitTypeStruct);

	NVIC_InitTypeStruct.NVIC_IRQChannel = EXTI3_IRQn;
	NVIC_InitTypeStruct.NVIC_IRQChannelPreemptionPriority = 2;
	NVIC_InitTypeStruct.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitTypeStruct.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitTypeStruct);

	NVIC_InitTypeStruct.NVIC_IRQChannel = EXTI4_IRQn;
	NVIC_InitTypeStruct.NVIC_IRQChannelPreemptionPriority = 2;
	NVIC_InitTypeStruct.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitTypeStruct.NVIC_IRQChannelCmd = DISABLE;
	NVIC_Init(&NVIC_InitTypeStruct);

	GPIO_InitTypeStruct.GPIO_Pin = GPIO_Pin_2;
	GPIO_InitTypeStruct.GPIO_Speed = GPIO_Speed_50MHz;		 		//IO 口下沿中断
	GPIO_InitTypeStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOE, &GPIO_InitTypeStruct);

	GPIO_InitTypeStruct.GPIO_Pin = GPIO_Pin_3;
	GPIO_InitTypeStruct.GPIO_Speed = GPIO_Speed_50MHz;		 		//IO 口下沿中断
	GPIO_InitTypeStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOE, &GPIO_InitTypeStruct);

	GPIO_InitTypeStruct.GPIO_Pin = GPIO_Pin_4;
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

	GPIO_EXTILineConfig(GPIO_PortSourceGPIOE, GPIO_PinSource4);
	EXTI_InitTypeStruct.EXTI_Line = EXTI_Line4;
	EXTI_InitTypeStruct.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitTypeStruct.EXTI_Trigger = EXTI_Trigger_Rising_Falling;
	EXTI_InitTypeStruct.EXTI_LineCmd = DISABLE;
	EXTI_Init(&EXTI_InitTypeStruct);




}

u8 GetPinValue(void)
{
	u8 u8Ret = 0;

	if (GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_2))
		u8Ret = u8Ret | Pin_RST;
	if (GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_3))
		u8Ret = u8Ret | Pin_VCC;
	if (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0))
		u8Ret = u8Ret | Pin_IO;

	return u8Ret;
}

void PINx_Level_Conversion_Init(void)
{
	GPIO_InitTypeDef   GPIO_InitTypeStruct;

	//OE ,电平转换器使能管脚, 0 为使能, 1 为不使能
	GPIO_InitTypeStruct.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitTypeStruct.GPIO_Speed = GPIO_Speed_2MHz;		 	
	GPIO_InitTypeStruct.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOC, &GPIO_InitTypeStruct);

	//DIR ,电平转换器方向管脚, 0 B->A, 1 A->B
	GPIO_InitTypeStruct.GPIO_Pin = GPIO_Pin_1;
	GPIO_InitTypeStruct.GPIO_Speed = GPIO_Speed_2MHz;		
	GPIO_InitTypeStruct.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOC, &GPIO_InitTypeStruct);

	GPIO_ResetBits(GPIOC, GPIO_Pin_0| GPIO_Pin_1);


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
