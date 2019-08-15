#include "lcd.h"
#include "oledfont.h"
#include "delay.h"
#include "bmp.h"
#include "stdio.h"
u16 BACK_COLOR;   //����ɫ

u16 lCurY;
u16 lCurX;


/******************************************************************************
      ����˵����LCD��������д�뺯��
      ������ݣ�dat  Ҫд��Ĵ�������
      ����ֵ��  ��
******************************************************************************/
void LCD_Writ_Bus(u8 dat) 
{	
	u8 i;
	for(i=0;i<8;i++)
	{			  
		OLED_SCLK_Clr();
		if(dat&0x80)
		   OLED_SDIN_Set();
		else
		   OLED_SDIN_Clr();
		OLED_SCLK_Set();
		dat<<=1;
	}
}


/******************************************************************************
      ����˵����LCDд������
      ������ݣ�dat д�������
      ����ֵ��  ��
******************************************************************************/
void LCD_WR_DATA8(u8 dat)
{
	OLED_DC_Set();//д����
	LCD_Writ_Bus(dat);
}


/******************************************************************************
      ����˵����LCDд������
      ������ݣ�dat д�������
      ����ֵ��  ��
******************************************************************************/
void LCD_WR_DATA(u16 dat)
{
	OLED_DC_Set();//д����
	LCD_Writ_Bus(dat>>8);
	LCD_Writ_Bus(dat);
}


/******************************************************************************
      ����˵����LCDд������
      ������ݣ�dat д�������
      ����ֵ��  ��
******************************************************************************/
void LCD_WR_REG(u8 dat)
{
	OLED_DC_Clr();//д����
	LCD_Writ_Bus(dat);
}


/******************************************************************************
      ����˵����������ʼ�ͽ�����ַ
      ������ݣ�x1,x2 �����е���ʼ�ͽ�����ַ
                y1,y2 �����е���ʼ�ͽ�����ַ
      ����ֵ��  ��
******************************************************************************/
void LCD_Address_Set(u16 x1,u16 y1,u16 x2,u16 y2)
{
	if(USE_HORIZONTAL==0)
	{
		LCD_WR_REG(0x2a);//�е�ַ����
		LCD_WR_DATA(x1);
		LCD_WR_DATA(x2);
		LCD_WR_REG(0x2b);//�е�ַ����
		LCD_WR_DATA(y1);
		LCD_WR_DATA(y2);
		LCD_WR_REG(0x2c);//������д
	}
	else if(USE_HORIZONTAL==1)
	{
		LCD_WR_REG(0x2a);//�е�ַ����
		LCD_WR_DATA(x1);
		LCD_WR_DATA(x2);
		LCD_WR_REG(0x2b);//�е�ַ����
		LCD_WR_DATA(y1+80);
		LCD_WR_DATA(y2+80);
		LCD_WR_REG(0x2c);//������д
	}
	else if(USE_HORIZONTAL==2)
	{
		LCD_WR_REG(0x2a);//�е�ַ����
		LCD_WR_DATA(x1);
		LCD_WR_DATA(x2);
		LCD_WR_REG(0x2b);//�е�ַ����
		LCD_WR_DATA(y1);
		LCD_WR_DATA(y2);
		LCD_WR_REG(0x2c);//������д
	}
	else
	{
		LCD_WR_REG(0x2a);//�е�ַ����
		LCD_WR_DATA(x1+80);
		LCD_WR_DATA(x2+80);
		LCD_WR_REG(0x2b);//�е�ַ����
		LCD_WR_DATA(y1);
		LCD_WR_DATA(y2);
		LCD_WR_REG(0x2c);//������д
	}
}


