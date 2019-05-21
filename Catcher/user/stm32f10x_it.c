#include "stm32f10x_it.h"
#include "gui.h"
#include "system.h"
#include "SysTick.h"
#include "tim.h"
#include "adc.h"
#include "button.h"
#include "led.h"
#include "stdio.h" 
u8 frequency_flag = 0;
long int shao_miao_shu_du = 0;
u8 num_shao_miao = 8;
u8 mode = 0;
u8 num_fu_du =7;
u8 ad_flag = 1;
float gao_pin_palus = 0;
u16 vcc_div = 0;
u16 vpp;

uint64_t uTempCounter;


int64_t      uTimes1[0x1000];
uint8_t      bBit1[0x1000];
uint16_t     uTimes2[0x1000];
uint8_t      bBit2[0x1000];
uint8_t  uCounter1;
uint8_t  uCounter2;
uint8_t   u8Channel;
				
void set_io0(void)					  										
{
	GPIO_ResetBits(GPIOA,GPIO_Pin_3);	
	GPIO_ResetBits(GPIOA,GPIO_Pin_4);
	GPIO_ResetBits(GPIOA,GPIO_Pin_5);
	GPIO_ResetBits(GPIOA,GPIO_Pin_6);
	GPIO_ResetBits(GPIOA,GPIO_Pin_7);
	

}

void set_io1(void)					  										
{
	GPIO_SetBits(GPIOA,GPIO_Pin_3);
	GPIO_SetBits(GPIOA,GPIO_Pin_7);	

	GPIO_ResetBits(GPIOA,GPIO_Pin_4);
	GPIO_ResetBits(GPIOA,GPIO_Pin_5);
	GPIO_ResetBits(GPIOA,GPIO_Pin_6);     
}

void set_io2(void)					  										
{
	GPIO_SetBits(GPIOA,GPIO_Pin_3);
	GPIO_SetBits(GPIOA,GPIO_Pin_7);	

	GPIO_ResetBits(GPIOA,GPIO_Pin_4);
	GPIO_ResetBits(GPIOA,GPIO_Pin_5);
	GPIO_SetBits(GPIOA,GPIO_Pin_6);     
}

void set_io3(void)					  										
{
	GPIO_SetBits(GPIOA,GPIO_Pin_3);
	GPIO_SetBits(GPIOA,GPIO_Pin_7);	

	GPIO_ResetBits(GPIOA,GPIO_Pin_4);
	GPIO_SetBits(GPIOA,GPIO_Pin_5);			   //  GPIO_SetBits
	GPIO_ResetBits(GPIOA,GPIO_Pin_6);     	   //GPIO_ResetBits
}

void set_io4(void)					  										
{
	GPIO_SetBits(GPIOA,GPIO_Pin_3);
	GPIO_SetBits(GPIOA,GPIO_Pin_7);	

	GPIO_ResetBits(GPIOA,GPIO_Pin_4);
	GPIO_SetBits(GPIOA,GPIO_Pin_5);			   //  GPIO_SetBits
	GPIO_SetBits(GPIOA,GPIO_Pin_6);     	   //GPIO_ResetBits
}

void set_io5(void)					  										
{
	GPIO_SetBits(GPIOA,GPIO_Pin_3);
	GPIO_SetBits(GPIOA,GPIO_Pin_7);	

	GPIO_SetBits(GPIOA,GPIO_Pin_4);
	GPIO_ResetBits(GPIOA,GPIO_Pin_5);			   //  GPIO_SetBits
	GPIO_SetBits(GPIOA,GPIO_Pin_6);     	   //GPIO_ResetBits
}

void set_io6(void)					  										
{
	GPIO_SetBits(GPIOA,GPIO_Pin_3);
	GPIO_SetBits(GPIOA,GPIO_Pin_7);	

	GPIO_SetBits(GPIOA,GPIO_Pin_4);
	GPIO_SetBits(GPIOA,GPIO_Pin_5);			   //  GPIO_SetBits
	GPIO_ResetBits(GPIOA,GPIO_Pin_6);     	   //GPIO_ResetBits
}

void set_io7(void)					  										
{
	GPIO_SetBits(GPIOA,GPIO_Pin_3);
	GPIO_SetBits(GPIOA,GPIO_Pin_7);	

	GPIO_SetBits(GPIOA,GPIO_Pin_4);
	GPIO_SetBits(GPIOA,GPIO_Pin_5);			   //  GPIO_SetBits
	GPIO_SetBits(GPIOA,GPIO_Pin_6);     	   //GPIO_ResetBits
}

