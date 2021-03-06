#include "operation.h"


extern TIM_HandleTypeDef htim1;
extern TIM_HandleTypeDef htim2;
extern TIM_HandleTypeDef htim3;
extern TIM_HandleTypeDef htim4;
extern TIM_HandleTypeDef htim5;
extern TIM_HandleTypeDef htim7;

extern USBD_HandleTypeDef hUsbDeviceHS;
extern SD_HandleTypeDef hsd1;

#ifdef __Test_FATFS
uint32_t byteswritten;                /* File write counts */ 
uint32_t bytesread;                   /* File read counts */ 
uint8_t wtext[] = "H743_Cat Start \r\n"; /* File write buffer */ 
uint8_t rtext[100];                     /* File read buffers */ 
char filename[] = "Bit00000.bits"; 

#endif

char fName[] = "Bit00000.bits"; 
#ifdef __Test_FATFS



void Test_FATFS1()
{
	retSD = f_mount(&fs, "", 0); 
	if(retSD) 
		printf(" mount error : %d \n",retSD); 

	retSD = f_open(&fil, filename, FA_CREATE_ALWAYS | FA_WRITE); 
	if(retSD) 
		printf(" open file error : %d\n",retSD); 

	retSD = f_write(&fil, wtext, sizeof(wtext), (void *)&byteswritten); 
    if(retSD) 
        printf(" write file error : %d \n",retSD);
		
	retSD = f_write(&fil, wtext, sizeof(wtext), (void *)&byteswritten); 
    if(retSD) 
        printf(" write file error : %d \n",retSD);
		
		    retSD = f_write(&fil, wtext, sizeof(wtext), (void *)&byteswritten); 
    if(retSD) 
        printf(" write file error : %d \n",retSD);

	

	retSD = f_close(&fil); 
}

	void Test_FATFS()
	{
//		Test_FATFS1();
		
		    printf("\n ****** FatFs Example ******\n"); 
    /*##-1- Register the file system object to the FatFs module ##############*/ 
    retSD = f_mount(&fs, "", 0); 
    if(retSD) 
    { 
        printf(" mount error : %d \n",retSD); 
        Error_Handler(); 
    } 
    else 
        printf(" mount sucess!!! \n"); 
    /*##-2- Create and Open new text file objects with write access ######*/ 
    retSD = f_open(&fil, filename, FA_CREATE_ALWAYS | FA_WRITE); 
    if(retSD) 
        printf(" open file error : %d\n",retSD); 
    else 
        printf(" open file sucess!!! \n"); 
    /*##-3- Write data to the text files ###############################*/ 
    retSD = f_write(&fil, wtext, sizeof(wtext), (void *)&byteswritten); 
    if(retSD) 
        printf(" write file error : %d \n",retSD);  
    else 
    { 
        printf(" write file sucess!!! \n"); 
        printf(" write Data : %s\n",wtext); 
    } 
		
		    retSD = f_write(&fil, wtext, sizeof(wtext), (void *)&byteswritten); 
    if(retSD) 
        printf(" write file error : %d \n",retSD);  
    else 
    { 
        printf(" write file sucess!!! \n"); 
        printf(" write Data : %s\n",wtext); 
    } 


    /*##-4- Close the open text files ################################*/ 
    retSD = f_close(&fil); 

    if(retSD) 
        printf(" close error : %d\n",retSD); 
    else 
        printf(" close sucess!!! \n"); 

    /*##-5- Open the text files object with read access ##############*/ 
    retSD = f_open(&fil, filename, FA_READ); 

    if(retSD) 
        printf(" open file error : %d\n",retSD); 
    else 
 printf(" open file sucess!!! \n"); 

    /*##-6- Read data from the text files ##########################*/ 
    retSD = f_read(&fil, rtext, sizeof(rtext), (UINT*)&bytesread); 
    if(retSD) 
        printf(" read error!!! %d\n",retSD); 
    else 
    { 
        printf(" read sucess!!! \n"); 
        printf(" read Data : %s\n",rtext); 

    } 

    /*##-7- Close the open text files ############################*/ 

    retSD = f_close(&fil); 
    if(retSD)   
        printf(" close error!!! %d\n",retSD); 
    else 
        printf(" close sucess!!! \n"); 
    /*##-8- Compare read data with the expected data ############*/ 
    if(bytesread == byteswritten) 
        printf(" FatFs is working well!!!\n"); 


	
		
	}
	

	


