#ifndef _CONTROL_H
#define _CONTROL_H
#include "board_drive.h"

#define ANGLE_ORIGIN	0

#define PD_KP			330
#define PD_KD			1.2

#define PI_KP			70
#define PI_KI			(PI_KP/200.0)

#define MOTO_PWM_THRESHOLD			0			//=== ������ѹ������PWM���

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
	float angErr;			//=== ������
	float angRef;			//=== �Ƕ�����ֵ	

	int m1EncFdb;			//=== �������������
	int m2EncFdb;
	
	int PI_Out;
	float PI_P;
	float PI_I;
	float EncodeLeast;		//=== �ٶ��ں�
	float UltrasonicSpd;	//=== �������ں�
	float BluetoothSpd;		//=== �����ں�
	
	int Car_Set_Spd;
	int Car_Set_Pos;
	
	bool Enable;
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
void Stop_Judge(void);
/**
*@brief	�����������ݴ�������PI�ٶȿ����ں�
*@param  
*@retval 		
*/
void Ultrasonic(void);

/**
*@brief	
*@param *value:Ҫ�޷���ֵ��ָ�룬max:����ֵ��min:����ֵ
*@retval none		
*/
void Value_Limit(float *value,int max,int min);


#endif





