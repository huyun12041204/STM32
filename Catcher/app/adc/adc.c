#include "adc.h"

u16 ADCConvertedValue[30];//用来存放ADC转换结果，

void DMA1_Init(void)
{

    DMA_InitTypeDef DMA_InitStructure;
    NVIC_InitTypeDef  NVIC_InitStructure;
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);//使能时钟

    DMA_DeInit(DMA1_Channel1);    //将通道一寄存器设为默认值
    DMA_InitStructure.DMA_PeripheralBaseAddr  = ((u32)0x4001244C);          //该参数用以定义DMA外设基地址
    DMA_InitStructure.DMA_MemoryBaseAddr      = (u32)&ADCConvertedValue;   //该参数用以定义DMA内存基地址(转换结果保存的地址)
    DMA_InitStructure.DMA_DIR                 = DMA_DIR_PeripheralSRC;          //该参数规定了外设是作为数据传输的目的地还是来源，此处是作为来源
    DMA_InitStructure.DMA_BufferSize          = 30;                             //定义指定DMA通道的DMA缓存的大小,单位为数据单位。这里也就是ADCConvertedValue的大小
    DMA_InitStructure.DMA_PeripheralInc       = DMA_PeripheralInc_Disable;      //设定外设地址寄存器递增与否,此处设为不变 Disable
    DMA_InitStructure.DMA_MemoryInc           = DMA_MemoryInc_Enable;           //用来设定内存地址寄存器递增与否,此处设为递增，Enable
    DMA_InitStructure.DMA_PeripheralDataSize  = DMA_PeripheralDataSize_HalfWord;//数据宽度为16位
    DMA_InitStructure.DMA_MemoryDataSize      = DMA_MemoryDataSize_HalfWord;    //数据宽度为16位
    DMA_InitStructure.DMA_Mode                = DMA_Mode_Normal;                  //工作不在循环缓存模式
    DMA_InitStructure.DMA_Priority            = DMA_Priority_High;              //DMA通道拥有高优先级 分别4个等级 低、中、高、非常高
    DMA_InitStructure.DMA_M2M                 = DMA_M2M_Disable;                //使能DMA通道的内存到内存传输


    DMA_Init(DMA1_Channel1, &DMA_InitStructure);//根据DMA_InitStruct中指定的参数初始化DMA的通道
    DMA_Cmd(DMA1_Channel1, ENABLE);             //启动DMA通道一


    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);   //中断分组1
    NVIC_InitStructure.NVIC_IRQChannel = DMA1_Channel1_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);          // Enable the DMA Interrupt

    DMA_ITConfig(DMA1_Channel1, DMA_IT_TC, ENABLE); //使能DMA传输完成中断
}

void Adc_Init(void)
{
    ADC_InitTypeDef ADC_InitStructure;
    GPIO_InitTypeDef GPIO_InitStructure;
//    /*3个IO口的配置（PA0、PA1、PA2）*/
//    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
//    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
//    GPIO_Init(GPIOA, &GPIO_InitStructure);
//
//    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
//    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
//    GPIO_Init(GPIOA, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
    /*IO和ADC使能时钟*/
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1|RCC_APB2Periph_GPIOA,ENABLE);
    RCC_ADCCLKConfig(RCC_PCLK2_Div6);

    ADC_DeInit(ADC1);
    ADC_InitStructure.ADC_Mode               = ADC_Mode_Independent;
    ADC_InitStructure.ADC_ScanConvMode       = DISABLE;
    ADC_InitStructure.ADC_ContinuousConvMode = DISABLE; //连续转换
    ADC_InitStructure.ADC_ExternalTrigConv   = ADC_ExternalTrigConv_T1_CC1;
    ADC_InitStructure.ADC_DataAlign          = ADC_DataAlign_Right;
    ADC_InitStructure.ADC_NbrOfChannel       = 1;
    ADC_Init(ADC1, &ADC_InitStructure);

    ADC_ExternalTrigConvCmd(ADC1,ENABLE);	 
    // ADC_RegularChannelConfig(ADC1,ADC_Channel_0,1,ADC_SampleTime_1Cycles5);//通道一转换结果保存到ADCConvertedValue[0~10][0]
    //	ADC_RegularChannelConfig(ADC1,ADC_Channel_1,2,ADC_SampleTime_1Cycles5););//通道二转换结果保存到ADCConvertedValue[0~10][1]
    ADC_RegularChannelConfig(ADC1,ADC_Channel_2,1,ADC_SampleTime_239Cycles5);//通道三转换结果保存到ADCConvertedValue[0~10][2]


    ADC_DMACmd(ADC1, ENABLE);//开启ADC的DMA支持
    ADC_Cmd(ADC1, ENABLE);

    ADC_ResetCalibration(ADC1);
    while(ADC_GetResetCalibrationStatus(ADC1));
    ADC_StartCalibration(ADC1);
    while(ADC_GetCalibrationStatus(ADC1));

}

u16 Get_Vcc_Value()
{
    u8 i;
    u32 Vcc = 0;
	  u32 Min,Max;
	  Min = ADCConvertedValue[0];
  	Max = ADCConvertedValue[0];
    for(i =0 ; i<30 ; i++ )
	  {  
			if(ADCConvertedValue[i] > Max)
				Max = ADCConvertedValue[i];
			if(ADCConvertedValue[i] < Min)
				Min = ADCConvertedValue[i];
			Vcc += ADCConvertedValue[i];
		}
		Vcc = Vcc -( Max + Min);
    Vcc = (Vcc*3300)/4096;
		Vcc = Vcc /28;
    return (u16)Vcc/10*10;
}


