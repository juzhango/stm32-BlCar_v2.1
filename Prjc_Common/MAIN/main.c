#include "board_drive.h"

 
void init()
{
	SystemInit();
	DEBUG_Init();	
	OLED_Init();									//=== OLED初始化
	Battery_Init();									//=== 电池电压采集初始化
	Ultra_Init();
	MPU6050_Init(DMP);
	Motor_Init();
	PWM_Init();
	Encoder_Init();
	BlCar_Control_Init();							//=== 平衡车控制的初始化
	SysTick_Init();									//=== 5m 滴答定时器中断
	SysTick->CTRL |=  SysTick_CTRL_ENABLE_Msk;		//=== 开启滴答定时器中断
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
		
		Get_Distance(&ultra);						//=== 超声波测距

	}
}	
int main()
{
	init();
	loop();
}


