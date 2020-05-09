#ifndef _MPU6050_H
#define _MPU6050_H
#include "board_drive.h"


#define BALANCE_BOARD
#define MPU6050


extern float Pitch,Roll,Yaw;
extern short gyro[3], accel[3], sensors;
extern float Pitch,Roll,Yaw; 






void MPU6050_Init(void);
int iic_writeBuffer(uint8_t addr, uint8_t reg, uint8_t len, uint8_t *data);
int iic_readBuffer(uint8_t addr, uint8_t reg, uint8_t len, uint8_t *data);







#endif

