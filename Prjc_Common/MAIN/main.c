#include "board_drive.h"

 
void init()
{
	SysTick_Init();			//=== 滴答定时器初始化
	delay_init();
	DEBUG_Init();
	OLED_Init();			//=== OLED初始化
	Battery_Init();			//=== 电池电压采集初始化
	Ultra_Init();			//=== 超声波测距初始化
	
	SysTick->CTRL |=  SysTick_CTRL_ENABLE_Msk;	 //使能总算法时钟
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


