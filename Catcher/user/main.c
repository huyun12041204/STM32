/* �������غ�D1ָʾ����˸��ʾ�����������У�����K_UP�л�Ƶ����ʾ���ƺ͵�ѹ���Ƶ��ڣ�
	K_DOWN��������K_RIGHT�����ӣ�AD����˿ڲ���PA2������ʹ������һ������STM32������
	�����������׵�һ�����巢�������ȥ���ԣ�����ͨ��PC1�ڷ��ͳ���ͨ������ֱ�����뵽ʾ����
	�������ϵ�PA2�ڼ��ɼ�⵽����Ĳ��Σ����ֻ��һ������STM32����������ѿ���ʹ���ź�
	�����������ź����뵽PA2�ڡ�����ֻ������һ���򵥵Ĳɼ�����ʾ���ڣ��ɼ��ľ��Ⱥ�׼ȷ��
	���ǱȽϸߵġ�*/

#include "system.h"
#include "SysTick.h"
#include "usart.h"
#include "led.h"
#include "button.h"
#include "tftlcd.h"
#include "gui.h"
#include "tim.h"
#include "stm32f10x_it.h"
#include "adc.h"

#include "String.h"

u8 u8Digit2Ascii(u8 u8Digit,u8* u8Ascii)
{

	u8 u8temp[3];
	u8 u8TDigit = u8Digit;
	u8 i;

	for ( i = 3; i > 0; i--)
	{
		u8temp[i-1]= u8TDigit % 10 + 0x30;
		u8TDigit = u8TDigit / 10;
	}

	for (i = 0; i < 2; i++)
	{
		if (u8temp[i] != 0x30)
			break;
	}

	memcpy(u8Ascii, u8temp+i, 3 - i);

	return 3 - i;

}

u8 u16Digit2Ascii(u16 u16Digit, u8* u8Ascii)
{

	u8 u8temp[5];
	u16 TDigit = u16Digit;
	u8 i;

	for (i = 5; i > 0; i--)
	{
		u8temp[i - 1] = TDigit % 10 + 0x30;
		TDigit = TDigit / 10;
	}

	for (i = 0; i < 5; i++)
	{
		if (u8temp[i] != 0x30)
			break;
	}

	memcpy(u8Ascii, u8temp + i, 5 - i);

	return 5 - i;

}

//u8 floatDigit2Ascii(u16 fDigit, u8* u8Ascii)
//{

//	u8 u8temp[6];
//	u16 TDigit = fDigit;
//	u8 i;

//	for (i = 6; i > 0; i--)
//	{
//		if(i == 4)
//		{
//			u8temp[4] = '.';
//		}
//		else
//		{
//			u8temp[i - 1] = TDigit % 10 + 0x30;
//			TDigit = TDigit / 10;
//		}
//	}

//	for (i = 0; i <3; i++)
//	{
//		if (u8temp[i] != 0x30)
//			break;
//	}

//	memcpy(u8Ascii, u8temp + i, 6 - i);

//	return 6 - i;

//}



u16 j = 0;
float temp;
float temp1;


void clear_point(u16 hang)
{
	u8 index_clear_lie = 0; 
	FRONT_COLOR = DARKBLUE;
	for(index_clear_lie = 0;index_clear_lie <201;index_clear_lie++)
	{		
		lcd_huadian(hang,index_clear_lie,FRONT_COLOR);
	}	
	FRONT_COLOR=RED;	
}
void nvic_init(void)
{
	NVIC_InitTypeDef    NVIC_InitTypeStruct;

	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);

	NVIC_InitTypeStruct.NVIC_IRQChannel = EXTI0_IRQn;
	NVIC_InitTypeStruct.NVIC_IRQChannelPreemptionPriority =	2;
	NVIC_InitTypeStruct.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitTypeStruct.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitTypeStruct);

	/*NVIC_InitTypeStruct.NVIC_IRQChannel = EXTI3_IRQn;
	NVIC_InitTypeStruct.NVIC_IRQChannelPreemptionPriority =	2;
	NVIC_InitTypeStruct.NVIC_IRQChannelSubPriority = 1;
	NVIC_InitTypeStruct.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitTypeStruct);

	NVIC_InitTypeStruct.NVIC_IRQChannel = EXTI4_IRQn;
	NVIC_InitTypeStruct.NVIC_IRQChannelPreemptionPriority =	2;
	NVIC_InitTypeStruct.NVIC_IRQChannelSubPriority = 2;
	NVIC_InitTypeStruct.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitTypeStruct);*/

	NVIC_InitTypeStruct.NVIC_IRQChannel = TIM2_IRQn;  		   //�����ж����ȼ�
	NVIC_InitTypeStruct.NVIC_IRQChannelPreemptionPriority =	0;
	NVIC_InitTypeStruct.NVIC_IRQChannelSubPriority = 3;
	NVIC_InitTypeStruct.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitTypeStruct);

	NVIC_InitTypeStruct.NVIC_IRQChannel = TIM3_IRQn; 
	NVIC_InitTypeStruct.NVIC_IRQChannelPreemptionPriority =	0;
	NVIC_InitTypeStruct.NVIC_IRQChannelSubPriority = 3;
	NVIC_InitTypeStruct.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitTypeStruct);
}

void rcc_init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1,ENABLE);

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOE|RCC_APB2Periph_AFIO, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);
	RCC_ADCCLKConfig(RCC_PCLK2_Div6);
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1,ENABLE);
}

