#include "var.h"





//TIM 1- 8 ��״̬��
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


////��������Ƶ��
//u16 TIM5Count;
//u8  u8CC1; // ������������жϴ˴�
//u32 u321st;
//u32 u322nd;




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

u16 u16Vol;
u16 u16Fre;
u16 u16TFre[10];

u16 u16DisVol;
u16 u16DisFre;

u8 u8FreTime;

