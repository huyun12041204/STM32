#include "var.h"





//


u16 TIM3Count;

u16 CurTIM3CLK;
u16 CurTIM3Count;

u16 preTIM3CLK;
u16 preTIM3Count;

u16 DeltaTIM3CLK;
u16 DeltaTIM3Count;


//ͨ��

u32 u32CLKLen;
u32 u32SendLen;
u32 u32SaveLen;

u8 _USB_SendBuf[512];
u8 _SD_SaveBuf[_Max_SD_Save];



u8 _Pre_Pin_Statue;
u8 _Cur_Pin_Statue;

u8 Sended = 0;


//�˴���ʾ��SRAM��ȡ,��SD��ȡʱ����л�
//���ڶ�ȡSD��Ҫ512��������������ֻ��64��������
//ȷ��������ȷ���˴���Ҫ֮ǰһ���Ӻδ���ȡ
u8 bSramRead = 1;

