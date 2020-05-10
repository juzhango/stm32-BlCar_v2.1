#include "board_drive.h"

 
void init()
{
	SysTick_Init();			//=== �δ�ʱ����ʼ��
	delay_init();
	DEBUG_Init();
	OLED_Init();			//=== OLED��ʼ��
	Battery_Init();			//=== ��ص�ѹ�ɼ���ʼ��
	Ultra_Init();			//=== ����������ʼ��
	
	SysTick->CTRL |=  SysTick_CTRL_ENABLE_Msk;	 //ʹ�����㷨ʱ��
}
void loop()
{
	while(1)
	{
		
	}
}	
int main()
{
	init();
	loop();
}


