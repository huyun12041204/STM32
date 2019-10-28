#include "command.h"



u16 __GetSize()
{
	
	_GetBitsBuf[0] = (u32CLKLen/0x1000000)&0xFF;
	_GetBitsBuf[1] = (u32CLKLen/0x10000)&0xFF;
	_GetBitsBuf[2] = (u32CLKLen/0x100) &0xFF;	
	_GetBitsBuf[3] =  u32CLKLen      &0xFF;	
	
	_GetBitsBuf[4] = (u32SendLen/0x1000000)&0xFF;
	_GetBitsBuf[5] = (u32SendLen/0x10000)  &0xFF;
	_GetBitsBuf[6] = (u32SendLen/0x100)    &0xFF;	
	_GetBitsBuf[7] =  u32SendLen           &0xFF;	
	 
	if (CDC_Transmit_HS(_GetBitsBuf, 8) == USBD_OK)
		return _SUCCESS;
	
	
	return _Wrong_UNKNOWN;
}

u16 __GetBits(u8 u8P3)
{
	
	
	u16 i ;
	u32 __Delta = u32CLKLen - u32SendLen;

	if(u8P3 == 0) _GetBitsLen = _Max_Bits_Buff;
	else _GetBitsLen = u8P3;
	
	if(__Delta < _GetBitsLen) _GetBitsLen= __Delta;
	
	_GetBitsOff = 0;
	
	
	for(i = 0 ; i < _GetBitsLen ; i++ )
		_GetBitsBuf[i] = GetCLKBuff(u32SendLen + i);
		
	
	return _SUCCESS;
	
}


void __GetBits_Send()
{
	

  u8 __SendLen;
	if(_GetBitsLen == 0) return;
	if(_GetBitsLen > 0x40) __SendLen = 64;
	else                   __SendLen = _GetBitsLen;
	
		
	if (CDC_Transmit_HS(_GetBitsBuf+_GetBitsOff, __SendLen) == USBD_OK) 
	{
		u32SendLen  += __SendLen;
		_GetBitsOff += __SendLen;
	  _GetBitsLen -= __SendLen;
			
	}
	if(_GetBitsLen == 0)_GetBitsOff = 0;
			 
}

u16 Excute_Command(u8* u8Command,u16 u16Length)
{
	u16 u16Ret = _Wrong_UNKNOWN;
	if(u8Command[__CLA]!= _USE_CLA)
		return _Wrong_CLA;
	
	
	switch(u8Command[__INS])
	{
		case _GET_SIZE  : u16Ret = __GetSize()               ; break;
		case _GET_DATAS :	u16Ret = __GetBits(u8Command[__P3]); break;
		case _INIT_BITS : u16Ret = _SUCCESS; 
		                  u32CLKLen  = 0;
		                  u32SendLen = 0; 
		                  u32SaveLen = 0;break;
		default: u16Ret =  _Wrong_INS;
	}
	
	return u16Ret;

}



