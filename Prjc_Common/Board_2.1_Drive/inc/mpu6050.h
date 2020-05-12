#ifndef _MPU6050_H
#define _MPU6050_H
#include "board_drive.h"


//模式选择
#define DMP 1			




//=== 移植mpu库用到
#define BALANCE_BOARD
#define MPU6050


extern float Pitch,Roll,Yaw;
extern short gyro[3], accel[3], sensors;
extern float Pitch,Roll,Yaw; 





/**
*@brief	
*@param mode:DMP 
*@retval 		
*/
void MPU6050_Init(uint8_t mode);
int iic_writeBuffer(uint8_t addr, uint8_t reg, uint8_t len, uint8_t *data);
int iic_readBuffer(uint8_t addr, uint8_t reg, uint8_t len, uint8_t *data);







#endif

