#include "var.h"

const char u8Information[8] = {0x00,0x11,0x22,0x33,0x44,0x55,0x66,0x77 };

//��ǰCLKNumber
uint64_t u64CurCLK;
//֮ǰCLKNumber
uint64_t u64PreCLK;

//TIM2 �ļ�����
uint32_t count;


//ͨ��

u32 u32CLKLen;
u32 u32SendLen;

u8 _USB_SendBuf[64];

u8 _Pre_Pin_Statue;
u8 _Cur_Pin_Statue;


u8 Sended = 0;