#endif

#ifdef __USE_SD_SAVE
	

	
#endif
	
	
	void GetCLKNumber ()
	{
		


		
		if(iExtCLK != Pin_CLK)
		{
					TIMECNT  = TIM7->CNT + uInterHigh;
		 
					TIM7->CNT   = 0;
			    uInterHigh  = 0;
		}
		else
		{

			TIMECNT =  TIM5->CNT;
			//此处写成1 是应为此时要包含自己的修改寄存器的时间	
			TIM5->CNT = 1;
						
		}
		
		
	}
	
	void SetCLKBuff(u8 __buff,u32 __offset)
	{
		u8CLKBuff[__offset&_Max_CLK_Buff] = __buff;	
	}
	u8 GetCLKBuff(u32 __offset)
	{
		return  u8CLKBuff[__offset&_Max_CLK_Buff];	
	}



	u8 __GetDeltaCLKBufferLen(u32 __TIMCNT)
	{

		u8 __ClkLen  = 0;
		
		if(__TIMCNT < 0x100)
			__ClkLen =1;
		else if(__TIMCNT < 0x10000)
			__ClkLen =2;
		else 
			__ClkLen = 3;

		return __ClkLen;

	}
	
	void SaveVccEvent(u16 ___vcc)
	{
			
		SetCLKBuff(0xFA       ,VCCEvent); 
		SetCLKBuff(___vcc&0xFF  ,VCCEvent+2); 
		SetCLKBuff(___vcc>>8,VCCEvent+1); 
		
		
		VCCSaved = __Completion_state;
		
	}


	void SaveCLkNumber(u8 __Pin)
	{

		
		u32 __CurOffset;
		u8  __ClkLen   = __GetDeltaCLKBufferLen(TIMECNT);
		u8 AddLe = 1; 
		
			
		__CurOffset    = u32CLKLen;

		
		//此处需要预先流出 但前计算出的长度,避免 不同中断里面的冲突
		u32CLKLen     += (__ClkLen+AddLe);	 
		if(VCCSaved == __Completion_state)
			u32ReadLen  = u32CLKLen;
		
		//保存当前各个PIN 的状态,和后续CLK buffer 长度
		SetCLKBuff(__Pin|__ClkLen,__CurOffset); 

		//保存最低位
		SetCLKBuff(TIMECNT&0xFF,__CurOffset+1);
		
		if(__ClkLen > 1) SetCLKBuff((TIMECNT>>8 )&0xFF       ,__CurOffset+2); 
		else return;
		
		
		if(__ClkLen > 2) SetCLKBuff((TIMECNT>>16 )&0xFF     ,__CurOffset+3);
		else return;
	
	 	 
			
	}
	
	//保存等待数值
	void SaveWaitTime(u8 __Pin)
	{

		
		u32 __CurOffset;
		
			
		__CurOffset    = u32CLKLen;
			u32CLKLen   += 4;	 
		
		//保存当前各个PIN 的状态,和后续CLK buffer 长度
		SetCLKBuff(__Pin|3,__CurOffset); 

		//保存最低位
		SetCLKBuff(0xFF,__CurOffset+1);
		SetCLKBuff(0xFF,__CurOffset+2);
		SetCLKBuff(0xFF,__CurOffset+3);

	
			
	}

	u8   GetPinValue  (void)
	{   u8 __Pin = 0;
		
		
		 if((GPIOE->IDR & GPIO_PIN_9) != 0x00)__Pin |= Pin_IO ;
		 if((GPIOA->IDR & GPIO_PIN_15) != 0x00)__Pin|= Pin_VCC;
		 if((GPIOB->IDR & GPIO_PIN_4) != 0x00)__Pin |= Pin_RST;
		// if((GPIOE->IDR & GPIO_PIN_0) != 0x00)__Pin |= Pin_CLK;

		return __Pin |= iExtCLK;		
	}
	
	
	
