#include "board_drive.h"

 
void init()
{
	SystemInit();
	DEBUG_Init();									//=== 调试串口初始化	
	OLED_Init();									//=== OLED初始化
	Battery_Init();									//=== 电池电压采集初始化
	Ultra_Init();
	MPU6050_Init();
	Motor_Init();
	PWM_Init();
	Encoder_Init();
	BlCar_Control_Init();							//=== 平衡车控制的初始化
	SysTick_Init();									//=== 5m 滴答定时器中断
	SysTick->CTRL |=  SysTick_CTRL_ENABLE_Msk;		//=== 开启滴答定时器中断
	oled_show_init();								//=== oled显示框架
	LEFT_Run();
	RIGHT_Run();
	Set_Pwm(&PWMA,0);
	Set_Pwm(&PWMB,0);
}
void loop()
{
	while(1)
	{
		Get_Distance(&ultra);						//=== 超声波测距
		oled_show_reflesh();						//=== oled数据刷新
		delay_ms(20);
	}
}	


int main()
{
	init();
	loop();
}


