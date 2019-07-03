#include "stm32f10x_it.h"
#include "gui.h"
#include "system.h"
#include "SysTick.h"
#include "tim.h"
#include "button.h"
#include "led.h"
#include "stdio.h" 
#include "var.h"

#include "sram.h"



				




#define _MODE2 1






#ifdef _ORI

//u8 frequency_flag = 0;
//long int shao_miao_shu_du = 0;
//u8 num_shao_miao = 8;
//u8 mode = 0;
//u8 num_fu_du =7;
//u8 ad_flag = 1;
//float gao_pin_palus = 0;
//u16 vcc_div = 0;
//u16 vpp;


 //void set_io0(void)					  										
//{
//	GPIO_ResetBits(GPIOA,GPIO_Pin_3);	
//	GPIO_ResetBits(GPIOA,GPIO_Pin_4);
//	GPIO_ResetBits(GPIOA,GPIO_Pin_5);
//	GPIO_ResetBits(GPIOA,GPIO_Pin_6);
//	GPIO_ResetBits(GPIOA,GPIO_Pin_7);
//	
//
//}
//
//void set_io1(void)					  										
//{
//	GPIO_SetBits(GPIOA,GPIO_Pin_3);
//	GPIO_SetBits(GPIOA,GPIO_Pin_7);	
//
//	GPIO_ResetBits(GPIOA,GPIO_Pin_4);
//	GPIO_ResetBits(GPIOA,GPIO_Pin_5);
//	GPIO_ResetBits(GPIOA,GPIO_Pin_6);     
//}
//
//void set_io2(void)					  										
//{
//	GPIO_SetBits(GPIOA,GPIO_Pin_3);
//	GPIO_SetBits(GPIOA,GPIO_Pin_7);	
//
//	GPIO_ResetBits(GPIOA,GPIO_Pin_4);
//	GPIO_ResetBits(GPIOA,GPIO_Pin_5);
//	GPIO_SetBits(GPIOA,GPIO_Pin_6);     
//}
//
//void set_io3(void)					  										
//{
//	GPIO_SetBits(GPIOA,GPIO_Pin_3);
//	GPIO_SetBits(GPIOA,GPIO_Pin_7);	
//
//	GPIO_ResetBits(GPIOA,GPIO_Pin_4);
//	GPIO_SetBits(GPIOA,GPIO_Pin_5);			   //  GPIO_SetBits
//	GPIO_ResetBits(GPIOA,GPIO_Pin_6);     	   //GPIO_ResetBits
//}
//
//void set_io4(void)					  										
//{
//	GPIO_SetBits(GPIOA,GPIO_Pin_3);
//	GPIO_SetBits(GPIOA,GPIO_Pin_7);	
//
//	GPIO_ResetBits(GPIOA,GPIO_Pin_4);
//	GPIO_SetBits(GPIOA,GPIO_Pin_5);			   //  GPIO_SetBits
//	GPIO_SetBits(GPIOA,GPIO_Pin_6);     	   //GPIO_ResetBits
//}
//
//void set_io5(void)					  										
//{
//	GPIO_SetBits(GPIOA,GPIO_Pin_3);
//	GPIO_SetBits(GPIOA,GPIO_Pin_7);	
//
//	GPIO_SetBits(GPIOA,GPIO_Pin_4);
//	GPIO_ResetBits(GPIOA,GPIO_Pin_5);			   //  GPIO_SetBits
//	GPIO_SetBits(GPIOA,GPIO_Pin_6);     	   //GPIO_ResetBits
//}
//
//void set_io6(void)					  										
//{
//	GPIO_SetBits(GPIOA,GPIO_Pin_3);
//	GPIO_SetBits(GPIOA,GPIO_Pin_7);	
//
//	GPIO_SetBits(GPIOA,GPIO_Pin_4);
//	GPIO_SetBits(GPIOA,GPIO_Pin_5);			   //  GPIO_SetBits
//	GPIO_ResetBits(GPIOA,GPIO_Pin_6);     	   //GPIO_ResetBits
//}
//
//void set_io7(void)					  										
//{
//	GPIO_SetBits(GPIOA,GPIO_Pin_3);
//	GPIO_SetBits(GPIOA,GPIO_Pin_7);	
//
//	GPIO_SetBits(GPIOA,GPIO_Pin_4);
//	GPIO_SetBits(GPIOA,GPIO_Pin_5);			   //  GPIO_SetBits
//	GPIO_SetBits(GPIOA,GPIO_Pin_6);     	   //GPIO_ResetBits
//}
//
//void set_io8(void)					  										
//{
//	GPIO_ResetBits(GPIOA,GPIO_Pin_3);
//	GPIO_SetBits(GPIOA,GPIO_Pin_7);	
//
//	GPIO_SetBits(GPIOA,GPIO_Pin_4);
//	GPIO_ResetBits(GPIOA,GPIO_Pin_5);			   //  GPIO_SetBits
//	GPIO_SetBits(GPIOA,GPIO_Pin_6);     	   //GPIO_ResetBits
//}
//
//void set_io9(void)					  										
//{
//	GPIO_ResetBits(GPIOA,GPIO_Pin_3);
//	GPIO_SetBits(GPIOA,GPIO_Pin_7);	
//
//	GPIO_SetBits(GPIOA,GPIO_Pin_4);
//	GPIO_SetBits(GPIOA,GPIO_Pin_5);			   //  GPIO_SetBits
//	GPIO_ResetBits(GPIOA,GPIO_Pin_6);     	   //GPIO_ResetBits
//}
//
//void set_io10(void)					  										
//{
//	GPIO_ResetBits(GPIOA,GPIO_Pin_3);
//	GPIO_SetBits(GPIOA,GPIO_Pin_7);	
//
//	GPIO_SetBits(GPIOA,GPIO_Pin_4);
//	GPIO_SetBits(GPIOA,GPIO_Pin_5);			   //  GPIO_SetBits
//	GPIO_SetBits(GPIOA,GPIO_Pin_6);     	   //GPIO_ResetBits
//}
//
//void set_io11(void)					  										
//{
//	GPIO_ResetBits(GPIOA,GPIO_Pin_3);
//	GPIO_ResetBits(GPIOA,GPIO_Pin_7);	
//
//	GPIO_SetBits(GPIOA,GPIO_Pin_4);
//	GPIO_ResetBits(GPIOA,GPIO_Pin_5);			   //  GPIO_SetBits
//	GPIO_SetBits(GPIOA,GPIO_Pin_6);     	   //GPIO_ResetBits
//}

