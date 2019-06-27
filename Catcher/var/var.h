

#ifndef _Var_H
#define _Var_H


#include "System.h"


#define _MaxCLKCount 50000
#define _MaxCommandLen 0x15

//�洢 CLK �����Ram����
extern u8  u8CLK[_MaxCLKCount];
//��ǰCLKNumber
extern uint64_t u64CurCLK;
//֮ǰCLKNumber
extern uint64_t u64PreCLK;

//��ǰӦ�ý����ж����
extern u16       u16EXIT_Type;
extern u8        u8Clk_EXIT_TYPE;

//TIM2 �ļ�����
extern uint32_t count;

//�洢CLK ����Ŀ�Լ�������Ŀ, �˴�����ʵʱ���͵�ʱ�������
extern u16 uCLKCount;
extern u16 uSendCLKCOunt;


//���һ���ķ��ͳ��ȣ�0-512
extern u16 u16SendCurSector;

//�Ѿ����͵���������
extern u32 u32SendSector   ;

// δ��512���ȵ������ȷ���Ram��;
extern u8 SDTemp[512];

//δ��512 ����Ram�ڵĳ���
extern u16 u16Save2SDTempLen;

//�Ѿ��洢�� SD ���ڵ���������
extern u32 u32SavedSector;

//�豸��Ϣ
extern const char u8Information[8] ;


//�����洢����ָ���buf
extern u8 u8Command[_MaxCommandLen];
//�����洢����ָ��ĳ���
extern u8 u8RecLen;
//ָ��Ľ��
extern u8 u8CommandRet;

#endif