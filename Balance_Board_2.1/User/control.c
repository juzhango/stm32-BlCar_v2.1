#include "board_drive.h"

float f32Power;					//电压
STR_TIME_REG str_time_cnt;			//计数

void BlCar_Control_Init()
{
	f32Power = 0.0;
	str_time_cnt.Time_1HZ = 0;
	str_time_cnt.Time_5HZ = 0;
}
/**
*@brief	This function must be 200HZ
*@param  
*@retval 		
*/
void BlCar_Control(void)
{
	str_time_cnt.Time_1HZ++;
	str_time_cnt.Time_5HZ++;

	if(str_time_cnt.Time_5HZ >= 40)				//=== 200ms
	{
		str_time_cnt.Time_5HZ = 0;
		oled_show_reflesh();
	}	
	
	if(str_time_cnt.Time_1HZ >= 200)			//=== 1000ms
	{
		str_time_cnt.Time_1HZ = 0;
		f32Power = Get_Bettrty(10);				//=== 获取电量
		oled_show_init();	
	}
}

