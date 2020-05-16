#include "board_drive.h"

 
void init()
{
	SystemInit();
	DEBUG_Init();	
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
}
void loop()
{
	while(1)
	{
		delay_ms(20);
		
		Get_Distance(&ultra);						//=== ���������

	}
}	
int main()
{
	init();
	loop();
}


