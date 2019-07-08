

#ifndef _Var_H
#define _Var_H

#define  _Mode_V2

#include "System.h"


//#define  _2Channel 
#define __2Sram
#define _USE_USB

#define _MaxCLKCount 1000
#define _MaxCommandLen 0x15

#define _MaxSectorSize  512
#define _MaxUsartSendSize 600

//存储 CLK 间隔的Ram变量
extern u8  u8CLK[_MaxCLKCount];
//当前CLKNumber
extern uint64_t u64CurCLK;
//之前CLKNumber
extern uint64_t u64PreCLK;

//当前应该进入中断类别
extern u16       u16EXIT_Type;
extern u8        u8Clk_EXIT_TYPE;

//TIM2 的计数器
extern uint32_t count;

//存储CLK 的数目以及发送数目, 此处用于实时传送的时候计数的
extern u16 uCLKCount;
extern u16 uSendCLKCOunt;


//最后一包的发送长度，0-512
extern u16 u16SendCurSector;

//已经发送的完整块数
extern u32 u32SendSector   ;

// 未满512长度的输入先放在Ram内;
extern u8 SDTemp[512];

//未满512 存在Ram内的长度
extern u16 u16Save2SDTempLen;

//已经存储在 SD 卡内的完整块数
extern u32 u32SavedSector;

//设备信息
extern const char u8Information[8] ;


//用来存储接受指令的buf
extern u8 u8Command[_MaxCommandLen];
//用来存储接受指令的长度
extern u8 u8RecLen;
//指令的结果
extern u8 u8CommandRet;

//用于读SD 数据后发送的全局变量，应该使用DMA USART 方式发送
extern u8 u8UsartSendBuf[_MaxUsartSendSize];

extern u16 u16UsartSendBufLength;
#endif



#ifdef _2Channel
//存储 CLK 间隔的Ram变量
extern u8  u8CLKT[_MaxCLKCount][2];
extern u16 uCount[2];
extern u8  u8Channel;
#endif


#ifdef __2Sram
//测试使用
extern uint64_t SramOffset;
#endif


#ifdef _Mode_V2

extern  u8 _Pre_Pin_Statue;
extern  u8 _Cur_Pin_Statue;

#endif


