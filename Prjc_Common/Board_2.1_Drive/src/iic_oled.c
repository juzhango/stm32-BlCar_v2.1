#include "board_drive.h"
#include "codetab.h"


//IO操作函数	 
#define SCL_H         OLED_SCL_GPIO_PORT->BSRR = OLED_SCL_PIN
#define SCL_L         OLED_SCL_GPIO_PORT->BRR  = OLED_SCL_PIN 

#define SDA_H         OLED_SDA_GPIO_PORT->BSRR = OLED_SDA_PIN
#define SDA_L         OLED_SDA_GPIO_PORT->BRR  = OLED_SDA_PIN 

#define SCL_read      OLED_SCL_GPIO_PORT->IDR  & OLED_SCL_PIN
#define SDA_read      OLED_SDA_GPIO_PORT->IDR  & OLED_SDA_PIN 

#define IIC_WR		OLED_IIC_WR
#define IIC_RD		OLED_IIC_RD

void OLED_IIC_GPIO_Config(void)
{
    GPIO_InitTypeDef gpio;
    RCC_APB2PeriphClockCmd(OLED_SDA_GPIO_CLK|OLED_SCL_GPIO_CLK , ENABLE);    
    
    gpio.GPIO_Speed = GPIO_Speed_2MHz;
    gpio.GPIO_Mode = GPIO_Mode_Out_OD;	
	
	gpio.GPIO_Pin = OLED_SCL_PIN;
    GPIO_Init(OLED_SCL_GPIO_PORT, &gpio);	
	
	gpio.GPIO_Pin = OLED_SDA_PIN;
    GPIO_Init(OLED_SDA_GPIO_PORT, &gpio);
}

bool OLED_CheckDevice(uint8_t _Address)
{
	uint8_t ucAck;
	
	IIC_Start();								

	IIC_Send_Byte(_Address<<1 | IIC_WR);	
	ucAck = IIC_WaitAck();						
	IIC_Stop();							

	return ucAck;
}



void WriteCmd(uint8_t cmd)
{
	IIC_WriteBuffer(OLED_ADDRESS,0x00,1,&cmd);
}

void WriteDat(uint8_t dat)
{
	IIC_WriteBuffer(OLED_ADDRESS,0x40,1,&dat);
}
 /**
  * @brief  OLED_Init，初始化OLED
  * @param  无
  * @retval 无
  */
void OLED_Init(void)
{
	OLED_IIC_GPIO_Config();
	delay_ms(999);		// 1s,这里的延时很重要,上电后延时，没有错误的冗余设计
	
	WriteCmd(0xAE); //display off
	WriteCmd(0x20);	//Set Memory Addressing Mode	
	WriteCmd(0x10);	//00,Horizontal Addressing Mode;01,Vertical Addressing Mode;10,Page Addressing Mode (RESET);11,Invalid
	WriteCmd(0xb0);	//Set Page Start Address for Page Addressing Mode,0-7
	WriteCmd(0xc8);	//Set COM Output Scan Direction
	WriteCmd(0x00); //---set low column address
	WriteCmd(0x10); //---set high column address
	WriteCmd(0x40); //--set start line address
	WriteCmd(0x81); //--set contrast control register
	WriteCmd(0xff); //亮度调节 0x00~0xff
	WriteCmd(0xa1); //--set segment re-map 0 to 127
	WriteCmd(0xa6); //--set normal display
	WriteCmd(0xa8); //--set multiplex ratio(1 to 64)
	WriteCmd(0x3F); //
	WriteCmd(0xa4); //0xa4,Output follows RAM content;0xa5,Output ignores RAM content
	WriteCmd(0xd3); //-set display offset
	WriteCmd(0x00); //-not offset
	WriteCmd(0xd5); //--set display clock divide ratio/oscillator frequency
	WriteCmd(0xf0); //--set divide ratio
	WriteCmd(0xd9); //--set pre-charge period
	WriteCmd(0x22); //
	WriteCmd(0xda); //--set com pins hardware configuration
	WriteCmd(0x12);
	WriteCmd(0xdb); //--set vcomh
	WriteCmd(0x20); //0x20,0.77xVcc
	WriteCmd(0x8d); //--set DC-DC enable
	WriteCmd(0x14); //
	WriteCmd(0xaf); //--turn on oled panel
	OLED_CLS();
}

 /**
  * @brief  OLED_SetPos，设置光标
  * @param  x,光标x位置
  *			y,光标y位置
  * @retval 无
  */