/******************************************************************************
      ����˵����LCD��ʼ������
      ������ݣ���
      ����ֵ��  ��
******************************************************************************/
void Lcd_Init(void)
{
	GPIO_InitTypeDef GPIO_Initure;
	__HAL_RCC_GPIOA_CLK_ENABLE();					//����GPIOAʱ��
	__HAL_RCC_GPIOB_CLK_ENABLE();					//����GPIOBʱ��
	__HAL_RCC_GPIOC_CLK_ENABLE();					//����GPIOCʱ��
	__HAL_RCC_GPIOE_CLK_ENABLE();					//����GPIOEʱ��

	GPIO_Initure.Pin=GPIO_PIN_5|GPIO_PIN_7;			//PA5,7
	GPIO_Initure.Mode=GPIO_MODE_OUTPUT_PP;  		//�������
	GPIO_Initure.Pull=GPIO_PULLUP;         			//����
	GPIO_Initure.Speed=GPIO_SPEED_FREQ_VERY_HIGH;  	//����
	HAL_GPIO_Init(GPIOA,&GPIO_Initure);     		//��ʼ��GPIOA
	HAL_GPIO_WritePin(GPIOA,GPIO_PIN_5|GPIO_PIN_7,GPIO_PIN_SET);
	
	GPIO_Initure.Pin=GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2;			//PB0,1,2
	GPIO_Initure.Mode=GPIO_MODE_OUTPUT_PP;  		//�������
	GPIO_Initure.Pull=GPIO_PULLUP;         			//����
	GPIO_Initure.Speed=GPIO_SPEED_FREQ_VERY_HIGH;  	//����
	HAL_GPIO_Init(GPIOB,&GPIO_Initure);     		//��ʼ��GPIOB
//	HAL_GPIO_WritePin(GPIOB,GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2,GPIO_PIN_SET);
	
	HAL_GPIO_WritePin(GPIOB,GPIO_PIN_0,GPIO_PIN_SET);
	
	GPIO_Initure.Pin=GPIO_PIN_4|GPIO_PIN_5;			//PC4,5
	GPIO_Initure.Mode=GPIO_MODE_OUTPUT_PP;  		//�������
	GPIO_Initure.Pull=GPIO_PULLUP;         			//����
	GPIO_Initure.Speed=GPIO_SPEED_FREQ_VERY_HIGH;  	//����
	HAL_GPIO_Init(GPIOC,&GPIO_Initure);     		//��ʼ��GPIOC
	HAL_GPIO_WritePin(GPIOC,GPIO_PIN_4|GPIO_PIN_5,GPIO_PIN_SET);
	
	//GPIO_Initure.Pin=GPIO_PIN_7|GPIO_PIN_8;			//PE7,8
	//GPIO_Initure.Mode=GPIO_MODE_OUTPUT_PP;  		//�������
	//GPIO_Initure.Pull=GPIO_PULLUP;         			//����
//	GPIO_Initure.Speed=GPIO_SPEED_FREQ_VERY_HIGH;  	//����
	//HAL_GPIO_Init(GPIOE,&GPIO_Initure);     		//��ʼ��GPIOE
//	HAL_GPIO_WritePin(GPIOE,GPIO_PIN_7|GPIO_PIN_8,GPIO_PIN_SET);
	
	OLED_RST_Clr();
	delay_ms(200);
	OLED_RST_Set();
	OLED_BLK_Set();
	delay_ms(200);
	
//************* Start Initial Sequence **********// 
LCD_WR_REG(0x36);
if(USE_HORIZONTAL==0)LCD_WR_DATA8(0x00);
else if(USE_HORIZONTAL==1)LCD_WR_DATA8(0xC0);
else if(USE_HORIZONTAL==2)LCD_WR_DATA8(0x70);
else LCD_WR_DATA8(0xA0);

LCD_WR_REG(0x3A); 
LCD_WR_DATA8(0x05);

LCD_WR_REG(0xB2);
LCD_WR_DATA8(0x0C);
LCD_WR_DATA8(0x0C);
LCD_WR_DATA8(0x00);
LCD_WR_DATA8(0x33);
LCD_WR_DATA8(0x33); 

LCD_WR_REG(0xB7); 
LCD_WR_DATA8(0x35);  

LCD_WR_REG(0xBB);
LCD_WR_DATA8(0x19);

LCD_WR_REG(0xC0);
LCD_WR_DATA8(0x2C);

LCD_WR_REG(0xC2);
LCD_WR_DATA8(0x01);

LCD_WR_REG(0xC3);
LCD_WR_DATA8(0x12);   

LCD_WR_REG(0xC4);
LCD_WR_DATA8(0x20);  

LCD_WR_REG(0xC6); 
LCD_WR_DATA8(0x0F);    

LCD_WR_REG(0xD0); 
LCD_WR_DATA8(0xA4);
LCD_WR_DATA8(0xA1);

LCD_WR_REG(0xE0);
LCD_WR_DATA8(0xD0);
LCD_WR_DATA8(0x04);
LCD_WR_DATA8(0x0D);
LCD_WR_DATA8(0x11);
LCD_WR_DATA8(0x13);
LCD_WR_DATA8(0x2B);
LCD_WR_DATA8(0x3F);
LCD_WR_DATA8(0x54);
LCD_WR_DATA8(0x4C);
LCD_WR_DATA8(0x18);
LCD_WR_DATA8(0x0D);
LCD_WR_DATA8(0x0B);
LCD_WR_DATA8(0x1F);
LCD_WR_DATA8(0x23);

LCD_WR_REG(0xE1);
LCD_WR_DATA8(0xD0);
LCD_WR_DATA8(0x04);
LCD_WR_DATA8(0x0C);
LCD_WR_DATA8(0x11);
LCD_WR_DATA8(0x13);
LCD_WR_DATA8(0x2C);
LCD_WR_DATA8(0x3F);
LCD_WR_DATA8(0x44);
LCD_WR_DATA8(0x51);
LCD_WR_DATA8(0x2F);
LCD_WR_DATA8(0x1F);
LCD_WR_DATA8(0x1F);
LCD_WR_DATA8(0x20);
LCD_WR_DATA8(0x23);

LCD_WR_REG(0x21); 

LCD_WR_REG(0x11); 

LCD_WR_REG(0x29);  
} 


