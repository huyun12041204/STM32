

#ifndef _Command_H
#define _Command_H
#include "system.h"
#include "SysTick.h"

#define _Com_CLA 0
#define _Com_INS 1
#define _Com_P1 2
#define _Com_P2 3
#define _Com_P3 4
#define _Com_Data 5
#define _Com_Tag 0xFE

#define _INS_GetInfo         02
#define _INS_GetSectorCount  0xC0
#define _INS_ReadSector      0xB0




#define _Com_Success     0x9000
#define _Com_WrongLength 0x6700


#define _Com_WrongOffset 0x6B00
#define _Com_WrongP1     0x6B00
#define _Com_WrongP2     0x6B00
#define _Com_WrongP3     0x6C00
#define _Com_WrongIns    0x6D00
#define _Com_WrongClass  0x6E00

#define _Com_ReadSDFailed    0x6F01
#define _Com_ReadFlashFailed 0x6F02
#define _Com_ReadRamFailed   0x6F03

#define _Com_OverLimit      0x9850



#define _Start_Sector      20


//************************************
// Method:    GetSectorCount
// FullName:  GetSectorCount
// Access:    public 
// Returns:   u16 成功返回0x9000;其他为失败;
// Qualifier: 
// XXXXXXXX XXXXXXXX 表示Sector数目，XXXX  为非整块存在RAM内的长度
// Parameter: u8 * u8Buf返回 的最大长度，此处应该可以达到
// bufLen 应该返回 10（10进制）
// Parameter: u16 * bufLen
//************************************
#define _Max_Sector_Count 0xFFFFFFFF

u16 GetSectorCount(u8* u8Buf, u16* bufLen);


u16 ReaduSectorData(u32 uSector, u16 u16Offset, u8* u8buf, u16 *u16bufLen);

//************************************
// Method:    ReadSector
// FullName:  读取扇区数据，也可以读取存储在Ram内的数据
// Access:    public 
// Returns:   u16 成功返回0x9000;其他为失败;
// Qualifier:
// Parameter: u8 * u8Buf
// Parameter: u16 * bufLen
//************************************
u16 ReadSector(u8* u8Buf, u16* bufLen);
void Excute_Command(void);
void _SendBuf_Init(void);
void _Command_Init(void);
void SendCharData(const char cData);
void Install_Command(u8 _u8CommandByte);

#endif
