#ifndef _ULTRA_H
#define _ULTRA_H
#include "board_drive.h"



typedef struct
{
	bool overflow;					//=== �����Ƿ񳬹��޶�ֵ
	uint8_t ultra_count;			//=== ����������Ķ�ʱ������
	float ultra_distance;			//=== ���������������ľ���
}ST_ULTRA_REGS;

extern ST_ULTRA_REGS ultra;


#define ULTRA_ZONE			100			//=== ��ʾ���ͳ����������գ���Ҫ�Ķ�ʱ������  N*(psc/APB2)��

#define ECHO_PIN			GPIO_Pin_1
#define ECHO_GPIO_PORT		GPIOB
#define ECHO_CLK			RCC_APB2Periph_GPIOB

#define TRIG_PIN			GPIO_Pin_0
#define TRIG_GPIO_PORT		GPIOB
#define TRIG_CLK			RCC_APB2Periph_GPIOB


#define ULTRA_TIMx			TIM1
#define ULTRA_TIM_CLK 		RCC_APB2Periph_TIM1
#define ULTRA_TIM_ARR		5000
#define ULTRA_TIM_PSC		720			//=== װ��һ�� t=arr*(psc/APB2)=50ms


/****************************************************
*��  �ƣ�
*˵  ����
*��  �룺
*��  ����
****************************************************/
void Ultra_Init(void);

/****************************************************
*��  �ƣ�
*˵  ����
*��  �룺
*��  ����
****************************************************/
void Ultra_Trigger(void);

/****************************************************
*��  �ƣ�void Get_Distance( ST_ULTRA_REGS *ultra)
*˵  ������ȡ���������
*��  �룺�������ṹ��
*��  ������
****************************************************/
void Get_Distance( ST_ULTRA_REGS *ultra);


#endif


