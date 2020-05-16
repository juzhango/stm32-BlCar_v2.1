#include "board_drive.h"



/**
*@brief	在inv_mpu.c文件实现
*@param  
*@retval 		
*/
int iic_writeBuffer(uint8_t addr, uint8_t reg, uint8_t len, uint8_t *data)
{
	if(MPU_IIC_WriteBuffer(addr,reg,len,data)== true)
		return 0;
	else
		return -1;
}
/**
*@brief	在inv_mpu.c文件实现
*@param  
*@retval 		
*/
int iic_readBuffer(uint8_t addr, uint8_t reg, uint8_t len, uint8_t *data)
{
	if(MPU_IIC_ReadBuffer(addr,reg,len,data) == true)
		return 0;
	else 
		return -1;
}

/**
*@brief	
*@param  
*@retval 		
*/
void MPU6050_Init()
{
	MPU_IIC_GPIO_Config();
	
	switch(IMU_MODE)
	{
		case DMP_MODE:
			DMP_Init();
			break;
		default:
			break;
	}
}
