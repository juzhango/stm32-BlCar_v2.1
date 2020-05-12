#include "board_drive.h"

 
void init()
{
	SystemInit();
	DEBUG_Init();	
	OLED_Init();									//=== OLED��ʼ��
	Battery_Init();									//=== ��ص�ѹ�ɼ���ʼ��
	Ultra_Init();
	MPU6050_Init(DMP);
	SysTick_Init();									//=== 5m �δ�ʱ���ж�
	SysTick->CTRL |=  SysTick_CTRL_ENABLE_Msk;		//=== �����δ�ʱ���ж�
	oled_show_init();
}
void loop()
{
	while(1)
	{
		delay_ms(30);
		Read_DMP();									//=== ��ȡ��̬
		Get_Distance(&ultra);						//=== ���������

	}
}	
int main()
{
	init();
	loop();
}


