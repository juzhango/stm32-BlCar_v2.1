#include "board_drive.h"

float f32Power;						//=== 电池电压
STR_TIME_REG str_time_cnt;			//=== 控制计数
STR_PD_PI_REG strBlCar;				//=== PID控制结构体

int Moto1,Moto2;					//=== 设置PWM


void BlCar_Control_Init()
{
	f32Power = 0.0;
	str_time_cnt.Time_1HZ = 0;
	str_time_cnt.Time_5HZ = 0;
	str_time_cnt.Time_10HZ = 0;
	
	strBlCar.PD_P = 0.6*PD_KP;			//=== PD直立环
	strBlCar.PD_D = 0.6*PD_KD;				
	strBlCar.PD_Out = 0;
	
	strBlCar.PI_P = PI_KP;					//=== PI速度环
	strBlCar.PI_I = PI_KI;
	strBlCar.PI_Out = 0;
	
	strBlCar.Car_Set_Spd = 0;
	strBlCar.Car_Set_Pos = 0;
	
	strBlCar.EncodeLeast = 0;
	
	strBlCar.Enable = true;
}
/**
*@brief	This function must be 200HZ		
**/
void BlCar_Control(void)
{
	str_time_cnt.Time_1HZ++;
	str_time_cnt.Time_5HZ++;
	str_time_cnt.Time_10HZ++;

	Get_Encoder(&encM1AB,&encM2AB);				//=== 获取编码器值
	Get_IMU_Data();								//=== 获取姿态
	PID_Assignment(&strBlCar);		
	PD_Upright(&strBlCar);						//=== PD直立环
	PI_Velocity(&strBlCar);						//=== PI速度环
	Stop_Judge();								//=== 停车判断
	Set_MOTO();									//=== 设置电机速度
	if(str_time_cnt.Time_10HZ >= 20){
		str_time_cnt.Time_10HZ = 0;
		Ultrasonic(); 							//=== 超声波
	}
	if(str_time_cnt.Time_5HZ >= 40){			//=== 5HZ定时器
		str_time_cnt.Time_5HZ = 0;
	}	
	if(str_time_cnt.Time_1HZ >= 200){			//=== 1HZ定时器
		str_time_cnt.Time_1HZ = 0;
		f32Power = Get_Bettrty(10);				//=== 获取电量
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
	
	/* out = p*angle + d*accel */
	p->PD_Out = p->PD_P*p->angErr + p->PD_D*p->gyro;     
	
	return p->PD_Out;
}
int PI_Velocity(STR_PD_PI_REG *p)
{
	static float Encoder,Encoder_Integral;
	
	p->EncodeLeast = (p->m1EncFdb + p->m2EncFdb);
	Encoder *= 0.7;													//=== 一阶低通滤波
	Encoder += p->EncodeLeast*0.3;
	Encoder_Integral += Encoder;
	Encoder_Integral += p->UltrasonicSpd;							//=== 融合超声波给定速度
	Value_Limit(&Encoder_Integral,15000,-15000);
	
	p->PI_Out = p->PI_P*(Encoder - p->Car_Set_Spd) + p->PI_I*(Encoder_Integral - p->Car_Set_Pos);
	
	return p->PI_Out;
}

void Set_MOTO(void)
{
	if(strBlCar.Enable){
			
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
	}
	else{
		Moto1=Moto2=0;
	}
	
	Set_Pwm(&PWMA,abs(Moto1));
	Set_Pwm(&PWMB,abs(Moto2)+5);
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
	if(ultra.ultra_distance >= 10 && ultra.ultra_distance <30){
		strBlCar.UltrasonicSpd = -5;
	}
	else if(ultra.ultra_distance > 0 && ultra.ultra_distance <10){
		strBlCar.UltrasonicSpd = 8;
	}
	else {
		strBlCar.UltrasonicSpd = 0;
	}
}
void Stop_Judge()
{
	if(fabs(strBlCar.angErr)>45)
		strBlCar.Enable = false;
	else
		strBlCar.Enable = true;
}