void SwitchTime(void)
{
	
 if((iExtCLK == 0)&&((GPIOA->IDR & GPIO_PIN_15) != 00))
 {
	 if((GPIOA->IDR & GPIO_PIN_4)!= 0)
	 { 
			GetCLKNumber();
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
			 GetCLKNumber();
       SaveCLkNumber( GetPinValue());	 
			 TIM7->CNT   = 0;
			 uInterHigh  = 0;
			 HAL_TIM_Base_Start_IT(&htim7);
			 iExtCLK = 0;
			 
		}
	}
}
	
	
	
	
	
	void _CLKBuff_Send()
	{
	
		u8 i;
		u8 TempBufer[_MAX_Buffer_Send];


		u32 __Len = u32ReadLen - u32SendLen;
		if(__Len >_MAX_Buffer_Send) __Len = _MAX_Buffer_Send;

		for (i = 0 ; i< __Len ; i++)
			TempBufer[i] = GetCLKBuff(u32SendLen + i);

		//此处内部会判断USB是否发送完成.如果没有返回 USBD_BUSY
		if (CDC_Transmit_HS(TempBufer, __Len) == USBD_OK) u32SendLen += __Len;
		//if (_packet_Send(TempBufer, __Len) == USBD_OK) u32SendLen += __Len;

	
		 
	}
	

	
	
	
	void PrintfSDInformation()
	{
//		switch(hsd1.SdCard.CardType)
//		{
//		case STD_CAPACITY_SD_CARD_V1_1:printf("Card Type:SDSC V1.1\r\n");break;
//		case STD_CAPACITY_SD_CARD_V2_0:printf("Card Type:SDSC V2.0\r\n");break;
//		case HIGH_CAPACITY_SD_CARD:printf("Card Type:SDHC V2.0\r\n");break;
//		case MULTIMEDIA_CARD:printf("Card Type:MMC Card\r\n");break;
//		}
		
		if(hsd1.State !=  0)
		{
			uint64_t uSize = hsd1.SdCard.LogBlockNbr*hsd1.SdCard.LogBlockSize;
			uSize          = uSize / (1024*1024);
			printf("SD Size : %d MB\n " ,(u32)uSize);
		}
	}
	
	#if __USE_FATFS
	
		u16 GetFileNumber()
	{
		DIR __dpp;
		FILINFO __file;
		u16 uNum = 0;
		//打开目录
		retSD = f_opendir (&__dpp, "");
		if(retSD) 
			return WriteDirFaild;
		
		while((f_readdir (&__dpp,&__file)== FR_OK)&&
			    (__file.fname[0]!= 0))
		{
			uNum++;
		}
			
		return uNum;
		
		
	}
	
	u8 SDIsReadForSave()
	{
		
		char FileH[] = "<Bits file>";


		u16 uFileNum = 0;
		//DIR dpp;
		if(hsd1.State ==0 )
			return SDNotExist;

		retSD = f_mount(&fs, "", 0); 
		if(retSD) 
			return MountFaild;
		
		
		//查询文件数目
	  uFileNum     =  GetFileNumber();	
		fName[3]  =  uFileNum/10000       + 0x30;
		fName[4]  =  ((uFileNum/1000)%10) + 0x30;
		fName[5]  =  ((uFileNum/100)%10)  + 0x30;
		fName[6]  =  ((uFileNum/10)%10)   + 0x30;
		fName[7]  =  (uFileNum%10)        + 0x30;
		
		//创建并且打开对应文件
		retSD = f_open(&fil, fName, FA_CREATE_ALWAYS | FA_WRITE); 
		if(retSD) 
			return OpenFileFaild;

		retSD = f_write(&fil, FileH, sizeof(FileH), (void *)&Bytes); 

		if(retSD) 
			return WriteFileFaild;
		
		retSD = f_close(&fil); 
		
		return FileIsRead;

	}
	

	
	
	void Save1LineCLKBuffer()
	{
		u8  Buf[64];
		u8 i;
		u32 __Len = u32ReadLen - u32SaveLen;
		if (__Len <= 0)
			return;

		if (__Len>64)
			__Len = 64;
		
		for(i = 0 ; i < __Len ; i++)
			Buf[i]= GetCLKBuff(u32SaveLen+ i) ;
		
		retSD = f_open(&fil, fName, FA_CREATE_ALWAYS | FA_WRITE); 

		retSD = f_write(&fil, Buf, __Len, (void *)&Bytes); 
		
		retSD = f_close(&fil); 
		
		if(!retSD)
			u32SaveLen += __Len;
	}
	

#endif

		