void OLED_SetPos(unsigned char x, unsigned char y) //设置起始点坐标
{ 
	WriteCmd(0xb0+y);
	WriteCmd(((x&0xf0)>>4)|0x10);
	WriteCmd((x&0x0f)|0x01);
}

 /**
  * @brief  OLED_Fill，填充整个屏幕
  * @param  fill_Data:要填充的数据
	* @retval 无
  */
void OLED_Fill(unsigned char fill_Data)//全屏填充
{
	unsigned char m,n;
	for(m=0;m<8;m++)
	{
		WriteCmd(0xb0+m);		//page0-page1
		WriteCmd(0x00);		//low column start address
		WriteCmd(0x10);		//high column start address
		for(n=0;n<128;n++)
		{
			WriteDat(fill_Data);
		}
	}
}

 /**
  * @brief  OLED_CLS，清屏
  * @param  无
	* @retval 无
  */
void OLED_CLS(void)//清屏
{
	OLED_Fill(0x00);
}


 /**
  * @brief  OLED_ON，将OLED从休眠中唤醒
  * @param  无
	* @retval 无
  */
void OLED_ON(void)
{
	WriteCmd(0X8D);  //设置电荷泵
	WriteCmd(0X14);  //开启电荷泵
	WriteCmd(0XAF);  //OLED唤醒
}


 /**
  * @brief  OLED_OFF，让OLED休眠 -- 休眠模式下,OLED功耗不到10uA
  * @param  无
  * @retval 无
  */
void OLED_OFF(void)
{
	WriteCmd(0X8D);  //设置电荷泵
	WriteCmd(0X10);  //关闭电荷泵
	WriteCmd(0XAE);  //OLED休眠
}


 /**
  * @brief  OLED_ShowStr，显示codetab.h中的ASCII字符,有6*8和8*16可选择
  * @param  x,y : 起始点坐标(x:0~127, y:0~7);
	*					ch[] :- 要显示的字符串; 
	*					TextSize : 字符大小(1:6*8 ; 2:8*16)
	* @retval 无
  */
void OLED_ShowStr(unsigned char x, unsigned char y, unsigned char ch[], unsigned char TextSize)
{
	unsigned char c = 0,i = 0,j = 0;
	switch(TextSize)
	{
		case 1:
		{
			while(ch[j] != '\0')
			{
				c = ch[j] - 32;
				if(x > 126)
				{
					x = 0;
					y++;
				}
				OLED_SetPos(x,y);
				for(i=0;i<6;i++)
					WriteDat(F6x8[c][i]);
				x += 6;
				j++;
			}
		}break;
		case 2:
		{
			while(ch[j] != '\0')
			{
				c = ch[j] - 32;
				if(x > 120)
				{
					x = 0;
					y++;
				}
				OLED_SetPos(x,y);
				for(i=0;i<8;i++)
					WriteDat(F8X16[c*16+i]);
				OLED_SetPos(x,y+1);
				for(i=0;i<8;i++)
					WriteDat(F8X16[c*16+i+8]);
				x += 8;
				j++;
			}
		}break;
	}
}

 /**
  * @brief  OLED_ShowStr，显示codetab.h中的ASCII字符,有6*8和8*16可选择
  * @param  x,y : 起始点坐标(x:0~127, y:0~7);
  *					ch[] :- 要显示的字符串; 
  *					TextSize : 字符大小(1:6*8 ; 2:8*16)
  * @retval 无
  */
void OLED_ShowNum(unsigned char x, unsigned char y, unsigned int num, unsigned char TextSize)
{
	char str[16];
	sprintf(str,"%d",num);
	OLED_ShowStr(x,y,(unsigned char *)str,TextSize);
}

 /**
  * @brief  OLED_ShowCN，显示codetab.h中的汉字,16*16点阵
  * @param  x,y: 起始点坐标(x:0~127, y:0~7); 
	*					N:汉字在codetab.h中的索引
	* @retval 无
  */
void OLED_ShowCN(unsigned char x, unsigned char y, unsigned char N)
{
	unsigned char wm=0;
	unsigned int  adder=32*N;
	OLED_SetPos(x , y);
	for(wm = 0;wm < 16;wm++)
	{
		WriteDat(F16x16[adder]);
		adder += 1;
	}
	OLED_SetPos(x,y + 1);
	for(wm = 0;wm < 16;wm++)
	{
		WriteDat(F16x16[adder]);
		adder += 1;
	}
}



 /**
  * @brief  OLED_DrawBMP，显示BMP位图
  * @param  x0,y0 :起始点坐标(x0:0~127, y0:0~7);
	*					x1,y1 : 起点对角线(结束点)的坐标(x1:1~128,y1:1~8)
	* @retval 无
  */
