#include "board_drive.h"


/*
 * 函数名：SysTick_Init
 * 描述  ：启动系统滴答定时器 SysTick
 * 输入  ：无
 * 输出  ：无
 * 调用  ：外部调用 
 */
void SysTick_Init(void)		  
{
	/* SystemFrequency / 100     10ms中断一次
	   SystemFrequency / 1000    1ms中断一次
	 * SystemFrequency / 100000	 10us中断一次
	 * SystemFrequency / 1000000 1us中断一次
	 */
	if (SysTick_Config(SystemCoreClock / 200))	// ST3.5.0库版本   1s/x= a ms   1s/200=5ms
 	{ 
		/* Capture error */ 
		while (1);
	}
	// 关闭滴答定时器  
	SysTick->CTRL &= ~ SysTick_CTRL_ENABLE_Msk;
}








