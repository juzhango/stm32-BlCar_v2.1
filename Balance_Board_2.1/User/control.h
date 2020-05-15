#ifndef _CONTROL_H
#define _CONTROL_H
#include "board_drive.h"

#define ANGLE_ORIGIN	8.6F

#define PD_KP			1
#define PD_KD			1

#define PI_KP			1
#define PI_KI			1


typedef struct
{
	uint8_t Time_1HZ;
	uint8_t Time_5HZ;
}STR_TIME_REG;



typedef struct
{
	float angle;
	float gyro;
	
	int PD_Out;
	float PD_P;
	float PD_D;
	float angErr;
	

//	int m1encRef;
//	int m2encRef;
//	
	int m1encFdb;
	int m2encFdb;
	
	
	float PI_P;
	float PI_I;
	int PI_Out;
	float Encode;
	float EncodeLeast;
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


/**
*@brief	
*@param *value:要限幅的值的指针，max:上限值，min:下限值
*@retval none		
*/
void Value_Limit(float *value,int max,int min);


#endif