/******************************************************************************
      ����˵����LCD��������
      ������ݣ���
      ����ֵ��  ��
******************************************************************************/
void LCD_Clear(u16 Color)
{
	u16 i,j;  	
	LCD_Address_Set(0,0,LCD_W-1,LCD_H-1);
    for(i=0;i<LCD_W;i++)
	  {
			for (j=0;j<LCD_H;j++)
				{
					LCD_WR_DATA(Color);
				}
	  }
}


/******************************************************************************
      ����˵����LCD��ʾ����
      ������ݣ�x,y   ��ʼ����
                index ���ֵ����
                size  �ֺ�
      ����ֵ��  ��
******************************************************************************/
void LCD_ShowChinese(u16 x,u16 y,u8 index,u8 size,u16 color)	
{  
	u8 i,j;
	u8 *temp,size1;
	if(size==16){temp=Hzk16;}//ѡ���ֺ�
	if(size==32){temp=Hzk32;}
  LCD_Address_Set(x,y,x+size-1,y+size-1); //����һ�����ֵ�����
  size1=size*size/8;//һ��������ռ���ֽ�
	temp+=index*size1;//д�����ʼλ��
	for(j=0;j<size1;j++)
	{
		for(i=0;i<8;i++)
		{
		 	if((*temp&(1<<i))!=0)//�����ݵĵ�λ��ʼ��
			{
				LCD_WR_DATA(color);//����
			}
			else
			{
				LCD_WR_DATA(BACK_COLOR);//������
			}
		}
		temp++;
	 }
}


/******************************************************************************
      ����˵����LCD��ʾ����
      ������ݣ�x,y   ��ʼ����
      ����ֵ��  ��
******************************************************************************/
void LCD_DrawPoint(u16 x,u16 y,u16 color)
{
	LCD_Address_Set(x,y,x,y);//���ù��λ�� 
	LCD_WR_DATA(color);
} 


/******************************************************************************
      ����˵����LCD��һ����ĵ�
      ������ݣ�x,y   ��ʼ����
      ����ֵ��  ��
******************************************************************************/
void LCD_DrawPoint_big(u16 x,u16 y,u16 color)
{
	LCD_Fill(x-1,y-1,x+1,y+1,color);
} 


