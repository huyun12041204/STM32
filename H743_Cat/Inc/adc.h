
//#define NODMAADC

#ifdef NODMAADC

#ifndef __ADC_H
#define __ADC_H
#include "sys.h"

void MY_ADC_Init(void); 				//ADC通道初始化
u16  Get_Adc(u32 ch); 		        //获得某个通道值 
u16 Get_Adc_Average(u32 ch,u8 times);//得到某个通道给定次数采样的平均值
#endif 

#else


/**
  ******************************************************************************
  * File Name          : ADC.h
  * Description        : This file provides code for the configuration
  *                      of the ADC instances.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2019 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under Ultimate Liberty license
  * SLA0044, the "License"; You may not use this file except in compliance with
  * the License. You may obtain a copy of the License at:
  *                             www.st.com/SLA0044
  *
  ******************************************************************************
  */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __adc_H
#define __adc_H
#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* USER CODE BEGIN Includes */

/* USER CODE END Includes */
	 
#define _ADC_BUF_SIZE 50

	 
	 
extern ADC_HandleTypeDef hadc2;

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

void MX_ADC2_Init(void);
	 
uint16_t Get_ADC_VCC(void);

/* USER CODE BEGIN Prototypes */

/* USER CODE END Prototypes */

#ifdef __cplusplus
}
#endif
#endif /*__ adc_H */

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

#endif

