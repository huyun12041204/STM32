#include "var.h"





//TIM 1- 8 ��״̬��
u8 TIMxStatue = 0;



//
u32 TIM3Count;

u16 CurTIM3CLK;
u32 CurTIM3Count;

u16 preTIM3CLK;
u32 preTIM3Count;

u16 DeltaTIM3CLK;
u32 DeltaTIM3Count;






//�������ݣ��������ݣ��洢���ݳ���

u32 u32CLKLen;
u32 u32SendLen;
u32 u32SaveLen;

//USB ���ͺ� �洢ʹ��

u8 _USB_SendBuf[512];
u8 _SD_SaveBuf[_Max_SD_Save];



u8 _Cur_Pin_Statue;

//�˴���ʾ��SRAM��ȡ,��SD��ȡʱ����л�
//���ڶ�ȡSD��Ҫ512��������������ֻ��64��������
//ȷ��������ȷ���˴���Ҫ֮ǰһ���Ӻδ���ȡ
u8 bSramRead = 1;

u32 u32Second;