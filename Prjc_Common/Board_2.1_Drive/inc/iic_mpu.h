#ifndef __IIC_MPU_H
#define __IIC_MPU_H
#include "board_drive.h"


#define MPU_SDA_GPIO_PORT				GPIOB
#define MPU_SDA_PIN						GPIO_Pin_9
#define MPU_SDA_GPIO_CLK				RCC_APB2Periph_GPIOB

#define MPU_SCL_GPIO_PORT				GPIOB
#define MPU_SCL_PIN						GPIO_Pin_8
#define MPU_SCL_GPIO_CLK				RCC_APB2Periph_GPIOB



#define MPU_ADDRESS			0X68
#define MPU_IIC_WR			0
#define MPU_IIC_RD			1



bool MPU_CheckDevice(uint8_t _Address);
void MPU_IIC_GPIO_Config(void);
bool MPU_IIC_WriteBuffer(uint8_t addr, uint8_t reg, uint8_t len, uint8_t * data);
bool MPU_IIC_ReadBuffer(uint8_t addr, uint8_t reg, uint8_t len, uint8_t *buf);
//-----------------------------------------------
static void IIC_Delay(void);
static bool IIC_Start(void);
static void IIC_Stop(void);
static void IIC_Ack(void);
static void IIC_NAck(void);
static bool IIC_WaitAck(void);
static void IIC_Send_Byte(uint8_t byte);
static uint8_t IIC_Read_Byte(void);



	

#endif

//------------------End of File----------------------------