void set_background(void)
{
	FRONT_COLOR = YELLOW;
	LCD_Clear(DARKBLUE);
	FRONT_COLOR = RED;
	GUI_Show12ASCII(20, 20, "Fre:", FRONT_COLOR, YELLOW);

	GUI_Show12ASCII(20, 40, "VCC:", FRONT_COLOR, YELLOW);

	//
	//LCD_DrawRectangleex(0,9,250,210,FRONT_COLOR);
	//GUI_Line(0,110,250,110,FRONT_COLOR);
	//GUI_Line(125,9,125,210,FRONT_COLOR);
	//FRONT_COLOR=RED;
	//GUI_Box(260,10,260+57,210,YELLOW);
	//LCD_DrawRectangleex(259,9,260+58,211,GREEN);
	//GUI_Show12ASCII(0,224,"www.prechin.com",FRONT_COLOR,WHITE);
	//GUI_Show12ASCII(204,224,"mv",FRONT_COLOR,WHITE);	
	//GUI_Show12ASCII(132,224,"vpp=",FRONT_COLOR,WHITE);
	//GUI_Show12ASCII(260,10,"us/div:",FRONT_COLOR,WHITE);
	//GUI_Show12ASCII(260,90,"mv/div:",FRONT_COLOR,WHITE);
	//
	//GUI_Show12ASCII(260,140,"PA2:",FRONT_COLOR,YELLOW);	
	//GUI_Show12ASCII(260,160,"ADC1_In",FRONT_COLOR,YELLOW);
}


#else






int64_t GetCLKNumber()
{
	return  count * 0xFFFF + TIM_GetCounter(TIM2);
}