void OLED_DrawBMP(unsigned char x0,unsigned char y0,unsigned char x1,unsigned char y1,unsigned char BMP[])
{
	unsigned int j=0;
	unsigned char x,y;

  if(y1%8==0)
		y = y1/8;
  else
		y = y1/8 + 1;
	for(y=y0;y<y1;y++)
	{
		OLED_SetPos(x0,y);
    for(x=x0;x<x1;x++)
		{
			WriteDat(BMP[j++]);
		}
	}
}

//---------------------------------------------------

/**
*@brief	
*@param  
*	@arg addr:
*	@arg reg:
*	@arg len:
*	@arg *data
*@retval ture or false		
*/
static bool IIC_WriteBuffer(uint8_t addr, uint8_t reg, uint8_t len, uint8_t * data)
{
    int i;
    if (!IIC_Start())
        return false;
    IIC_Send_Byte(addr << 1 | IIC_WR);
    if (!IIC_WaitAck()) {
        IIC_Stop();
        return false;
    }
    IIC_Send_Byte(reg);
    IIC_WaitAck();
    for (i = 0; i < len; i++) {
        IIC_Send_Byte(data[i]);
        if (!IIC_WaitAck()) {
            IIC_Stop();
            return false;
        }
    }
    IIC_Stop();
    return true;
}

/**
*@brief	
*@param  
*	@arg addr:
*	@arg reg:
*	@arg len:
*	@arg *buf
*@retval ture or false		
*/
//static bool IIC_ReadBuffer(uint8_t addr, uint8_t reg, uint8_t len, uint8_t *buf)
//{
//    if (!IIC_Start())
//        return false;
//    IIC_Send_Byte(addr << 1 | I2C_Direction_Transmitter);
//    if (!IIC_WaitAck()) {
//        IIC_Stop();
//        return false;
//    }
//    IIC_Send_Byte(reg);
//    IIC_WaitAck();
//    IIC_Start();
//    IIC_Send_Byte(addr << 1 | I2C_Direction_Receiver);
//    IIC_WaitAck();
//    while (len) {
//        *buf = IIC_Read_Byte();
//        if (len == 1)
//            IIC_NAck();
//        else
//            IIC_Ack();
//        buf++;
//        len--;
//    }
//    IIC_Stop();
//    return true;
//}


static void IIC_Delay(void)
{
	delay_us(1);
}

static bool IIC_Start(void)
{
	SDA_H;
	SCL_H;
	IIC_Delay();
	if (!SDA_read)
		return false;
	SDA_L;
	IIC_Delay();
	if (SDA_read)
		return false;
	SDA_L;
	IIC_Delay();
	return true;
}

static void IIC_Stop(void)
{
    SCL_L;
    IIC_Delay();
    SDA_L;
    IIC_Delay();
    SCL_H;
    IIC_Delay();
    SDA_H;
    IIC_Delay();
}

//static void IIC_Ack(void)
//{
//    SCL_L;
//    IIC_Delay();
//    SDA_L;
//    IIC_Delay();
//    SCL_H;
//    IIC_Delay();
//    SCL_L;
//    IIC_Delay();
//}

//static void IIC_NAck(void)
//{
//    SCL_L;
//    IIC_Delay();
//    SDA_H;
//    IIC_Delay();
//    SCL_H;
//    IIC_Delay();
//    SCL_L;
//    IIC_Delay();
//}

static bool IIC_WaitAck(void)
{
    SCL_L;
    IIC_Delay();
    SDA_H;
    IIC_Delay();
    SCL_H;
    IIC_Delay();
    if (SDA_read) {
        SCL_L;
        return false;
    }
    SCL_L;
    return true;
}

static void IIC_Send_Byte(uint8_t byte)
{
    uint8_t i = 8;
    while (i--) {
        SCL_L;
        IIC_Delay();
        if (byte & 0x80)
            SDA_H;
        else
            SDA_L;
        byte <<= 1;
        IIC_Delay();
        SCL_H;
        IIC_Delay();
    }
    SCL_L;
}

//static uint8_t IIC_Read_Byte(void)
//{
//    uint8_t i = 8;
//    uint8_t byte = 0;

//    SDA_H;
//    while (i--) {
//        byte <<= 1;
//        SCL_L;
//        IIC_Delay();
//        SCL_H;
//        IIC_Delay();
//        if (SDA_read) {
//            byte |= 0x01;
//        }
//    }
//    SCL_L;
//    return byte;
//}




////==========分割线==========================================	



