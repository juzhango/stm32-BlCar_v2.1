#include "board_drive.h"

 
void init()
{
	SystemInit();
	DEBUG_Init();	
	OLED_Init();									//=== OLED��ʼ��
	Battery_Init();									//=== ��ص�ѹ�ɼ���ʼ��
	Ultra_Init();
	MPU6050_Init(DMP);
	Motor_Init();
	PWM_Init();
	Encoder_Init();
	BlCar_Control_Init();							//=== ƽ�⳵���Ƶĳ�ʼ��
	SysTick_Init();									//=== 5m �δ�ʱ���ж�
	SysTick->CTRL |=  SysTick_CTRL_ENABLE_Msk;		//=== �����δ�ʱ���ж�
	oled_show_init();
	
	
	Set_Pwm(&PWMA,650);
	Set_Pwm(&PWMB,650);
	LEFT_Back();
	RIGHT_Run();
}
void loop()
{
	while(1)
	{
		delay_ms(30);
		
		Get_Distance(&ultra);						//=== ���������

	}
}	
int main()
{
	init();
	loop();
}