void _ConverntClkDif(	uint64_t u64CLKDiff,u16 u16EXTI_Type,u16 _Pin,u16* uData,u16* uDataLen)
{
	
	
	
	
	if (u64CLKDiff < 0xFF)
	{
	    uData[0] = _Pin + u16EXTI_Type + Bits_Len1 + u64CLKDiff; 
	    *uDataLen = 1;
	}
	else if (u64CLKDiff < 0xFFFFFF)
	{
		 uData[0] = _Pin + u16EXTI_Type + Bits_Len2 + ((u64CLKDiff >>16)&0xFF);
		 uData[1] = u64CLKDiff & 0xFFFF;
		  *uDataLen  = 2;

	}

	else if (u64CLKDiff < 0xFFFFFFFFFF)
	{
		uData[0]  = _Pin + u16EXTI_Type + Bits_Len3 + ((u64CLKDiff >> 32) & 0xFF);
		uData[1]  = (u64CLKDiff >> 16) & 0xFFFF;
		uData[2] = u64CLKDiff & 0xFFFF;
		 *uDataLen = 3;
	}

//	else if (u64CLKDiff < 0xFFFFFFFFFFFFFF)
//	{
//		u16CLK[u8Counter[_Channel]][_Channel] = _Pin + u16EXTI_Type + Bits_Len4 + ((u64CLKDiff >> 48) & 0xFF);
//		u16CLK[u8Counter[_Channel] + 1][_Channel] = (u64CLKDiff >> 32) & 0xFFFF;
//		u16CLK[u8Counter[_Channel] + 1][_Channel] = (u64CLKDiff >> 16) & 0xFFFF;
//		u16CLK[u8Counter[_Channel] + 1][_Channel] = u64CLKDiff & 0xFFFF;
//		u8Counter[_Channel] += 4;
//	}
	
	
	
}

void SaveCurrentCLK(u16 u16EXTI_Type,u16 _Pin)
{
	uint64_t u64CLKDiff;
	u8 __ClkLen;
	u8 ii;

	u64CLKDiff = u64CurCLK - u64PreCLK;

#ifndef _2Channel
	if (u64CLKDiff < 0xFF)
		__ClkLen = Bits_Len1;
	else if (u64CLKDiff < 0xFFFFFF)
		__ClkLen = Bits_Len2;
	else if (u64CLKDiff < 0xFFFFFFFFFF)
		__ClkLen = Bits_Len3;

	if ((uCLKCount + 1) > _MaxCLKCount)
		uCLKCount = 0;


	
	
	#ifdef __2Sram
	
	u8CLK[uCLKCount] = _Pin + u16EXTI_Type + __ClkLen;
	FSMC_SRAM_WriteBuf(&u8CLK[uCLKCount],SramOffset,1);
	uCLKCount += 1;
	SramOffset += 1;

	for (ii = (__ClkLen * 2 - 1); ii > 0; ii -= 1)
	{
		if ((uCLKCount + 1) > _MaxCLKCount)
			uCLKCount = 0;
		u8CLK[uCLKCount] = ((u64CLKDiff >> ((ii - 1) * 8)) & 0xFF);
  	    FSMC_SRAM_WriteBuf(&u8CLK[uCLKCount],SramOffset ,1);
		uCLKCount += 1;
		SramOffset += 1;
	}
	
	
	
	
	

	#else
	
	
			u8CLK[uCLKCount] = _Pin + u16EXTI_Type + __ClkLen;
//	FSMC_SRAM_WriteBuf(&u8CLK[uCLKCount],SramOffset,1);
	uCLKCount += 1;
	//SramOffset += 1;

	for (ii = (__ClkLen * 2 - 1); ii > 0; ii -= 1)
	{
		if ((uCLKCount + 1) > _MaxCLKCount)
			uCLKCount = 0;
		u8CLK[uCLKCount] = ((u64CLKDiff >> ((ii - 1) * 8)) & 0xFF);
  //	FSMC_SRAM_WriteBuf(&u8CLK[uCLKCount],SramOffset,1);
		uCLKCount += 1;
	//	SramOffset += 1;
	}
	

	#endif
	
	
	
	u64PreCLK = u64CurCLK;
	
	

#else

	if (u64CLKDiff < 0xFF)
		__ClkLen = Bits_Len1;
	else if (u64CLKDiff < 0xFFFFFF)
		__ClkLen = Bits_Len2;
	else if (u64CLKDiff < 0xFFFFFFFFFF)
		__ClkLen = Bits_Len3;


	for (ii = (__ClkLen * 2 - 1); ii > 0; ii -= 1)
	{
		u8CLKT[uCount[u8Channel]][u8Channel] = ((u64CLKDiff >> ((ii - 1) * 8)) & 0xFF);

		uCount[u8Channel] += 1;
	}

	

	u64PreCLK = u64CurCLK;
#endif



}



