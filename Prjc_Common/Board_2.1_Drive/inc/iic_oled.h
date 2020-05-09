#ifndef _IIC_OLED_H
#define _IIC_OLED_H

#include "board_drive.h"




#define OLED_SDA_GPIO_PORT			GPIOA
#define OLED_SDA_PIN				GPIO_Pin_0
#define OLED_SDA_GPIO_CLK			RCC_APB2Periph_GPIOA

#define OLED_SCL_GPIO_PORT			GPIOA
#define OLED_SCL_PIN				GPIO_Pin_1
#define OLED_SCL_GPIO_CLK			RCC_APB2Periph_GPIOA


#define OLED_ADDRESS		0X3C
#define OLED_IIC_WR			0
#define OLED_I2C_RD			1





void OLED_IIC_GPIO_Config(void);
bool OLED_CheckDevice(uint8_t _Address);				//=== 检测I2C总线设备OLED
void OLED_Init(void);
void OLED_Fill(unsigned char fill_Data);
void OLED_CLS(void);
void OLED_SetPos(unsigned char x, unsigned char y);
void OLED_ON(void);
void OLED_OFF(void);
void OLED_ShowStr(unsigned char x, unsigned char y, unsigned char ch[], unsigned char TextSize);
void OLED_ShowNum(unsigned char x, unsigned char y, unsigned int num, unsigned char TextSize);
void OLED_ShowCN(unsigned char x, unsigned char y, unsigned char N);
void OLED_DrawBMP(unsigned char x0,unsigned char y0,unsigned char x1,unsigned char y1,unsigned char BMP[]);
//---------------------------------------------------

static void IIC_Delay(void);
static bool IIC_Start(void);
static void IIC_Stop(void);
static void IIC_Ack(void);
static void IIC_NAck(void);
static bool IIC_WaitAck(void);
static void IIC_Send_Byte(uint8_t byte);
static uint8_t IIC_Read_Byte(void);
static bool IIC_WriteBuffer(uint8_t addr, uint8_t reg, uint8_t len, uint8_t * data);
#endif

