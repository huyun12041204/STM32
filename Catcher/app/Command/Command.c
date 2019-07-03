#include "Command.h"
#include "system.h"
#include "String.h"
#include "var.h"
#include "sd.h"
#include "usart.h"	 
#include "dma.h"
#include "sram.h"

void _SendBuf_Init(void)
{
	 u16SendCurSector= 0;
	 u32SendSector   = 0;
}

void _Command_Init(void)
{
	memset(u8Command,0, sizeof(u8Command));
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
// Method:    GetSectorCount
// FullName:  ��ȡ�Ѿ��洢�����ݵĿ������� �Լ������������ ����
// Access:    public 
// Returns:   u16 �ɹ�����0x9000;����Ϊʧ��;
// Qualifier: 
// XXXXXXXX XXXXXXXX ��ʾSector��Ŀ��XXXX  Ϊ���������RAM�ڵĳ���
// Parameter: u8 * u8Buf���� ����󳤶ȣ��˴�Ӧ�ÿ��Դﵽ
// bufLen Ӧ�÷��� 10��10���ƣ�
// Parameter: u8 * bufLen
//************************************
u16 GetSectorCount(u8* u8Buf, u16* bufLen)
{
	u8 i;
	u8 Limit;
	*bufLen = 0;

	//buf���ȴ��� ����6700
	//if (sizeof(u8Buf)<10)
	//{
	//	return _Com_WrongLength;
	//}

	memset(u8Buf,0,10);
	Limit = (_Max_Sector_Count > 0xFFFFFFFF ? 0 : 4);

	for(i = 8; i > Limit;i++)
	{
		u8Buf[i - 1] = ((u32SavedSector - _Start_Sector) >> ((8 - i) * 8)) & 0xFF;
	}
	 
	u8Buf[8] = u16Save2SDTempLen >> 8;
	u8Buf[9] = u16Save2SDTempLen&0xFF;
	*bufLen = 10;

//	printf("%d\n", u32SavedSector);
//	printf("%d\n", u16Save2SDTempLen);
	return _Com_Success;
}



u16 ReaduSectorData(u32 uSector, u16 u16Offset, u8* u8buf, u16 *u16bufLen)
{

	u8 u8Ret = 0;
	if (u16Offset != 0)
	{
		u8Ret = SD_ReadDisk(u8buf, uSector, 1);

		if (u8Ret != 0)
			return _Com_ReadSDFailed;

		memcpy(u8buf, u8buf + u16Offset, _MaxSectorSize - u16Offset);

		*u16bufLen = _MaxSectorSize - u16Offset;
	}
	else
	{
		u8Ret = SD_ReadDisk(u8buf, uSector, 1);
		delay_us(30);
		*u16bufLen = _MaxSectorSize;
	}



	return _Com_Success;
}
u16 ReadSector(u8* u8Buf, u16* bufLen)
{
	u8 i;
	u16 u16Offset;
	u32 u32Sector = 0;
	uint64_t CurrentSramOffset = SramOffset;
	

	u16UsartSendBufLength = 0;
	//P3 ���󷵻�6CXX
	if (u8Command[_Com_P3] != 0x08)
		return _Com_WrongP3+0x08;

	u16Offset = u8Command[_Com_P1] * 0x100 + u8Command[_Com_P2];

	//ƫ�������������С �򷵻� 6B00
	if (u16Offset>= _MaxSectorSize)
		return _Com_WrongOffset;

	for (i = 4; i < 8 ; i++)
		u32Sector = (u32Sector << (i-4)*8) + u8Command[i+_Com_Data];	

	
	#ifdef __2Sram
	
	if((uint64_t)( u32Sector*512+512) <= CurrentSramOffset)
	{
		*bufLen = 512-u16Offset;
		FSMC_SRAM_ReadBuf(u8Buf, (u32Sector*512+u16Offset) ,*bufLen);	
	
	}
	else
	{
		 *bufLen = CurrentSramOffset -(uint64_t)(u32Sector*512+u16Offset);
		 FSMC_SRAM_ReadBuf(u8Buf, (u32Sector*512+u16Offset) , *bufLen );

	}
	
		return _Com_Success;
	

	#else
	
		u32Sector = u32Sector + _Start_Sector;

	//��������ȡ����
	if (u32Sector < u32SavedSector)
		return ReaduSectorData(u32Sector, u16Offset, u8Buf, bufLen);
	else if ((u32Sector == u32SavedSector) &&
		     (u16Offset<u16Save2SDTempLen))
	{
		*bufLen = u16Save2SDTempLen - u16Offset;
		memcpy(u8Buf, SDTemp+u16Offset, *bufLen);
		return _Com_Success;
	}else return _Com_OverLimit;
	
	
	#endif
	
	
	

	


	
	

	
}


//************************************
// Method:    Excute_Command
// FullName:  Excute_Command
// Access:    public 
// Returns:   void
// Qualifier: ִ��USARTָ��
// Parameter: void
//************************************
void Excute_Command(void)
{
	u16 u16SW;
	u16UsartSendBufLength = 0;
	
	if(u8Command[_Com_CLA] != 0xFE)
	{
		u16SW = _Com_WrongClass;	
	}

	switch (u8Command[_Com_INS])
	{
	case _INS_GetInfo:
		u16UsartSendBufLength = 8;
		memcpy(u8UsartSendBuf, u8Information, u16UsartSendBufLength);
		u16SW = _Com_Success;
		break;

	case _INS_GetSectorCount:
		u16SW = GetSectorCount(u8UsartSendBuf, &u16UsartSendBufLength);
		if (u16SW != _Com_Success)
			u16UsartSendBufLength = 0;
		break;

	case _INS_ReadSector:
		u16SW = ReadSector(u8UsartSendBuf, &u16UsartSendBufLength);
		if (u16SW != _Com_Success)
			u16UsartSendBufLength = 0;
		break;

	default:
		u16UsartSendBufLength = 0;
		u16SW = _Com_WrongIns;
		break;
	}
	
	u8UsartSendBuf[u16UsartSendBufLength]   = (u16SW>>8)&0xFF;
	u8UsartSendBuf[u16UsartSendBufLength+1] = u16SW&0xFF;	
	u16UsartSendBufLength += 2;	
		
	USART_DMACmd(USART1,USART_DMAReq_Tx,ENABLE);  //ʹ�ܴ���1��DMA����     
	DMA_Enable(DMA1_Channel4,u16UsartSendBufLength);     //��ʼһ��DMA���䣡
	_Command_Init();
}

void Install_Command(u8 _u8CommandByte)
{

	u8Command[u8RecLen] =_u8CommandByte;
	u8RecLen +=1;
	 // LCD_Dislay_Printf(_u8CommandByte );
	//  SendCharData(_u8CommandByte);
	
	if(u8RecLen < 5)
		return;
	else if(u8RecLen == 5+ u8Command[_Com_P3])
	{
		USART_ITConfig(USART1, USART_IT_RXNE, DISABLE);
		Excute_Command();		
//		u8RecLen = 0;
	}

	
	
	
	
}
