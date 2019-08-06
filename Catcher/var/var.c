#include "var.h"





//TIM 1- 8 的状态，
u8 TIMxStatue = 0;



//
u32 TIM3Count;

u16 CurTIM3CLK;
u32 CurTIM3Count;

u16 preTIM3CLK;
u32 preTIM3Count;

u16 DeltaTIM3CLK;
u32 DeltaTIM3Count;






//发送数据，接受数据，存储数据长度

u32 u32CLKLen;
u32 u32SendLen;
u32 u32SaveLen;

//USB 发送和 存储使用

u8 _USB_SendBuf[512];
u8 _SD_SaveBuf[_Max_SD_Save];



u8 _Cur_Pin_Statue;

//此处表示从SRAM读取,和SD读取时候的切换
//由于读取SD需要512整数倍，而发送只能64整数倍，
//确保发送正确，此处需要之前一条从何处读取
u8 bSramRead = 1;

u32 u32Second;