void gpio_init(void)
{
	GPIO_InitTypeDef GPIO_InitTypeStruct;

	GPIO_InitTypeStruct.GPIO_Pin = GPIO_Pin_2;
	GPIO_InitTypeStruct.GPIO_Speed = GPIO_Speed_50MHz;				 //�ⲿʱ�ӵģ�������Ƶ�ʵģ�
	GPIO_InitTypeStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOD, &GPIO_InitTypeStruct);

	GPIO_InitTypeStruct.GPIO_Pin = GPIO_Pin_2;
	GPIO_InitTypeStruct.GPIO_Speed = GPIO_Speed_50MHz;		 		 //adc��������
	GPIO_InitTypeStruct.GPIO_Mode = GPIO_Mode_AIN;
	GPIO_Init(GPIOA, &GPIO_InitTypeStruct);

	GPIO_InitTypeStruct.GPIO_Pin = GPIO_Pin_3 | GPIO_Pin_4;
	GPIO_InitTypeStruct.GPIO_Speed = GPIO_Speed_50MHz;		 		 //�ⲿ�жϵ�io����
	GPIO_InitTypeStruct.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_Init(GPIOE, &GPIO_InitTypeStruct);

	GPIO_InitTypeStruct.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitTypeStruct.GPIO_Speed = GPIO_Speed_50MHz;		 		//�ⲿ�жϵ�io����
	GPIO_InitTypeStruct.GPIO_Mode = GPIO_Mode_IPD;
	GPIO_Init(GPIOA, &GPIO_InitTypeStruct);

	GPIO_InitTypeStruct.GPIO_Pin = GPIO_Pin_8;					 //��ʱ��1����adת����������Ǹ���
	GPIO_InitTypeStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitTypeStruct.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_Init(GPIOA, &GPIO_InitTypeStruct);

	GPIO_InitTypeStruct.GPIO_Pin = GPIO_Pin_3;
	GPIO_InitTypeStruct.GPIO_Speed = GPIO_Speed_50MHz;		 		// adc3
	GPIO_InitTypeStruct.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOA, &GPIO_InitTypeStruct);

	GPIO_InitTypeStruct.GPIO_Pin = GPIO_Pin_4;
	GPIO_InitTypeStruct.GPIO_Speed = GPIO_Speed_50MHz;		 		//	adc4
	GPIO_InitTypeStruct.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOA, &GPIO_InitTypeStruct);

	GPIO_InitTypeStruct.GPIO_Pin = GPIO_Pin_5;
	GPIO_InitTypeStruct.GPIO_Speed = GPIO_Speed_50MHz;		 		//	adc5
	GPIO_InitTypeStruct.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOA, &GPIO_InitTypeStruct);

	GPIO_InitTypeStruct.GPIO_Pin = GPIO_Pin_6;
	GPIO_InitTypeStruct.GPIO_Speed = GPIO_Speed_50MHz;		 		//	adc6
	GPIO_InitTypeStruct.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOA, &GPIO_InitTypeStruct);

	GPIO_InitTypeStruct.GPIO_Pin = GPIO_Pin_7;
	GPIO_InitTypeStruct.GPIO_Speed = GPIO_Speed_50MHz;		 		// adc7
	GPIO_InitTypeStruct.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOA, &GPIO_InitTypeStruct);

	GPIO_InitTypeStruct.GPIO_Pin = GPIO_Pin_8;
	GPIO_InitTypeStruct.GPIO_Speed = GPIO_Speed_50MHz;		 	
	GPIO_InitTypeStruct.GPIO_Mode = GPIO_Mode_IPD;
	GPIO_Init(GPIOA, &GPIO_InitTypeStruct);
}
int main(void)
{	
	u8 clk_buf[6];
	u8 vpp_buf[6];
	u16 u16CLK = 0;
	u16 u16VPP = 0;
	SysTick_Init(72);
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);  //�ж����ȼ����� ��2��
	USART1_Init(9600);		//��ʼ�����ڲ�����Ϊ115200 
	rcc_init();			   //����ʱ������	
	led_init();				
	TFTLCD_Init();
	LCD_Clear(DARKBLUE);
	nvic_init();		   // �ж����ȼ�����
	gpio_init();		   	//����io������
	set_io0();
	//key_init();
	//ADC1_Init();	//adc����
	IO_Init();
	ADCx_Init();
	set_background();	 	 //��ʼ������
	 
	time_init();			//��ʱ�����ã���Ƶ���õĶ�����ʱ��
	time_enable();			//ͬ����ʼ����
	//ADC_Get_Value();
	//vpp = ADC_Get_Vpp();

	while(1)
	{	
		u16CLK = frequency/1000;
		clk_buf[u16Digit2Ascii(u16CLK, clk_buf)] = '\0';

		GUI_Show12ASCII(60, 20, clk_buf, FRONT_COLOR, WHITE);

		GUI_Show12ASCII(100, 20, "kHz", FRONT_COLOR, WHITE);

		memset(vpp_buf, '\0', 6);
	
		u16VPP = Get_ADCx_Value(ADC_Channel_2,100);
		vpp_buf[0] = u16VPP/1000 + 0x30;
		vpp_buf[1] = '.';
		vpp_buf[2] = u16VPP%1000/100+ 0x30;
		vpp_buf[3] = u16VPP%100/10+ 0x30;
		
		GUI_Show12ASCII(60,40,vpp_buf,FRONT_COLOR,WHITE);	
		GUI_Show12ASCII(100, 40, "v", FRONT_COLOR, WHITE);
		
	
	}
}





