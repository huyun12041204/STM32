#include "var.h"




//存储 CLK 间隔的Ram变量
u8  u8CLK[_MaxCLKCount];
//当前CLKNumber
uint64_t u64CurCLK;
//之前CLKNumber
uint64_t u64PreCLK;

//当前应该进入中断类别
u16       u16EXIT_Type;
u8        u8Clk_EXIT_TYPE;


//TIM2 的计数器
uint32_t count;


//通道

u16 uCLKCount;
u16 uSendCLKCOunt;


//最后一包的发送长度，0-512
u16 u16SendCurSector;

//已经发送的完整块数
u32 u32SendSector   ;

// 未满512长度的输入先放在Ram内;
u8 SDTemp[512];
u16 u16Save2SDTempLen;
u32 u32SavedSector;



u8 u8Command[_MaxCommandLen];
u8 u8RecLen;
u8 u8CommandRet;


u8 u8UsartSendBuf[_MaxSectorSize];
u16 u16UsartSendBufLength;

const char u8Information[8] = {0x00,0x11,0x22,0x33,0x44,0x55,0x66,0x77 };











