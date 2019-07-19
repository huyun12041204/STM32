/**
  ******************************************************************************
  * @file    usbio.c
  * $Author: wdluo $
  * $Revision: 67 $
  * $Date:: 2012-08-15 19:00:29 +0800 #$
  * @brief   USB上层函数.
  ******************************************************************************
  * @attention
  *
  *<h3><center>&copy; Copyright 2009-2012, ViewTool</center>
  *<center><a href="http:\\www.viewtool.com">http://www.viewtool.com</a></center>
  *<center>All Rights Reserved</center></h3>
  * 
  ******************************************************************************
  */
/* Includes ------------------------------------------------------------------*/
//#include "main.h"
#include "Stm32f10x.h"
#include "usb_desc.h"
#include "usb_lib.h"
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
extern uint8_t USB_Receive_Buffer[256];
extern uint8_t USB_Send_Buffer[256];
uint8_t g_dataSerialNumber;
/* Private variables ---------------------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/

  
/* Private functions ---------------------------------------------------------*/
/**
  * @brief  通过USB发送数据
  * @param  data 数据存储首地址
  * @param  dataNum 发送的数据字节数
  * @retval 发送的字节数
  */
uint32_t USB_SendData(uint8_t bEpNum,uint8_t *data,uint32_t dataNum)
{
	//将数据通过USB发送出去
	if(bEpNum == ENDP1){
		UserToPMABufferCopy(data, ENDP1_TXADDR, dataNum);
	}else{
		UserToPMABufferCopy(data, ENDP2_TXADDR, dataNum);
	}
	SetEPTxCount(bEpNum, dataNum);
	SetEPTxValid(bEpNum);
	return dataNum;  
}
/**
  * @brief  接收从USB获取的数据
  * @param  data 数据存储首地址
  * @param  dataNum 准备读取的数据字节数
  * @retval 读取的字节数
  */
uint32_t USB_GetData(uint8_t bEpNum,uint8_t *data,uint32_t dataNum)
{
    uint32_t len=0;
	if(dataNum>sizeof(USB_Receive_Buffer)){
		dataNum = sizeof(USB_Receive_Buffer);
	}
	for(len=0;len<dataNum;len++){
		*data=USB_Receive_Buffer[len];
		data++;
	}
    return dataNum;
}

uint32_t USB_SendData_EndP1_Two(uint8_t *data,uint32_t dataNum)
{
	
	if (GetENDPOINT(ENDP1) & EP_DTOG_RX)
	{
		UserToPMABufferCopy(data, ENDP1_TXADDR0, dataNum);
		SetEPDblBuf0Count(ENDP1, EP_DBUF_IN, dataNum);
	}
	else
	{
		UserToPMABufferCopy(data, ENDP1_TXADDR1, dataNum);
		SetEPDblBuf1Count(ENDP1, EP_DBUF_IN, dataNum);
	}
	
	FreeUserBuffer(ENDP1, EP_DBUF_IN);
	return dataNum;

}


/*********************************END OF FILE**********************************/

