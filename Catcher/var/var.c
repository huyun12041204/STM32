#include "var.h"





//

u16 TIM3CLK;
u16 TIM3Count;



//Í¨µÀ

u32 u32CLKLen;
u32 u32SendLen;
u32 u32SaveLen;

u8 _USB_SendBuf[512];
u8 _SD_SaveBuf[_Max_SD_Save];



u8 _Pre_Pin_Statue;
u8 _Cur_Pin_Statue;

u8 Sended = 0;

