#include "board_drive.h"



/**
*@brief	��inv_mpu.c�ļ�ʵ��
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
*@brief	��inv_mpu.c�ļ�ʵ��
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
#define DMP
void MPU6050_Init()
{
	MPU_IIC_GPIO_Config();
	
#if defined DMP
	DMP_Init();
	
#elif defined 
	
#elif defined
	
#endif

}