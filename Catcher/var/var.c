#include "var.h"



#ifndef _2Channel
//�洢 CLK �����Ram����
u8  u8CLK[_MaxCLKCount];
#endif

//��ǰCLKNumber
uint64_t u64CurCLK;
//֮ǰCLKNumber
uint64_t u64PreCLK;

//��ǰӦ�ý����ж����
u16       u16EXIT_Type;
u8        u8Clk_EXIT_TYPE;


//TIM2 �ļ�����
uint32_t count;


//ͨ��

u16 uCLKCount;
u16 uSendCLKCOunt;


uint64_t SramOffset;



//���һ���ķ��ͳ��ȣ�0-512
u16 u16SendCurSector;

//�Ѿ����͵���������
u32 u32SendSector   ;

// δ��512���ȵ������ȷ���Ram��;
u8 SDTemp[512];
u16 u16Save2SDTempLen;
u32 u32SavedSector;



u8 u8Command[_MaxCommandLen];
u8 u8RecLen;
u8 u8CommandRet;


u8 u8UsartSendBuf[_MaxUsartSendSize];
u16 u16UsartSendBufLength;

const char u8Information[8] = {0x00,0x11,0x22,0x33,0x44,0x55,0x66,0x77 };


#ifdef _2Channel
//�洢 CLK �����Ram����
u8  u8CLKT[_MaxCLKCount][2];
u16 uCount[2];
u8  u8Channel;
#endif



#ifdef _Mode_V2

u8 _Pre_Pin_Statue;
u8 _Cur_Pin_Statue;

#endif

u8 TIM5_CH1_CAPTURE_STA; //���벶��״̬ 
u16 TIM5_CH1_CAPTURE_VAL;//���벶��ֵ