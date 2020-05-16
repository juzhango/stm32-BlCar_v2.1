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
	float angErr;			//=== ������
	float angRef;			//=== �Ƕ�����ֵ	

	int m1EncFdb;			//=== �������������
	int m2EncFdb;
	
	
	float PI_P;
	float PI_I;
	int PI_Out;
	float Encode;			//=== �ٶ��ں�
	float EncodeLeast;		//=== �ٶ��ں�
	float UltrasonicSpd;	//=== �������ں�
	float BluetoothSpd;		//=== �����ں�
	
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