void TIM2_IRQHandler(void)
{

	if (TIM_GetITStatus(TIM2, TIM_IT_Update))
	{
		TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
		count++;

	}

}

//void TIM3_IRQHandler(void)
//{

//	if (TIM_GetITStatus(TIM3, TIM_IT_Update))
//	{
//		TIM_ClearITPendingBit(TIM3, TIM_IT_Update);
//		count++;

//	}
//	
//}

//void TIM4_IRQHandler(void)
//{
//	if (TIM_GetITStatus(TIM4, TIM_IT_Update))
//	{
//
//		//TIM_Cmd(TIM4, DISABLE);
//		////清除TIM状态
//		//TIM_ClearITPendingBit(TIM4, TIM_IT_Update);
//		////获取TIM3计数
//		//frequency = GetCLKNumber() - u64StartCLK;
//		//if (frequency < 1000000)
//		//	frequency = 0;
//
//
//
//		//TIM_SetCounter(TIM4, 0);
//		//u64StartCLK = GetCLKNumber();
//		////printf("%llu::",u64StartCLK);
//		//TIM_Cmd(TIM4, ENABLE);
//
//	}
//}


//void EXTI0_IRQHandler(void)
//{
//	//if (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0))
//	//{
//		EXTI_ClearITPendingBit(EXTI_Line0);
//		SaveCurrentCLK(u8Channel);
//	//}
//}

//void EXTI_Switch(void)
//{
//	if (u8EXIT_Type == EXIT_RAISE)
//		EXTI_StructInit(&EXTI_InitStructure2);
//	else
//    	EXTI_StructInit(&EXTI_InitStructure3);
//
//	u8EXIT_Type = !u8EXIT_Type;
//}






void EXTI2_IRQHandler(void)
{
	u64CurCLK = GetCLKNumber();
	EXTI_ClearITPendingBit(EXTI_Line2);

	
	if ((u16EXIT_Type != EXIT_FALL)&&
		(GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_2) == 0))
	{
		u16EXIT_Type = EXIT_FALL;
		SaveCurrentCLK(EXIT_RAISE ,Pin_IO);
		
	}

}

void EXTI3_IRQHandler(void)
{
	u64CurCLK = GetCLKNumber();
	EXTI_ClearITPendingBit(EXTI_Line3);
	if 	((u16EXIT_Type != EXIT_RAISE) &&
		(GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_3) == 1))
	{
		u16EXIT_Type = EXIT_RAISE;
		SaveCurrentCLK(EXIT_FALL,Pin_IO);
		
	}

}

void EXTI4_IRQHandler(void)
{
	u64CurCLK = GetCLKNumber();
	EXTI_ClearITPendingBit(EXTI_Line4);



	if ((u8Clk_EXIT_TYPE&CLK_EXITT_RAISE != EXIT_RAISE) &&
		(GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_4) == 1))
	{
		u8Clk_EXIT_TYPE = CLK_EXITT_FALL;
		SaveCurrentCLK( EXIT_FALL,Pin_CLK);

	}

	if ((u8Clk_EXIT_TYPE&CLK_EXITT_FALL != CLK_EXITT_FALL) &&
		(GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_4) == 0))
	{
		u8Clk_EXIT_TYPE = CLK_EXITT_RAISE;
		SaveCurrentCLK(EXIT_RAISE, Pin_CLK);

	}



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
	NVIC_InitTypeStruct.NVIC_IRQChannelCmd = ENABLE;
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
	EXTI_InitTypeStruct.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EXTI_InitTypeStruct);




}


#endif 
