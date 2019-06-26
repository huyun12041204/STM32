
#ifndef __STM32F10x_IT_H
#define __STM32F10x_IT_H

#ifdef __cplusplus
 extern "C" {
#endif 

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"

#ifndef EXIT_FALL
#define EXIT_FALL  0x0
#define EXIT_RAISE 0x8
#define EXIT_ALL   0xF
#endif


#ifndef CLK_EXITT_ALL 
#define CLK_EXITT_FALL  0x1
#define CLK_EXITT_RAISE  0x2
#define CLK_EXITT_ALL   0x3
#endif


#ifndef  Pin_ALL
#define  Pin_ALL 0x70
#define  Pin_VCC 0x10
#define  Pin_RES 0x20
#define  Pin_CLK 0x30
#define  Pin_IO  0x40 
#endif

#ifndef Bits_Number
#define Bits_Number 0x7
#define Bits_Len1   0x1
#define Bits_Len2   0x2
#define Bits_Len3   0x3
#define Bits_Len4   0x4
#define Bits_Len5   0x5
#define Bits_Len6   0x6
#define Bits_Len7   0x7
#endif 

#define _MaxCLKCount 50000


#ifdef _ORI

	 //extern u8 frequency_flag;
//extern long int shao_miao_shu_du;
//extern u8 num_shao_miao;
//extern u8 mode;
//extern u8 num_fu_du;
//extern u8 ad_flag;
//extern u16 vpp;
//extern float gao_pin_palus;
//extern u16 vcc_div;

	 void lcd_huadian(u16 a, u16 b, u16 color);
	 void lcd_huaxian(u16 x1, u16 y1, u16 x2, u16 y2, u16 color);
	 void hua_wang(void);
	 void set_background(void);

	
	 void key_init(void);

	 void IO3_Init(void);
	 void set_io0(void);
	 void set_io1(void);
	 void set_io2(void);
	 void set_io3(void);
	 void set_io4(void);
	 void set_io5(void);
	 void set_io6(void);
	 void set_io7(void);
	 void set_io8(void);
	 void set_io9(void);
	 void set_io10(void);
	 void set_io11(void);
	 /* Exported types ------------------------------------------------------------*/
	 /* Exported constants --------------------------------------------------------*/
	 /* Exported macro ------------------------------------------------------------*/
	 /* Exported functions ------------------------------------------------------- */

	 void NMI_Handler(void);
	 void HardFault_Handler(void);
	 void MemManage_Handler(void);
	 void BusFault_Handler(void);
	 void UsageFault_Handler(void);
	 void SVC_Handler(void);
	 void DebugMon_Handler(void);
	 void PendSV_Handler(void);
	 void SysTick_Handler(void);

#else
void IO_Init(void);
void EXIT2_PARAM(void);
void _ConverntClkDif(uint64_t u64CLKDiff, u16 u16EXTI_Type, u16 _Pin, u16* uData, u16* uDataLen);
void SaveCurrentCLK( u16 u16EXTI_Type, u16 _Pin);
void PINx_EXIT_Init(void);
#endif





#ifdef __cplusplus
}
#endif

#endif /* __STM32F10x_IT_H */

/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
