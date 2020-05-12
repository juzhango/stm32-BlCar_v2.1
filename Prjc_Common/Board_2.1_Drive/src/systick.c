#include "board_drive.h"


/*
 * ��������SysTick_Init
 * ����  ������ϵͳ�δ�ʱ�� SysTick
 * ����  ����
 * ���  ����
 * ����  ���ⲿ���� 
 */
void SysTick_Init(void)		  
{
	/* SystemFrequency / 100     10ms�ж�һ��
	   SystemFrequency / 1000    1ms�ж�һ��
	 * SystemFrequency / 100000	 10us�ж�һ��
	 * SystemFrequency / 1000000 1us�ж�һ��
	 */
	if (SysTick_Config(SystemCoreClock / 200))	// ST3.5.0��汾   1s/x= a ms   1s/200=5ms
 	{ 
		/* Capture error */ 
		while (1);
	}
	// �رյδ�ʱ��  
	SysTick->CTRL &= ~ SysTick_CTRL_ENABLE_Msk;
}








