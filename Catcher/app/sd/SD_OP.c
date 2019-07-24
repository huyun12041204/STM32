#include "sd.h"
#include "SD_OP.h"
#include "SysTick.h"

u8 SD_SAVE_BUFF[512];

u8 SD_Write(u8* u8Input,u32 uWriteAddr,u32 u32Length)
{
	
	 u8 u8Ret;
	 u32 u32Sector = 0;
	 u16 u16PreSave= 0;
	 u16 u16Offset = 0;
	 u32 u32Batch= 0;
	
	
	//计算当前的扇区
	u32Sector = uWriteAddr/512;
	


	//当不时512整数的地址时，应该先读取当前扇区数据
	
	u16Offset = uWriteAddr%512;
	if(u16Offset!= 0)
	{
		 
		SD_ReadDisk(SD_SAVE_BUFF,u32Sector,1);
		//将数据补足512，重新写入；
		
		if(u32Length < (512 - u16PreSave))
		{
			memcpy(SD_SAVE_BUFF+u16Offset,u8Input,u32Length);
			u16PreSave =  u32Length;
		}
		else
		{	
		
	  	memcpy(SD_SAVE_BUFF+u16Offset,u8Input,512-u16Offset);
			u16PreSave += (512-u16Offset);
			
		}
		
		u8Ret = SD_WriteDisk(SD_SAVE_BUFF,u32Sector,1);
		if(u8Ret!=0)
			return 1;
		u32Sector += 1;
			
	}
	
	//检查当前可以批量写入的数据长度

	u32Batch =  u32Length - u16PreSave;
	u32Batch = (u32Batch/512);
	if(u32Batch != 0)
	{
			u8Ret = SD_WriteDisk(u8Input+u16PreSave,u32Sector,u32Batch);
    	if(u8Ret!=0)
		  	return 2;
	   u32Sector  += u32Batch;
	   u16PreSave += u32Batch*512;
		
	}

	//最后补齐后续没有写入的长度
	
	if(u16PreSave<u32Length )
	{
	    memset(SD_SAVE_BUFF,0x00,512);
	    memcpy(SD_SAVE_BUFF,u8Input+u16PreSave,512);
	 
	    u8Ret = SD_WriteDisk(SD_SAVE_BUFF,u32Sector,1);
	    if(u8Ret!=0)
			   return 3;
  }
	
	return 0;
	
}


u8 SD_Read(u8* u8Output,u32 uWriteAddr,u32 u32Length)
{
	
	u8 u8Ret;
	u32 u32Sector  = 0;
	u16 u16PreRead = 0;
	u32 u32Batch   = 0; 
	u16 u16Offset  = 0;
	
	

	//计算当前的扇区
	u32Sector = uWriteAddr/512;
	
	//当不时512整数的地址时，应该先读取当前扇区数据
	u16Offset = uWriteAddr%512;
	if(u16Offset!= 0)
	{
		u8Ret = SD_ReadDisk(SD_SAVE_BUFF,u32Sector,1);
		if(u8Ret!=0)
   		return 1;
		if(u32Length <= u16PreRead)
		{
			memcpy(u8Output,SD_SAVE_BUFF+u16Offset,u32Length);
			return 0;
		}
		else
			memcpy(u8Output,SD_SAVE_BUFF+u16Offset,512 - u16Offset);
		
		u16PreRead = 512 - u16Offset;
		u32Sector +=1;

	}
	
	u32Batch =  u32Length - u16PreRead;
	u32Batch = (u32Batch/512);
	if(u32Batch != 0)
	{
	
	u32Batch =  u32Length - u16PreRead;
	u32Batch = (u32Batch/512);
	u8Ret = SD_ReadDisk(u8Output+u16PreRead,u32Sector,u32Batch);
	if(u8Ret!=0)
		return 2;
	
	u32Sector  += u32Batch;
	u16PreRead += u32Batch*512;
}
	
	if(u16PreRead<u32Length )
	{
		  u8Ret =  SD_ReadDisk(SD_SAVE_BUFF,u32Sector,1);
			if(u8Ret!=0)
	    	return 3;
			memcpy(u8Output+u16PreRead,SD_SAVE_BUFF,u32Length-u16PreRead);
		

		
	}
	
  return u8Ret;
	
	
}
