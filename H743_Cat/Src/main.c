/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
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
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "usb_device.h"
#include "lcd.h"
#include "var.h"
#include "operation.h"
#include "usart.h"
#include "sdmmc.h"
#include "tim.h"
#include "gpio.h"
#include "command.h"
#include "dma.h"
#include "adc.h"
//#include "usart_if.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

extern SD_HandleTypeDef hsd1;
extern TIM_HandleTypeDef htim1;
extern TIM_HandleTypeDef htim2;
extern TIM_HandleTypeDef htim3;
extern TIM_HandleTypeDef htim4;
extern TIM_HandleTypeDef htim5;
extern TIM_HandleTypeDef htim7;
extern UART_HandleTypeDef huart1;
extern USBD_HandleTypeDef hUsbDeviceHS;

extern ADC_HandleTypeDef hadc1;
extern DMA_HandleTypeDef hdma_adc1;


/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);



static void MX_NVIC_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
 {
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

	u16 TEMP;

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
    Cache_Enable();                 //打开L1-Cache
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_SDMMC1_SD_Init();
  MX_TIM1_Init();
  MX_TIM2_Init();
  MX_TIM3_Init();
  //MX_TIM4_Init();
	MX_TIM5_Init();
	MX_TIM7_Init();
	
  MX_USB_DEVICE_Init();
  MX_USART1_UART_Init();

	MX_DMA_Init();
	
  MX_ADC1_Init();
	

	//MX_RTC_Init();
	
//  
  /* Initialize interrupts */
  MX_NVIC_Init();
	

	
	//PrintfSDInformation();
  /* USER CODE BEGIN 2 */
	
		LCD_View_Init();
	

#if __USE_FATFS
    MX_FATFS_Init();
		FileStatue = SDIsReadForSave();

#ifdef __Test_FATFS
	 Test_FATFS1();
#endif

#endif


  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
	
	
	


  HAL_TIM_Base_Start(&htim1); //使能定时器1
	HAL_TIM_IC_Start_IT(&htim1,TIM_CHANNEL_1);
	HAL_TIM_IC_Start_IT(&htim1,TIM_CHANNEL_2);
	
	HAL_TIM_Base_Start(&htim2); //使能定时器1  	
	HAL_TIM_IC_Start_IT(&htim2,TIM_CHANNEL_1);
	HAL_TIM_IC_Start_IT(&htim2,TIM_CHANNEL_2);
	
	HAL_TIM_Base_Start(&htim3); //使能定时器1
	HAL_TIM_IC_Start_IT(&htim3,TIM_CHANNEL_1);
	HAL_TIM_IC_Start_IT(&htim3,TIM_CHANNEL_2);
	
	//HAL_TIM_Base_Start_IT(&htim4); //使能定时器3和定时器4更新中断：TIM_IT_UPDATE    
	
	HAL_TIM_Base_Start_IT(&htim5);
	
	HAL_TIM_Base_Start_IT(&htim7); //使能定时器3和定时器4更新中断：TIM_IT_UPDATE    
	 u32CLKLen  = 0;
//   u32SendLen = 0;


  // HAL_ADC_Stop_DMA(&hadc1);

 //HAL_ADCEx_Calibration_Start(&hadc1,ADC_CALIB_OFFSET,ADC_SINGLE_ENDED); //ADC校准
  
 HAL_NVIC_DisableIRQ(DMA1_Stream0_IRQn);
//	TEMP = 0;
//  HAL_ADC_Start_DMA(&hadc1,&TEMP,1);
	
	HAL_ADC_Start_DMA(&hadc1,ADC_DATA,1);
	
	
	 while (1)
 
	 {		
    /* USER CODE END WHILE */

		 
		
		 
   //  VCC=Get_Adc_Average(1,20);//获取通道19的转换值，20次取平均
		//  VCC=Get_Adc_Average(ADC_CHANNEL_3,20);//获取通道19的转换值，20次取平均
	//	 _VCC=(float)VCC*(3.3/65536);//获取计算后的带小数的实际电压值，比如3.1111
   // VCC=Get_Adc_Average(3,20);//获取通道19的转换值，20次取平均
 // VCC=Get_Adc_Average(4,20);//获取通道19的转换值，20次取平均
    /* USER CODE BEGIN 3 */
		 
		 //此处进行切换CLK的使用,
		 //当使用内部CLK 时, PE0 为1时, 停用 TIM7;

		 if((iExtCLK == 0)&&((GPIOA->IDR & GPIO_PIN_15) != 00))
		 {
			 if((GPIOA->IDR & GPIO_PIN_4)!= 0)
			 { 
				 GetCLKNumber(1);
				 SaveCLkNumber( GetPinValue());	 
				 TIM7->CNT   = 0;
				 uInterHigh  = 0;
				 HAL_TIM_Base_Stop_IT(&htim7);
				 iExtCLK = Pin_CLK;
				 
			 }
			 
			 

		 }
		 //当不是用内部CLK 时, 但PE0 为0 时,开启TIM7;
		 
		 else if ((iExtCLK == Pin_CLK)&&((GPIOA->IDR & GPIO_PIN_15) == 00))
		 {
			 
			 
			 if((GPIOA->IDR & GPIO_PIN_4)== 0)
			 { 
			   GetCLKNumber(1);
         SaveCLkNumber( GetPinValue());	 
			   TIM7->CNT   = 0;
			   uInterHigh  = 0;
			   HAL_TIM_Base_Start_IT(&htim7);
			   iExtCLK = 0;
			 
			 }
			 

		 }
		

	//	 printf("%d mv \n", (ADC_DATA[50]*3300 / 0xFFFF));
	
		 __GetBits_Send();
		 
	
	//	  hcdc = (USBD_CDC_HandleTypeDef*) hUsbDeviceHS->pClassData;
//		 if(u32CLKLen > u32SendLen)
//			 _CLKBuff_Send();
#if __USE_FATFS
		 if (FileStatue == FileIsRead)
			 Save1LineCLKBuffer();
#endif
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
  RCC_PeriphCLKInitTypeDef PeriphClkInitStruct = {0};

  /** Supply configuration update enable 
  */
  HAL_PWREx_ConfigSupply(PWR_LDO_SUPPLY);
  /** Configure the main internal regulator output voltage 
  */
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  while(!__HAL_PWR_GET_FLAG(PWR_FLAG_VOSRDY)) {}
  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI48|RCC_OSCILLATORTYPE_HSI
                              |RCC_OSCILLATORTYPE_LSI|RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSIState = RCC_HSI_DIV1;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.LSIState = RCC_LSI_ON;
  RCC_OscInitStruct.HSI48State = RCC_HSI48_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 5;
  RCC_OscInitStruct.PLL.PLLN = 160;
  RCC_OscInitStruct.PLL.PLLP = 2;
  RCC_OscInitStruct.PLL.PLLQ = 2;
  RCC_OscInitStruct.PLL.PLLR = 2;
  RCC_OscInitStruct.PLL.PLLRGE = RCC_PLL1VCIRANGE_2;
  RCC_OscInitStruct.PLL.PLLVCOSEL = RCC_PLL1VCOWIDE;
  RCC_OscInitStruct.PLL.PLLFRACN = 0;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2
                              |RCC_CLOCKTYPE_D3PCLK1|RCC_CLOCKTYPE_D1PCLK1;
  RCC_ClkInitStruct.SYSCLKSource   = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.SYSCLKDivider  = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.AHBCLKDivider  = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB3CLKDivider = RCC_APB3_DIV2;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_APB1_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_APB2_DIV2;
  RCC_ClkInitStruct.APB4CLKDivider = RCC_APB4_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
  PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_RTC|RCC_PERIPHCLK_USART1
                              |RCC_PERIPHCLK_SDMMC|RCC_PERIPHCLK_USB;
  PeriphClkInitStruct.SdmmcClockSelection = RCC_SDMMCCLKSOURCE_PLL;
  PeriphClkInitStruct.Usart16ClockSelection = RCC_USART16CLKSOURCE_D2PCLK2;
  PeriphClkInitStruct.UsbClockSelection = RCC_USBCLKSOURCE_HSI48;
  PeriphClkInitStruct.RTCClockSelection = RCC_RTCCLKSOURCE_LSI;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  HAL_RCC_MCOConfig(RCC_MCO1, RCC_MCO1SOURCE_HSI, RCC_MCODIV_1);
  /** Enable USB Voltage detector 
  */
  HAL_PWREx_EnableUSBVoltageDetector();
}

/**
  * @brief NVIC Configuration.
  * @retval None
  */
static void MX_NVIC_Init(void)
{
  /* OTG_HS_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(OTG_HS_IRQn, 2, 2);
  HAL_NVIC_EnableIRQ(OTG_HS_IRQn);
  /* TIM1_CC_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(TIM1_CC_IRQn, 1, 0);
  HAL_NVIC_EnableIRQ(TIM1_CC_IRQn);
  /* TIM2_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(TIM2_IRQn, 1, 1);
  HAL_NVIC_EnableIRQ(TIM2_IRQn);
  /* TIM3_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(TIM3_IRQn, 1, 2);
  HAL_NVIC_EnableIRQ(TIM3_IRQn);
  /* TIM4_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(TIM4_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(TIM4_IRQn);
	
	
	HAL_NVIC_SetPriority(TIM5_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(TIM5_IRQn);
	/* TIM4_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(TIM7_IRQn,2, 0);
	HAL_NVIC_EnableIRQ(TIM7_IRQn);
	
}

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */

  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{ 
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
