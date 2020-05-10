#include "board_drive.h"


//IO²Ù×÷º¯Êý	 
#define SCL_H         MPU_SCL_GPIO_PORT->BSRR = MPU_SCL_PIN
#define SCL_L         MPU_SCL_GPIO_PORT->BRR  = MPU_SCL_PIN 

#define SDA_H         MPU_SDA_GPIO_PORT->BSRR = MPU_SDA_PIN
#define SDA_L         MPU_SDA_GPIO_PORT->BRR  = MPU_SDA_PIN 

#define SCL_read      MPU_SCL_GPIO_PORT->IDR  & MPU_SCL_PIN
#define SDA_read      MPU_SDA_GPIO_PORT->IDR  & MPU_SDA_PIN 

#define IIC_WR		MPU_IIC_WR
#define IIC_RD		MPU_IIC_RD

void MPU_IIC_GPIO_Config(void)
{
    GPIO_InitTypeDef gpio;
    RCC_APB2PeriphClockCmd(MPU_SDA_GPIO_CLK|MPU_SCL_GPIO_CLK , ENABLE);    
    
    gpio.GPIO_Speed = GPIO_Speed_2MHz;
    gpio.GPIO_Mode = GPIO_Mode_Out_OD;	
	
	gpio.GPIO_Pin = MPU_SCL_PIN;
    GPIO_Init(MPU_SCL_GPIO_PORT, &gpio);	
	
	gpio.GPIO_Pin = MPU_SDA_PIN;
    GPIO_Init(MPU_SDA_GPIO_PORT, &gpio);
}

bool MPU_CheckDevice(uint8_t _Address)
{
	uint8_t ucAck;
	
	IIC_Start();								

	IIC_Send_Byte(_Address<<1 | IIC_WR);	
	ucAck = IIC_WaitAck();						
	IIC_Stop();							

	return ucAck;
}

/**
*@brief	
*@param  
*	@arg addr:
*	@arg reg:
*	@arg len:
*	@arg *data
*@retval ture or false		
*/
bool MPU_IIC_WriteBuffer(uint8_t addr, uint8_t reg, uint8_t len, uint8_t * data)
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
bool MPU_IIC_ReadBuffer(uint8_t addr, uint8_t reg, uint8_t len, uint8_t *buf)
{
    if (!IIC_Start())
        return false;
    IIC_Send_Byte(addr << 1 | I2C_Direction_Transmitter);
    if (!IIC_WaitAck()) {
        IIC_Stop();
        return false;
    }
    IIC_Send_Byte(reg);
    IIC_WaitAck();
    IIC_Start();
    IIC_Send_Byte(addr << 1 | I2C_Direction_Receiver);
    IIC_WaitAck();
    while (len) {
        *buf = IIC_Read_Byte();
        if (len == 1)
            IIC_NAck();
        else
            IIC_Ack();
        buf++;
        len--;
    }
    IIC_Stop();
    return true;
}
//-----------------------------------------------






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

static void IIC_Ack(void)
{
    SCL_L;
    IIC_Delay();
    SDA_L;
    IIC_Delay();
    SCL_H;
    IIC_Delay();
    SCL_L;
    IIC_Delay();
}

static void IIC_NAck(void)
{
    SCL_L;
    IIC_Delay();
    SDA_H;
    IIC_Delay();
    SCL_H;
    IIC_Delay();
    SCL_L;
    IIC_Delay();
}

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

static uint8_t IIC_Read_Byte(void)
{
    uint8_t i = 8;
    uint8_t byte = 0;

    SDA_H;
    while (i--) {
        byte <<= 1;
        SCL_L;
        IIC_Delay();
        SCL_H;
        IIC_Delay();
        if (SDA_read) {
            byte |= 0x01;
        }
    }
    SCL_L;
    return byte;
}






