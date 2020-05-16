#ifndef _CONTROL_H
#define _CONTROL_H
#include "board_drive.h"

#define ANGLE_ORIGIN	8.6F

#define PD_KP			0
#define PD_KD			0

#define PI_KP			0
#define PI_KI			PI_KP/200


typedef struct
{
	uint8_t Time_1HZ;
	uint8_t Time_5HZ;
	uint8_t Time_10HZ;
}STR_TIME_REG;

typedef struct
{
	float angle;
	float gyro;
	
	int PD_Out;
	float PD_P;
	float PD_D;
	float angErr;			//=== 倾角误差
	float angRef;			//=== 角度期望值	

	int m1EncFdb;			//=== 电机编码器反馈
	int m2EncFdb;
	
	
	float PI_P;
	float PI_I;
	int PI_Out;
	float Encode;			//=== 速度融合
	float EncodeLeast;		//=== 速度融合
	float UltrasonicSpd;	//=== 超声波融合
	float BluetoothSpd;		//=== 蓝牙融合
	
	int Car_Set_Spd;
	int Car_Set_Pos;
}STR_PD_PI_REG;


extern STR_PD_PI_REG strBlCar; 


extern float f32Power;

extern void BlCar_Control(void);

void BlCar_Control_Init(void);
void BlCar_Control(void);
void PID_Assignment(STR_PD_PI_REG *p);
int PD_Upright(STR_PD_PI_REG *p);
int PI_Velocity(STR_PD_PI_REG *p);
void Set_MOTO(void);
void Get_IMU_Data(void);
/**
*@brief	超声波的数据处理，用于PI速度控制融合
*@param  
*@retval 		
*/
void Ultrasonic(void);

/**
*@brief	
*@param *value:要限幅的值的指针，max:上限值，min:下限值
*@retval none		
*/
void Value_Limit(float *value,int max,int min);


#endif





