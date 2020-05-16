#include "board_drive.h"

float f32Power;						//=== ��ص�ѹ
STR_TIME_REG str_time_cnt;			//=== ���Ƽ���
STR_PD_PI_REG strBlCar;				//=== PID���ƽṹ��

int Moto1,Moto2;					//=== ����PWM


void BlCar_Control_Init()
{
	f32Power = 0.0;
	str_time_cnt.Time_1HZ = 0;
	str_time_cnt.Time_5HZ = 0;
	str_time_cnt.Time_10HZ = 0;
	
	strBlCar.PD_P = PD_KP;
	strBlCar.PD_D = PD_KD;
	strBlCar.PD_Out = 0;
	
	strBlCar.PI_P = PI_KP;
	strBlCar.PI_I = PI_KI;
	strBlCar.PI_Out = 0;
	
	strBlCar.Car_Set_Spd = 0;
	strBlCar.Car_Set_Pos = 0;
}
/**
*@brief	This function must be 200HZ
*@param  
*@retval 		
*/
void BlCar_Control(void)
{
	str_time_cnt.Time_1HZ++;
	str_time_cnt.Time_5HZ++;
	str_time_cnt.Time_10HZ++;

	Get_Encoder(&encM1AB,&encM2AB);				//=== ��ȡ������ֵ
	Get_IMU_Data();								//=== ��ȡ��̬
	PID_Assignment(&strBlCar);		
	PD_Upright(&strBlCar);						//=== PDֱ����
	PI_Velocity(&strBlCar);						//=== PI�ٶȻ�
	Set_MOTO();									//=== ���õ���ٶ�
	
	if(str_time_cnt.Time_10HZ >= 20){
		str_time_cnt.Time_10HZ = 0;
		Ultrasonic(); 							//=== ������
	}
	if(str_time_cnt.Time_5HZ >= 40){			//=== 5HZ��ʱ��
		str_time_cnt.Time_5HZ = 0;
		oled_show_reflesh();					//=== oled����ˢ��
	}	
	if(str_time_cnt.Time_1HZ >= 200){			//=== 1HZ��ʱ��
		str_time_cnt.Time_1HZ = 0;
		f32Power = Get_Bettrty(10);				//=== ��ȡ����
	}
}


void PID_Assignment(STR_PD_PI_REG *p)
{
	p->angle = Roll;
	p->gyro = gyro[0];
	
	p->m1EncFdb = encM1AB.Encoder;
	p->m2EncFdb = encM2AB.Encoder;
}

int PD_Upright(STR_PD_PI_REG *p)
{
	p->angErr = p->angle - ANGLE_ORIGIN;
	
	//=== out = p*angle + d*accel
	p->PD_Out = p->PD_P*p->angErr + p->PD_D*p->gyro;     
	
	return p->PD_Out;
}
int PI_Velocity(STR_PD_PI_REG *p)
{
	static float Encoder_Integral = 0;
	
	p->EncodeLeast = p->m1EncFdb + p->m2EncFdb;
	p->Encode *= 0.7;												//=== oldȨ��0.7  newȨ��0.3
	p->Encode += p->Encode + 0.3*p->EncodeLeast;
	Encoder_Integral += p->Encode;
	Encoder_Integral += p->UltrasonicSpd;							//=== �ںϳ����������ٶ�
	Value_Limit(&Encoder_Integral,15000,-15000);
	
	p->PI_Out = p->PI_P*(p->Encode - p->Car_Set_Spd) + p->PI_I*(Encoder_Integral - p->Car_Set_Pos);
	
	return p->PI_Out;
}

void Set_MOTO(void)
{
	Moto1 = strBlCar.PD_Out + strBlCar.PI_Out;
	Moto2 = strBlCar.PD_Out + strBlCar.PI_Out;
	
	if(Moto1 > 0){
		LEFT_Run();
	}
	else{
		LEFT_Back();
	}
	if(Moto2 > 0){
		RIGHT_Run();
	}	
	else{
		RIGHT_Back();
	}
	
	Set_Pwm(&PWMA,abs(Moto1));
	Set_Pwm(&PWMB,abs(Moto2));
}

void Value_Limit(float *value,int max,int min)
{
	if(*value > max){
		*value = max;
	}
	if(*value < min){
		*value = min;
	}
}


void Get_IMU_Data(void)
{
	switch(IMU_MODE){
		case DMP_MODE:
			Read_DMP();
			break;
		default:
			break;		
	}
}
void Ultrasonic(void)
{
	if(ultra.ultra_distance > 10)
		strBlCar.UltrasonicSpd = 0;
	
	if(ultra.ultra_distance <10)
		strBlCar.UltrasonicSpd = 0;
}
