#include "board_drive.h"



/**************************************************************************
函数功能：定时中断初始化
入口参数：arr：自动重装值  psc：时钟预分频数 
返回  值：无
**************************************************************************/
void Timer1_Init(u16 arr,u16 psc)  
{  
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;  
	NVIC_InitTypeDef NVIC_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1,ENABLE);
	
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseStructure.TIM_Period = arr;
	TIM_TimeBaseStructure.TIM_Prescaler = psc;
	TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;//重复计数设置 	 
	TIM_TimeBaseInit(TIM1,&TIM_TimeBaseStructure);
	
	TIM_ITConfig(TIM1, TIM_IT_Update | TIM_IT_Trigger,ENABLE);
	
	TIM_ClearFlag(TIM1, TIM_FLAG_Update);//清中断标志位  
	
	TIM_Cmd(TIM1, ENABLE);  //使能TIMx外设  		
	
	NVIC_InitStructure.NVIC_IRQChannel = TIM1_UP_IRQn;  //TIM1中断  
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;  //先占优先级3级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;  //从优先级0级
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQ通道被使能
	NVIC_Init(&NVIC_InitStructure);  //根据NVIC_InitStruct中指定的参数初始化外设NVIC寄存器
	

}  



void TIM1_UP_IRQHandler(void)
{
	if (TIM_GetITStatus(TIM1, TIM_IT_Update) != RESET)
	{
		TIM_ClearITPendingBit(TIM1, TIM_IT_Update); 
		BlCar_Control();			//5m 中断
	}
	
}






