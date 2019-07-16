#include "sram.h"


//初始化外部SRAM
void FSMC_SRAM_Init(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
	FSMC_NORSRAMInitTypeDef        FSMC_NORSRAMInitStructure;
	FSMC_NORSRAMTimingInitTypeDef  FSMC_ReadWriteNORSRAMTiming; 

	//PD,PE-FSMC_DATA 	  PF,PG-FSMC_A
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD | RCC_APB2Periph_GPIOE  
	                      | RCC_APB2Periph_GPIOF|RCC_APB2Periph_GPIOG, ENABLE);
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_FSMC, ENABLE);

	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_10;	  //FSMC_NE3 PG10
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_Init(GPIOG, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_0|GPIO_Pin_1;	  //FSMC_NBL0-1 PE0	PE1
	GPIO_Init(GPIOE, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_4|GPIO_Pin_5;	  //FSMC_NOE,FSMC_NWE PD4 PD5
	GPIO_Init(GPIOD, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = (GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_8  
								  | GPIO_Pin_9 | GPIO_Pin_10 |GPIO_Pin_11
								  | GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14
								  | GPIO_Pin_15 );
	GPIO_Init(GPIOD, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = (GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9
	                               | GPIO_Pin_10 | GPIO_Pin_11 | GPIO_Pin_12
								   | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15);
	GPIO_Init(GPIOE, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = (GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2  
								  | GPIO_Pin_3 | GPIO_Pin_4 |GPIO_Pin_5
								  | GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14
								  | GPIO_Pin_15 );
	GPIO_Init(GPIOF, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = (GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2  
								  | GPIO_Pin_3 | GPIO_Pin_4 |GPIO_Pin_5);
	GPIO_Init(GPIOG, &GPIO_InitStructure);
 	
 	  
 	FSMC_ReadWriteNORSRAMTiming.FSMC_AddressSetupTime = 0x00;	 //??????(ADDSET)?1?HCLK 
	FSMC_ReadWriteNORSRAMTiming.FSMC_AddressHoldTime = 0x00;	 //??????(ADDHLD)??A???	
	FSMC_ReadWriteNORSRAMTiming.FSMC_DataSetupTime = 0x08;		 ////??????(DATAST)?9?HCLK 	 	 
	FSMC_ReadWriteNORSRAMTiming.FSMC_BusTurnAroundDuration = 0x00;
	FSMC_ReadWriteNORSRAMTiming.FSMC_CLKDivision = 0x00;
	FSMC_ReadWriteNORSRAMTiming.FSMC_DataLatency = 0x00;
	FSMC_ReadWriteNORSRAMTiming.FSMC_AccessMode = FSMC_AccessMode_A;	 //??A 

	FSMC_NORSRAMInitStructure.FSMC_Bank = FSMC_Bank1_NORSRAM3;	 //使用Bank1-3区
	FSMC_NORSRAMInitStructure.FSMC_DataAddressMux = FSMC_DataAddressMux_Disable; 
	FSMC_NORSRAMInitStructure.FSMC_MemoryType = FSMC_MemoryType_SRAM;
	FSMC_NORSRAMInitStructure.FSMC_MemoryDataWidth = FSMC_MemoryDataWidth_16b;
	FSMC_NORSRAMInitStructure.FSMC_BurstAccessMode = FSMC_BurstAccessMode_Disable;
	FSMC_NORSRAMInitStructure.FSMC_WaitSignalPolarity = FSMC_WaitSignalPolarity_Low;
	FSMC_NORSRAMInitStructure.FSMC_AsynchronousWait = FSMC_AsynchronousWait_Disable;
	FSMC_NORSRAMInitStructure.FSMC_WrapMode = FSMC_WrapMode_Disable;
	FSMC_NORSRAMInitStructure.FSMC_WaitSignalActive = FSMC_WaitSignalActive_BeforeWaitState;
	FSMC_NORSRAMInitStructure.FSMC_WriteOperation = FSMC_WriteOperation_Enable;	//?????? 
	FSMC_NORSRAMInitStructure.FSMC_WaitSignal = FSMC_WaitSignal_Disable;

	FSMC_NORSRAMInitStructure.FSMC_ExtendedMode = FSMC_ExtendedMode_Disable; //读写使用相同的时序
	FSMC_NORSRAMInitStructure.FSMC_WriteBurst = FSMC_WriteBurst_Disable;  
	FSMC_NORSRAMInitStructure.FSMC_ReadWriteTimingStruct = &FSMC_ReadWriteNORSRAMTiming;
	FSMC_NORSRAMInitStructure.FSMC_WriteTimingStruct = &FSMC_ReadWriteNORSRAMTiming; //??????
	FSMC_NORSRAMInit(&FSMC_NORSRAMInitStructure); 

	FSMC_NORSRAMCmd(FSMC_Bank1_NORSRAM3, ENABLE);		
}

//FSMC_SRAM写函数
//pbuf：写入的数据
//writeaddr：写入的数据的起始地址
//len：写入数据的长度
void FSMC_SRAM_WriteBuffer(u8* pBuffer,u32 WriteAddr,u32 n)
{
	WriteAddr = WriteAddr&0x3FFFFF;
	for(;n!=0;n--)  
	{
		*(u8*)(Bank1_SRAM3_ADDR+WriteAddr)=*pBuffer++;	 		
		WriteAddr++;
	}		
}

//FSMC_SRAM读函数
//pbuf：保存读的数据
//readaddr：读取数据的起始地址
//len：读数据的长度
void FSMC_SRAM_ReadBuffer(u8* pBuffer,u32 ReadAddr,u32 n)
{
	ReadAddr = ReadAddr&0x3FFFFF;
	for(;n!=0;n--)  
	{
		*pBuffer++=*(u8*)(Bank1_SRAM3_ADDR+ReadAddr);    
		ReadAddr++;
	}		
}

//SRAM写测试，写一个字节
//dat：写入的数据
//wirte_addr：写入的地址
 

//SRAM读测试，读一个字节
//read_addr：读取的地址

