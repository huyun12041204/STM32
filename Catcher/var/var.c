#include "var.h"




//�洢 CLK �����Ram����
u8  u8CLK[_MaxCLKCount];
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


u8 u8UsartSendBuf[_MaxSectorSize];
u16 u16UsartSendBufLength;

const char u8Information[8] = {0x00,0x11,0x22,0x33,0x44,0x55,0x66,0x77 };