/******************************************************************************
      ����˵������ָ�����������ɫ
      ������ݣ�xsta,ysta   ��ʼ����
                xend,yend   ��ֹ����
      ����ֵ��  ��
******************************************************************************/
void LCD_Fill(u16 xsta,u16 ysta,u16 xend,u16 yend,u16 color)
{          
	u16 i,j; 
	LCD_Address_Set(xsta,ysta,xend,yend);      //���ù��λ�� 
	for(i=ysta;i<=yend;i++)
	{													   	 	
		for(j=xsta;j<=xend;j++)LCD_WR_DATA(color);//���ù��λ�� 	    
	} 					  	    
}


/******************************************************************************
      ����˵��������
      ������ݣ�x1,y1   ��ʼ����
                x2,y2   ��ֹ����
      ����ֵ��  ��
******************************************************************************/
void LCD_DrawLine(u16 x1,u16 y1,u16 x2,u16 y2,u16 color)
{
	u16 t; 
	int xerr=0,yerr=0,delta_x,delta_y,distance;
	int incx,incy,uRow,uCol;
	delta_x=x2-x1; //������������ 
	delta_y=y2-y1;
	uRow=x1;//�����������
	uCol=y1;
	if(delta_x>0)incx=1; //���õ������� 
	else if (delta_x==0)incx=0;//��ֱ�� 
	else {incx=-1;delta_x=-delta_x;}
	if(delta_y>0)incy=1;
	else if (delta_y==0)incy=0;//ˮƽ�� 
	else {incy=-1;delta_y=-delta_x;}
	if(delta_x>delta_y)distance=delta_x; //ѡȡ�������������� 
	else distance=delta_y;
	for(t=0;t<distance+1;t++)
	{
		LCD_DrawPoint(uRow,uCol,color);//����
		xerr+=delta_x;
		yerr+=delta_y;
		if(xerr>distance)
		{
			xerr-=distance;
			uRow+=incx;
		}
		if(yerr>distance)
		{
			yerr-=distance;
			uCol+=incy;
		}
	}
}


/******************************************************************************
      ����˵����������
      ������ݣ�x1,y1   ��ʼ����
                x2,y2   ��ֹ����
      ����ֵ��  ��
******************************************************************************/
void LCD_DrawRectangle(u16 x1, u16 y1, u16 x2, u16 y2,u16 color)
{
	LCD_DrawLine(x1,y1,x2,y1,color);
	LCD_DrawLine(x1,y1,x1,y2,color);
	LCD_DrawLine(x1,y2,x2,y2,color);
	LCD_DrawLine(x2,y1,x2,y2,color);
}


/******************************************************************************
      ����˵������Բ
      ������ݣ�x0,y0   Բ������
                r       �뾶
      ����ֵ��  ��
******************************************************************************/
void Draw_Circle(u16 x0,u16 y0,u8 r,u16 color)
{
	int a,b;
//	int di;
	a=0;b=r;	  
	while(a<=b)
	{
		LCD_DrawPoint(x0-b,y0-a,color);             //3           
		LCD_DrawPoint(x0+b,y0-a,color);             //0           
		LCD_DrawPoint(x0-a,y0+b,color);             //1                
		LCD_DrawPoint(x0-a,y0-b,color);             //2             
		LCD_DrawPoint(x0+b,y0+a,color);             //4               
		LCD_DrawPoint(x0+a,y0-b,color);             //5
		LCD_DrawPoint(x0+a,y0+b,color);             //6 
		LCD_DrawPoint(x0-b,y0+a,color);             //7
		a++;
		if((a*a+b*b)>(r*r))//�ж�Ҫ���ĵ��Ƿ��Զ
		{
			b--;
		}
	}
}


