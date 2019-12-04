#include "lcd_driver.h"
#include "delay.h"

u16 tft_id;
u16 POINT_COLOR=0x0000;
/****************************************************************************
*��������TFT_GPIO_Config
*��  �룺��
*��  ������
*��  �ܣ���ʼ��TFT��IO�ڡ�
****************************************************************************/	  

void TFT_GPIO_Config(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD|RCC_APB2Periph_GPIOE|RCC_APB2Periph_GPIOG,ENABLE);//ʹ��PORTD,E,Gʱ��
	
 	//PORTD�����������  
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_10|GPIO_Pin_14|GPIO_Pin_15;				 //	//PORTD�����������  
 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; 		 //�����������   
 	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
 	GPIO_Init(GPIOD, &GPIO_InitStructure); 
  	 
	//PORTE�����������  
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7|GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_10|GPIO_Pin_11|GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15;				 //	//PORTD�����������  
 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; 		 //�����������   
 	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
 	GPIO_Init(GPIOE, &GPIO_InitStructure);    	    	 											 

   	//	//PORTG12����������� A10	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_12;	 //	//PORTG�����������  
 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; 		 //�����������   
 	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
 	GPIO_Init(GPIOG, &GPIO_InitStructure);
}

/****************************************************************************
* Function Name  : TFT_FSMC_Config
* Description    : ��ʼ��FSMC
* Input          : None
* Output         : None
* Return         : None
****************************************************************************/

void TFT_FSMC_Config(void)
{
	FSMC_NORSRAMInitTypeDef  FSMC_NORSRAMInitStructure;
  	FSMC_NORSRAMTimingInitTypeDef  FSMC_ReadTimingInitStructure; 
	FSMC_NORSRAMTimingInitTypeDef  FSMC_WriteTimingInitStructure;
	
  	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_FSMC,ENABLE);	//ʹ��FSMCʱ��

	FSMC_ReadTimingInitStructure.FSMC_AddressSetupTime = 0x01;	 //��ַ����ʱ�䣨ADDSET��Ϊ2��HCLK 1/36M=27ns
  	FSMC_ReadTimingInitStructure.FSMC_AddressHoldTime = 0x00;	 //��ַ����ʱ�䣨ADDHLD��ģʽAδ�õ�	
  	FSMC_ReadTimingInitStructure.FSMC_DataSetupTime = 0x0f;		 // ���ݱ���ʱ��Ϊ16��HCLK,��ΪҺ������IC�Ķ����ݵ�ʱ���ٶȲ���̫�죬�����1289���IC��
  	FSMC_ReadTimingInitStructure.FSMC_BusTurnAroundDuration = 0x00;
  	FSMC_ReadTimingInitStructure.FSMC_CLKDivision = 0x00;
  	FSMC_ReadTimingInitStructure.FSMC_DataLatency = 0x00;
  	FSMC_ReadTimingInitStructure.FSMC_AccessMode = FSMC_AccessMode_A;	 //ģʽA 


	FSMC_WriteTimingInitStructure.FSMC_AddressSetupTime = 0x15;	 //��ַ����ʱ�䣨ADDSET��Ϊ16��HCLK  
  	FSMC_WriteTimingInitStructure.FSMC_AddressHoldTime = 0x15;	 //��ַ����ʱ��		
  	FSMC_WriteTimingInitStructure.FSMC_DataSetupTime = 0x05;		 //���ݱ���ʱ��Ϊ6��HCLK	
  	FSMC_WriteTimingInitStructure.FSMC_BusTurnAroundDuration = 0x00;
  	FSMC_WriteTimingInitStructure.FSMC_CLKDivision = 0x00;
  	FSMC_WriteTimingInitStructure.FSMC_DataLatency = 0x00;
  	FSMC_WriteTimingInitStructure.FSMC_AccessMode = FSMC_AccessMode_A;	 //ģʽA  


  	FSMC_NORSRAMInitStructure.FSMC_Bank = FSMC_Bank1_NORSRAM4;//  ��������ʹ��NE4 ��Ҳ�Ͷ�ӦBTCR[6],[7]��
  	FSMC_NORSRAMInitStructure.FSMC_DataAddressMux = FSMC_DataAddressMux_Disable; // ���������ݵ�ַ
  	FSMC_NORSRAMInitStructure.FSMC_MemoryType =FSMC_MemoryType_SRAM;// FSMC_MemoryType_SRAM;  //SRAM   
  	FSMC_NORSRAMInitStructure.FSMC_MemoryDataWidth = FSMC_MemoryDataWidth_16b;//�洢�����ݿ��Ϊ16bit   
  	FSMC_NORSRAMInitStructure.FSMC_BurstAccessMode =FSMC_BurstAccessMode_Disable;// FSMC_BurstAccessMode_Disable; 
  	FSMC_NORSRAMInitStructure.FSMC_WaitSignalPolarity = FSMC_WaitSignalPolarity_Low;
	FSMC_NORSRAMInitStructure.FSMC_AsynchronousWait=FSMC_AsynchronousWait_Disable; 
  	FSMC_NORSRAMInitStructure.FSMC_WrapMode = FSMC_WrapMode_Disable;   
  	FSMC_NORSRAMInitStructure.FSMC_WaitSignalActive = FSMC_WaitSignalActive_BeforeWaitState;  
  	FSMC_NORSRAMInitStructure.FSMC_WriteOperation = FSMC_WriteOperation_Enable;	//  �洢��дʹ��
  	FSMC_NORSRAMInitStructure.FSMC_WaitSignal = FSMC_WaitSignal_Disable;   
  	FSMC_NORSRAMInitStructure.FSMC_ExtendedMode = FSMC_ExtendedMode_Enable; // ��дʹ�ò�ͬ��ʱ��
  	FSMC_NORSRAMInitStructure.FSMC_WriteBurst = FSMC_WriteBurst_Disable; 
  	FSMC_NORSRAMInitStructure.FSMC_ReadWriteTimingStruct = &FSMC_ReadTimingInitStructure; //��дʱ��
  	FSMC_NORSRAMInitStructure.FSMC_WriteTimingStruct = &FSMC_WriteTimingInitStructure;  //дʱ��

  	FSMC_NORSRAMInit(&FSMC_NORSRAMInitStructure);  //��ʼ��FSMC����

 	FSMC_NORSRAMCmd(FSMC_Bank1_NORSRAM4, ENABLE);  // ʹ��BANK1	
}

