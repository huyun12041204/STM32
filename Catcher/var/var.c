#include "var.h"





//TIM 1- 8 的状态，
u8 TIMxStatue = 0;

u32 PreTIM2CLK;
u32 CurTIM2CLK;

//
u32 TIM3Count;

u16 CurTIM3CLK;
u32 CurTIM3Count;

u16 preTIM3CLK;
u32 preTIM3Count;

u16 DeltaTIM3CLK;
u32 DeltaTIM3Count;


////用来计算频率
//u16 TIM5Count;
//u8  u8CC1; // 用来捕获接受中断此处
//u32 u321st;
//u32 u322nd;




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

u16 u16Vol;
u16 u16Fre;
u16 u16TFre[10];

u16 u16DisVol;
u16 u16DisFre;

u8 u8FreTime;

