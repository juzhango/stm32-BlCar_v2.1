#include "board_drive.h"

 
int main()
{
	delay_init();
	LED_Init();
	DEBUG_Init();
	OLED_Init();
	MPU6050_Init();


	
	
	
	while(1)
	{
		Read_DMP();
		delay_ms(30);
		printf("%f\t%f\t%f\r\n",Pitch,Yaw,Roll);

	}
}


