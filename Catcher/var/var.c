#include "var.h"






//

u16 TIM2CLK;
u16 TIM2Count;

u16 TIM3CLK;
u16 TIM3Count;



//通道

u32 u32CLKLen;
u32 u32SendLen;
u32 u32SaveLen;

u8 _USB_SendBuf[512];
u8 _SD_SaveBuf[_Max_SD_Save];



u8 _Pre_Pin_Statue;
u8 _Cur_Pin_Statue;

u8 Sended = 0;


//此处表示从SRAM读取,和SD读取时候的切换
//由于读取SD需要512整数倍，而发送只能64整数倍，
//确保发送正确，此处需要之前一条从何处读取
u8 bSramRead = 1;


SD_Error Status = SD_OK;
