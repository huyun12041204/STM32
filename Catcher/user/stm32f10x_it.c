#include "stm32f10x_it.h"
#include "gui.h"
#include "system.h"
#include "SysTick.h"
#include "tim.h"
#include "adc.h"
#include "button.h"
#include "led.h"
#include "stdio.h" 






				









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


#define EXIT_FALL  0
#define EXIT_RAISE 1

uint64_t u64StartCLK;

uint8_t      u8Channel;
uint64_t     u64CLK[1000][2];
uint8_t      bBit[1000][2];
uint8_t      u8Counter[2];

uint32_t count;

//EXTI_InitTypeDef EXTI_InitStructure2;
//EXTI_InitTypeDef EXTI_InitStructure3;
u8       u8EXIT_Type;
uint64_t u64CurCLK;


int64_t GetCLKNumber()
{
	return  count * 0xFFFF + TIM_GetCounter(TIM2);
}

void SaveCurrentCLK(u8 _Channel)
{

	u64CLK[u8Counter[_Channel]][_Channel] = u64CurCLK;
	bBit[u8Counter[_Channel]][_Channel] = u8EXIT_Type;

	u8Counter[_Channel]++;

	if (u8Counter[_Channel] > 1000)
		printf("LIMIT");

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
	if (GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_2) == 0)
	{
		SaveCurrentCLK(u8Channel);
		u8EXIT_Type = EXIT_RAISE;
	}

}

void EXTI3_IRQHandler(void)
{
	u64CurCLK = GetCLKNumber();
	EXTI_ClearITPendingBit(EXTI_Line3);
	if (GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_3) == 1)
	{
		SaveCurrentCLK(u8Channel);
		u8EXIT_Type = EXIT_FALL;
	}

}







#endif 