/****************************************************************************
* Function Name  : TFT_WriteCmd
* Description    : LCDд������
* Input          : cmd��д���16λ����
* Output         : None
* Return         : None
****************************************************************************/

void TFT_WriteCmd(uint16_t cmd)
{
	TFT->TFT_CMD=(cmd>>8)<<1;
	TFT->TFT_CMD=(cmd&0xff)<<1;
}

/****************************************************************************
* Function Name  : TFT_WriteData
* Description    : LCDд������
* Input          : dat��д���16λ����
* Output         : None
* Return         : None
****************************************************************************/

void TFT_WriteData(u16 dat)
{
	TFT->TFT_DATA=(dat>>8)<<1;
	TFT->TFT_DATA=(dat&0xff)<<1;
}

u32 LCD_RGBColor_Change(u16 color)
{
	u8 r,g,b=0;
	
	r=(color>>11)&0x1f;
	g=(color>>5)&0x3f;
	b=color&0x1f;
	
	return ((r<<13)|(g<<6)|(b<<1));
}

void TFT_WriteData_Color(u16 color)
{
	u32 recolor=0;
	recolor=LCD_RGBColor_Change(color);
	TFT->TFT_DATA=(recolor>>9);
	TFT->TFT_DATA=recolor;
}

/****************************************************************************
* Function Name  : TFT_Init
* Description    : ��ʼ��LCD��
* Input          : None
* Output         : None
* Return         : None
****************************************************************************/

