#ifndef _COMMAND_H
#define _COMMAND_H
#include "operation.h"
#include "var.h"

#define __CLA  00
#define __INS  01
#define __P1   02
#define __P2   03
#define __P3   04


#define _USE_CLA      0xF0
#define _GET_SIZE     0xA0
#define _GET_DATAS    0xB0
#define _SET_OFFSET   0xC0
#define _INIT_BITS    0xF0

#define _Wrong_UNKNOWN  0x6F00
#define _Wrong_CLA      0x6E00
#define _Wrong_INS      0x6D00

#define _SUCCESS        0x9000
#define _Not_Finish     0x9F00


u16 Excute_Command(u8* u8Command,u16 u16Length);

void __GetBits_Send(void);


#endif
