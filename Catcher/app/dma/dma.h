#ifndef _dma_H
#define _dma_H

#include "system.h"
//#include "delay.h"
void DMA_Init_(DMA_Channel_TypeDef* DMA_CHx,u32 cpar,u32 cmar,u16 cndtr);
void DMA_Enable(DMA_Channel_TypeDef* DMA_CHx,u16 cndtr);  //开启DMA一次传输

#endif