/******************************************************************************
      ����˵������ʾ�ַ�
      ������ݣ�x,y    �������
                num    Ҫ��ʾ���ַ�
                mode   1���ӷ�ʽ  0�ǵ��ӷ�ʽ
      ����ֵ��  ��
******************************************************************************/
void LCD_ShowChar(u16 x,u16 y,u8 num,u8 mode,u16 color)
{
    u8 temp;
    u8 pos,t;
	  u16 x0=x;    
    if(x>LCD_W-16||y>LCD_H-16)return;	    //���ô���		   
	num=num-' ';//�õ�ƫ�ƺ��ֵ
	LCD_Address_Set(x,y,x+8-1,y+16-1);      //���ù��λ�� 
	if(!mode) //�ǵ��ӷ�ʽ
	{
		for(pos=0;pos<16;pos++)
		{ 
			temp=asc2_1608[(u16)num*16+pos];		 //����1608����
			for(t=0;t<8;t++)
		    {                 
		        if(temp&0x01)LCD_WR_DATA(color);
				else LCD_WR_DATA(BACK_COLOR);
				temp>>=1;
				x++;
		    }
			x=x0;
			y++;
		}	
	}else//���ӷ�ʽ
	{
		for(pos=0;pos<16;pos++)
		{
		    temp=asc2_1608[(u16)num*16+pos];		 //����1608����
			for(t=0;t<8;t++)
		    {                 
		        if(temp&0x01)LCD_DrawPoint(x+t,y+pos,color);//��һ����     
		        temp>>=1; 
		    }
		}
	}   	   	 	  
}


/******************************************************************************
      ����˵������ʾ�ַ���
      ������ݣ�x,y    �������
                *p     �ַ�����ʼ��ַ
      ����ֵ��  ��
******************************************************************************/
void LCD_ShowString(u16 x,u16 y,const u8 *p,u16 color)
{         
    while(*p!='\0')
    {       
        if(x>LCD_W-16){x=0;y+=16;}
        if(y>LCD_H-16){y=x=0;LCD_Clear(RED);}
        LCD_ShowChar(x,y,*p,0,color);
        x+=8;
        p++;
    }  
}


/******************************************************************************
      ����˵������ʾ����
      ������ݣ�m������nָ��
      ����ֵ��  ��
******************************************************************************/
u32 mypow(u8 m,u8 n)
{
	u32 result=1;	 
	while(n--)result*=m;    
	return result;
}


/******************************************************************************
      ����˵������ʾ����
      ������ݣ�x,y    �������
                num    Ҫ��ʾ������
                len    Ҫ��ʾ�����ָ���
      ����ֵ��  ��
******************************************************************************/
void LCD_ShowNum(u16 x,u16 y,u16 num,u8 len,u16 color)
{         	
	u8 t,temp;
	u8 enshow=0;
	for(t=0;t<len;t++)
	{
		temp=(num/mypow(10,len-t-1))%10;
		if(enshow==0&&t<(len-1))
		{
			if(temp==0)
			{
				LCD_ShowChar(x+8*t,y,' ',0,color);
				continue;
			}else enshow=1; 
		 	 
		}
	 	LCD_ShowChar(x+8*t,y,temp+48,0,color); 
	}
} 


/******************************************************************************
      ����˵������ʾС��
      ������ݣ�x,y    �������
                num    Ҫ��ʾ��С��
                len    Ҫ��ʾ�����ָ���
      ����ֵ��  ��
******************************************************************************/
void LCD_ShowNum1(u16 x,u16 y,float num,u8 len,u16 color)
{         	
	u8 t,temp;
//	u8 enshow=0;
	u16 num1;
	num1=num*100;
	for(t=0;t<len;t++)
	{
		temp=(num1/mypow(10,len-t-1))%10;
		if(t==(len-2))
		{
			LCD_ShowChar(x+8*(len-2),y,'.',0,color);
			t++;
			len+=1;
		}
	 	LCD_ShowChar(x+8*t,y,temp+48,0,color);
	}
}


/******************************************************************************
      ����˵������ʾ40x40ͼƬ
      ������ݣ�x,y    �������
      ����ֵ��  ��
******************************************************************************/
void LCD_ShowPicture(u16 x1,u16 y1,u16 x2,u16 y2)
{
	int i;
	  LCD_Address_Set(x1,y1,x2,y2);
		for(i=0;i<1600;i++)
	  { 	
			LCD_WR_DATA8(image[i*2+1]);	 
			LCD_WR_DATA8(image[i*2]);			
	  }			
}

