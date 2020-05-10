#include "board_drive.h"

 
void init()
{
	delay_init();
	DEBUG_Init();
	OLED_Init();			//=== OLED初始化
	Battery_Init();			//=== 电池电压采集初始化
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


