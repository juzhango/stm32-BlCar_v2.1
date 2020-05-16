#include "board_drive.h"

 
void init()
{
	SystemInit();
	DEBUG_Init();									//=== ���Դ��ڳ�ʼ��	
	OLED_Init();									//=== OLED��ʼ��
	Battery_Init();									//=== ��ص�ѹ�ɼ���ʼ��
	Ultra_Init();
	MPU6050_Init();
	Motor_Init();
	PWM_Init();
	Encoder_Init();
	BlCar_Control_Init();							//=== ƽ�⳵���Ƶĳ�ʼ��
	SysTick_Init();									//=== 5m �δ�ʱ���ж�
	SysTick->CTRL |=  SysTick_CTRL_ENABLE_Msk;		//=== �����δ�ʱ���ж�
	oled_show_init();								//=== oled��ʾ���
	LEFT_Run();
	RIGHT_Run();
	Set_Pwm(&PWMA,0);
	Set_Pwm(&PWMB,0);
}
void loop()
{
	while(1)
	{
		Get_Distance(&ultra);						//=== ���������
		oled_show_reflesh();						//=== oled����ˢ��
		delay_ms(20);
	}
}	


int main()
{
	init();
	loop();
}