void set_io8(void)					  										
{
	GPIO_ResetBits(GPIOA,GPIO_Pin_3);
	GPIO_SetBits(GPIOA,GPIO_Pin_7);	

	GPIO_SetBits(GPIOA,GPIO_Pin_4);
	GPIO_ResetBits(GPIOA,GPIO_Pin_5);			   //  GPIO_SetBits
	GPIO_SetBits(GPIOA,GPIO_Pin_6);     	   //GPIO_ResetBits
}

void set_io9(void)					  										
{
	GPIO_ResetBits(GPIOA,GPIO_Pin_3);
	GPIO_SetBits(GPIOA,GPIO_Pin_7);	

	GPIO_SetBits(GPIOA,GPIO_Pin_4);
	GPIO_SetBits(GPIOA,GPIO_Pin_5);			   //  GPIO_SetBits
	GPIO_ResetBits(GPIOA,GPIO_Pin_6);     	   //GPIO_ResetBits
}

void set_io10(void)					  										
{
	GPIO_ResetBits(GPIOA,GPIO_Pin_3);
	GPIO_SetBits(GPIOA,GPIO_Pin_7);	

	GPIO_SetBits(GPIOA,GPIO_Pin_4);
	GPIO_SetBits(GPIOA,GPIO_Pin_5);			   //  GPIO_SetBits
	GPIO_SetBits(GPIOA,GPIO_Pin_6);     	   //GPIO_ResetBits
}

void set_io11(void)					  										
{
	GPIO_ResetBits(GPIOA,GPIO_Pin_3);
	GPIO_ResetBits(GPIOA,GPIO_Pin_7);	

	GPIO_SetBits(GPIOA,GPIO_Pin_4);
	GPIO_ResetBits(GPIOA,GPIO_Pin_5);			   //  GPIO_SetBits
	GPIO_SetBits(GPIOA,GPIO_Pin_6);     	   //GPIO_ResetBits
}

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



void TIM2_IRQHandler(void)
{
	
	if (TIM_GetITStatus(TIM2, TIM_IT_Update))
	{
		TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
		count++;

	}
	//if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET)
	//{

	//	if (u8Channel == 1)
	//	{

	//		uTimes1[uCounter1] = count * 0xFFFF + TIM_GetCounter(TIM3);
	//		bBit1[uCounter1] = GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0);
	//		uCounter1++;
	//	}
	//	else
	//	{
	//		uTimes2[uCounter2] = count * 0xFFFF + TIM_GetCounter(TIM3);
	//		bBit2[uCounter2] = GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0);
	//		uCounter2++;
	//	}

	//}

	//TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
}

void TIM3_IRQHandler(void)
{
	//if(TIM_GetITStatus(TIM3, TIM_IT_Update))
	//{
 //  		TIM_ClearITPendingBit(TIM3, TIM_IT_Update);
	//	count++;
	//	
	//}


	if (TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET)
	{

		if (u8Channel == 1)
		{
			
			uTimes1[uCounter1] = count * 0xFFFF + TIM_GetCounter(TIM2);
			bBit1[uCounter1] = GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0);

		//	printf("clk:%08x,", uTimes1[uCounter1]);
			uCounter1++;
		}
		else
		{
			uTimes2[uCounter2] = count * 0xFFFF + TIM_GetCounter(TIM2);
			bBit2[uCounter2] = GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0);
			uCounter2++;
		}

	}

	TIM_ClearITPendingBit(TIM3, TIM_IT_Update);
}

void TIM4_IRQHandler(void)
{
	if (TIM_GetITStatus(TIM4, TIM_IT_Update))
	{

		TIM_Cmd(TIM4, DISABLE);
		//清除TIM状态
		TIM_ClearITPendingBit(TIM4, TIM_IT_Update);
		//获取TIM3计数
		if (uTempCounter != 0)
		{
			frequency = 65536 * count + TIM_GetCounter(TIM2) - uTempCounter;
		}

		TIM_SetCounter(TIM4, 0);

		uTempCounter = 65536 * count + TIM_GetCounter(TIM2);
		TIM_Cmd(TIM4, ENABLE);

	}
}


