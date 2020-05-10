#include "board_drive.h"



/**************************************************************************
�������ܣ���ʱ�жϳ�ʼ��
��ڲ�����arr���Զ���װֵ  psc��ʱ��Ԥ��Ƶ�� 
����  ֵ����
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
	TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;//�ظ��������� 	 
	TIM_TimeBaseInit(TIM1,&TIM_TimeBaseStructure);
	
	TIM_ITConfig(TIM1, TIM_IT_Update | TIM_IT_Trigger,ENABLE);
	
	TIM_ClearFlag(TIM1, TIM_FLAG_Update);//���жϱ�־λ  
	
	TIM_Cmd(TIM1, ENABLE);  //ʹ��TIMx����  		
	
	NVIC_InitStructure.NVIC_IRQChannel = TIM1_UP_IRQn;  //TIM1�ж�  
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;  //��ռ���ȼ�3��
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;  //�����ȼ�0��
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQͨ����ʹ��
	NVIC_Init(&NVIC_InitStructure);  //����NVIC_InitStruct��ָ���Ĳ�����ʼ������NVIC�Ĵ���
	

}  



void TIM1_UP_IRQHandler(void)
{
	if (TIM_GetITStatus(TIM1, TIM_IT_Update) != RESET)
	{
		TIM_ClearITPendingBit(TIM1, TIM_IT_Update); 
		BlCar_Control();			//5m �ж�
	}
	
}






