

#ifndef _Command_H
#define _Command_H
#include "system.h"
#include "SysTick.h"

#define _Com_CLA 0
#define _Com_INS 1
#define _Com_P1 2
#define _Com_P2 3
#define _Com_P3 4

#define _Com_Tag 0xFE

#define _INS_GetInfo         02
#define _INS_GetSendSign     04
#define _INS_GetBits       0x20
#define _INS_GetBits_First   01
#define _INS_GetBits_Next    02
#define _INS_GetBits_Pre     03



void Excute_Command(void);
void _SendBuf_Init(void);
void _Command_Init(void);
void SendCharData(const char cData);
void Install_Command(u8 _u8CommandByte);

#endif