void LCD_View_Init(void)
{
	
  Lcd_Init();
	LCD_Clear(WHITE);
	BACK_COLOR=WHITE;
	
  lCurY = _Output_Text_Y;
  lCurX = _Output_Text_X;
	
	LCD_DrawRectangle(_Windows_S_X,_Windows_S_Y,_Windows_E_X,_Windows_E_Y,BLUE);
	LCD_DrawRectangle(_Windows_S_X+1,_Windows_S_Y+1,_Windows_E_X+1,_Windows_E_Y+1,BLUE);
	LCD_DrawRectangle(_Windows_S_X+2,_Windows_S_Y+2,_Windows_E_X+2,_Windows_E_Y+2,BLUE);
	
//	LCD_DrawLine(5,50,235,50,GBLUE);
	
    //������
    LCD_DrawLine(_Windows_S_X,_Title_E_Y,_Windows_E_X,_Title_E_Y,_Windows_Color);

    //����״̬

    //��������
//	GUI_Line(_Connect_TYPE_E_X,_Title_E_Y,_Connect_TYPE_E_X,_Connect_TYPE_E_Y,_Windows_Color);

    LCD_ShowString(_Text_X,     _Connect_E_Y-17,"Type  :", FRONT_COLOR);
    LCD_ShowString(_Text_X+115, _Connect_E_Y-17,"Statue:", FRONT_COLOR);

    LCD_ShowString(_Text_X+60,  _Connect_E_Y-17,"None", FRONT_COLOR);
    LCD_ShowString(_Text_X+175, _Connect_E_Y-17,"--", FRONT_COLOR);

    LCD_DrawLine(_Windows_S_X,_Connect_E_Y,_Windows_E_X,_Connect_E_Y,_Windows_Color);

   // LCD_ShowString(_Text_X, _Connect_E_Y+1,"Data", FRONT_COLOR);

    LCD_ShowString(_Text_X    , _Data_SS_E_Y-17,"Save  :", FRONT_COLOR);
    LCD_ShowString(_Text_X+115, _Data_SS_E_Y-17,"Send  :", FRONT_COLOR);
    LCD_ShowString(_Text_X+60,  _Data_SS_E_Y-17,"0", FRONT_COLOR);
    LCD_ShowString(_Text_X+175, _Data_SS_E_Y-17,"0", FRONT_COLOR);

    LCD_DrawLine(_Windows_S_X,_Data_SS_E_Y,_Windows_E_X,_Data_SS_E_Y,_Windows_Color);


    LCD_ShowString(_Text_X, _PIN_SS_E_Y-17,"VCC:",FRONT_COLOR);


    LCD_ShowString(_Text_X+40, _PIN_SS_E_Y-17,"----mv",FRONT_COLOR);


    LCD_ShowString(_Text_X+115, _PIN_SS_E_Y-17,"CLK:",FRONT_COLOR);


    LCD_ShowString(_Text_X+155, _PIN_SS_E_Y-17,"----khz",FRONT_COLOR);


    LCD_DrawLine(_Windows_S_X,_PIN_SS_E_Y,_Windows_E_X,_PIN_SS_E_Y,_Windows_Color);
		
	//	LCD_DrawLine(_Windows_S_X,_Windows_Outpu_S_Y,_Windows_E_X,_Windows_Outpu_S_Y,_Windows_Color);
	
}

int fputc(int ch,FILE *p)  //����Ĭ�ϵģ���ʹ��printf����ʱ�Զ�����
{
	    u8 Empty[30] = {0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,
                    0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,
                    0x20,0x20,0x20,0x20,0x20,0x20,0x20
                   };
    //��Ϊ��һ���ַ�ʱ��,�����ǰ��;
    if(lCurX == _Output_Text_X)		 
			 LCD_ShowString(lCurX,lCurY,Empty,FRONT_COLOR);



    if(ch == '\n')
    {
        lCurX  = _Output_Text_X;
        lCurY += _Row_Height;
        if (lCurY >= 220)
            lCurY = _Output_Text_Y;
    }
    else
    {
        LCD_ShowString(lCurX, lCurY, (uint8_t*)&ch, FRONT_COLOR);
        lCurX += 8;
    }




    return ch;
}




