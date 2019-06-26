#include "Command.h"
#include "usart.h"	 
#include "system.h"
u8 u8Command[5];
u8 u8RecLen;
u8 u8CommandRet;



//最后一包的发送长度，0-512
u16 u16SendCurSector;

//已经发送的完整块数
u32 u32SendSector   ;


//未满512 存在Ram内的长度
extern u16 u16Save2SDTempLen;

//已经存储在 SD 卡内的完整块数
extern u32 u32SavedSector;

//设备信息
const char u8Information[8] = {0x00,0x11,0x22,0x33,0x44,0x55,0x66,0x77 };


void _SendBuf_Init(void)
{
	 u16SendCurSector= 0;
	 u32SendSector   = 0;
}

void _Command_Init(void)
{
	memset(u8Command,0, 5);
	u8RecLen     = 0;
	//u8CommandRet = 0;

}

void SendCharData(const char cData)
{
	USART_SendData(USART1, cData);
	while (USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);

}
void _SendBuf2USART(const char* cBuf, u16 u16BufLen)
{
	u16 i;
	for (i=0 ; i< u16BufLen ; i++  )
		SendCharData(cBuf[i]);
}

	


//************************************
// Method:    Excute_Command
// FullName:  Excute_Command
// Access:    public 
// Returns:   void
// Qualifier: 执行USART指令
// Parameter: void
//************************************
void Excute_Command(void)
{
	if(u8Command[_Com_CLA] != 0xFE)
		goto Command_Finish;
	
		if(u8Command[_Com_INS] == _INS_GetInfo)
		{		
			_SendBuf2USART(u8Information, 8); 	 
			goto Command_Finish;
		}
		
		if (u8Command[_Com_INS] == _INS_GetSendSign)
		{
			if ((u32SavedSector > u32SendSector)||
				((u32SavedSector == u32SendSector)&&
				(u16Save2SDTempLen > u16SendCurSector)))
				SendCharData(0x01);
			else
				SendCharData(0x00);

			goto Command_Finish;
		}
		
		if (u8Command[_Com_INS] == _INS_GetBits)
		{
			//判断是否有数据需要发送
			if ((u32SavedSector > u32SendSector)||
				((u32SavedSector == u32SendSector)&&
				(u16Save2SDTempLen > u16SendCurSector)))
			{
				
				 ReadSendBuf();
				
			}

			

			goto Command_Finish;
		}
	

	Command_Finish:_Command_Init();
}

void Install_Command(u8 _u8CommandByte)
{
	
		u8Command[u8RecLen] =_u8CommandByte;
		u8RecLen +=1;
	 // LCD_Dislay_Printf(_u8CommandByte );
	//  SendCharData(_u8CommandByte);
		if(u8RecLen == 5)
		{
			LCD_Dislay_Printf("Excute data");
			Excute_Command();		
			u8RecLen = 0;
		}
	
	
}
