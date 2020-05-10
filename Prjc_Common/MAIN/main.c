#include "board_drive.h"

 
void init()
{
	delay_init();
	DEBUG_Init();
	OLED_Init();			//=== OLED��ʼ��
	Battery_Init();			//=== ��ص�ѹ�ɼ���ʼ��
	Timer1_Init(50,7199);
}
void loop()
{
	while(1)
	{
		printf("%f\r\n",f32Power);
		delay_ms(500);
	}
}	
int main()
{
	init();
	loop();
}


