#include "var.h"

const char u8Information[8] = {0x00,0x11,0x22,0x33,0x44,0x55,0x66,0x77 };

//当前CLKNumber
uint64_t u64CurCLK;
//之前CLKNumber
uint64_t u64PreCLK;

//TIM2 的计数器
uint32_t count;


//通道

u32 u32CLKLen;
u32 u32SendLen;

u8 _USB_SendBuf[64];

u8 _Pre_Pin_Statue;
u8 _Cur_Pin_Statue;


u8 Sended = 0;