void TFT_Init(void)
{
	uint16_t i;

	TFT_GPIO_Config();
	TFT_FSMC_Config();
	delay_ms(50); 



	TFT_WriteCmd(0x0000);
	TFT_WriteCmd(0x0000);
	delay_ms(10);
	TFT_WriteCmd(0x0000);
	TFT_WriteCmd(0x0000);
	TFT_WriteCmd(0x0000);
	TFT_WriteCmd(0x0000);
	TFT_WriteCmd(0x00A4);TFT_WriteData(0x0001);
	delay_ms(10);

	TFT_WriteCmd(0x0060);TFT_WriteData(0x2700);
	TFT_WriteCmd(0x0008);TFT_WriteData(0x0808);

	//----------- Adjust the Gamma Curve ----------/
	TFT_WriteCmd(0x0300);TFT_WriteData(0x0109);  // Gamma Control
	TFT_WriteCmd(0x0301);TFT_WriteData(0x7E0A); 
	TFT_WriteCmd(0x0302);TFT_WriteData(0x0704); 
	TFT_WriteCmd(0x0303);TFT_WriteData(0x0911); 
	TFT_WriteCmd(0x0304);TFT_WriteData(0x2100); 
	TFT_WriteCmd(0x0305);TFT_WriteData(0x1109); 
	TFT_WriteCmd(0x0306);TFT_WriteData(0x7407); 
	TFT_WriteCmd(0x0307);TFT_WriteData(0x0A0E); 
	TFT_WriteCmd(0x0308);TFT_WriteData(0x0901); 
	TFT_WriteCmd(0x0309);TFT_WriteData(0x0021);

	TFT_WriteCmd(0x0010);TFT_WriteData(0x0010);  // Frame frequence
	TFT_WriteCmd(0x0011);TFT_WriteData(0x0202);  // 
	TFT_WriteCmd(0x0012);TFT_WriteData(0x0300); 
	TFT_WriteCmd(0x0013);TFT_WriteData(0x0007);
	delay_ms(10);
	// -------------- Power On sequence -------------//
	TFT_WriteCmd(0x0100);TFT_WriteData(0x0000);  // VGH/VGL 6/-3
	TFT_WriteCmd(0x0101);TFT_WriteData(0x0007);  // VCI1
	TFT_WriteCmd(0x0102);TFT_WriteData(0x0000);  // VREG1
	TFT_WriteCmd(0x0103);TFT_WriteData(0x0000);  // VDV 
	TFT_WriteCmd(0x0280);TFT_WriteData(0x0000);  // VCM
	delay_ms(200);//delay_ms 200ms
	TFT_WriteCmd(0x0100);TFT_WriteData(0x0330);  // VGH/VGL 6/-3
	TFT_WriteCmd(0x0101);TFT_WriteData(0x0247);  // VCI1
	delay_ms(50);//delay_ms 50ms
	TFT_WriteCmd(0x0102);TFT_WriteData(0xD1B0);  // VREG1
	delay_ms(50);//delay_ms 50ms
	TFT_WriteCmd(0x0103);TFT_WriteData(0x1000);  // VDV          //0900
	TFT_WriteCmd(0x0280);TFT_WriteData(0xC600);  // VCM          //chenyu 0xc600

	delay_ms(200);

	TFT_WriteCmd(0x0001);TFT_WriteData(0x0000);
	TFT_WriteCmd(0x0002);TFT_WriteData(0x0200);
	TFT_WriteCmd(0x0003);TFT_WriteData(0x1038);
	TFT_WriteCmd(0x0009);TFT_WriteData(0x0001);
	TFT_WriteCmd(0x000A);TFT_WriteData(0x0008);
	TFT_WriteCmd(0x000C);TFT_WriteData(0x0000);
	TFT_WriteCmd(0x000D);TFT_WriteData(0x0000);
	TFT_WriteCmd(0x000E);TFT_WriteData(0x0030);
	TFT_WriteCmd(0x0020);TFT_WriteData(0x0000);//H Start
	TFT_WriteCmd(0x0021);TFT_WriteData(0x0000);//V Start
	TFT_WriteCmd(0x0029);TFT_WriteData(0x0052);
	TFT_WriteCmd(0x0050);TFT_WriteData(0x0000);
	TFT_WriteCmd(0x0051);TFT_WriteData(0x00EF);
	TFT_WriteCmd(0x0052);TFT_WriteData(0x0000);
	TFT_WriteCmd(0x0053);TFT_WriteData(0x013F);
	TFT_WriteCmd(0x0061);TFT_WriteData(0x0000);
	TFT_WriteCmd(0x006A);TFT_WriteData(0x0000);
	TFT_WriteCmd(0x0080);TFT_WriteData(0x0000);
	TFT_WriteCmd(0x0081);TFT_WriteData(0x0000);
	TFT_WriteCmd(0x0082);TFT_WriteData(0x005F);
	TFT_WriteCmd(0x0093);TFT_WriteData(0x0507);

	TFT_WriteCmd(0x0007);TFT_WriteData(0x0100);//DISPLAY ON
	delay_ms(50);
	TFT_WriteCmd(0x0022);//GRAM Data Write
}

/****************************************************************************
* Function Name  : TFT_SetWindow
* Description    : ����Ҫ�����Ĵ��ڷ�Χ
* Input          : xStart��������ʼX����
*                * yStart��������ʼY����
*                * xEnd�����ڽ���X����
*                * yEnd�����ڽ���Y����
* Output         : None
* Return         : None
****************************************************************************/

void TFT_SetWindow(uint16_t xStart, uint16_t yStart, uint16_t xEnd, uint16_t yEnd)
{

	TFT_WriteCmd(0x0212);   
	TFT_WriteData(xStart);
	TFT_WriteCmd(0x0213);  
	TFT_WriteData(xEnd);
	TFT_WriteCmd(0x0210);   
	TFT_WriteData(yStart);
	TFT_WriteCmd(0x0211);   
	TFT_WriteData(yEnd);

	TFT_WriteCmd(0x0201);   
	TFT_WriteData(xStart);
	TFT_WriteCmd(0x0200);   
	TFT_WriteData(yStart);	
	TFT_WriteCmd(0x0202);
}

/****************************************************************************
* Function Name  : TFT_ClearScreen
* Description    : ��LCD��������Ӧ����ɫ
* Input          : color��������ɫ
* Output         : None
* Return         : None
****************************************************************************/
	  
void TFT_ClearScreen(uint16_t color)
{
 	uint16_t i, j ;

	TFT_SetWindow(0, 0, TFT_XMAX-1, TFT_YMAX-1);	 //��������
  	for(i=0; i<TFT_XMAX; i++)
	{
		for (j=0; j<TFT_YMAX; j++)
		{
			TFT_WriteData_Color(color);
		}
	}
}

