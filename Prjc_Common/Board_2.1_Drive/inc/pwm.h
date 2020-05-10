/*
*********************************************************************************************************
*
*	ģ������ : PWM����ģ��
*	�ļ����� : pwm.h
*	��    �� : V1.0
*	˵    �� : 
*	�޸ļ�¼ :
*		�汾��  ����        ����      ˵��
*		V1.0    2020-04-16  juzhang_   ��
*
*********************************************************************************************************
*/
#ifndef _PWM_H
#define _PWM_H
#include "board_drive.h"


typedef struct
{
	GPIO_TypeDef* Gpio;
	uint16_t Pin;
	uint32_t Gclk;	
	
	TIM_TypeDef* Tim;
	uint32_t Tclk;
	uint16_t Arr;
	uint16_t Psc;
	uint8_t TIM_CHx;			//=== ͨ��
	uint16_t CCR_val;			//=== ȱʡΪ0
	
}ST_PWM_REGS;


extern ST_PWM_REGS PWMA,PWMB;

/* ------------------------------------------------------ */

#define PWMA_PIN		GPIO_Pin_2
#define PWMA_GPIO_PORT	GPIOA
#define PWMA_CLK		RCC_APB2Periph_GPIOA

#define PWMA_TIMx		TIM2
#define PWMA_TIM_CLK	RCC_APB1Periph_TIM2
#define PWMA_TIM_ARR	7199
#define PWMA_TIM_PSC	0

#define PWMB_PIN		GPIO_Pin_3
#define PWMB_GPIO_PORT	GPIOA
#define PWMB_CLK		RCC_APB2Periph_GPIOA

#define PWMB_TIMx		TIM2
#define PWMB_TIM_CLK	RCC_APB1Periph_TIM2
#define PWMB_TIM_ARR	7199
#define PWMB_TIM_PSC	0

/* ------------------------------------------------------ */



/****************************************************
*��  �ƣ�PWM_Init
*˵  ����������·pwm����
*��  �룺��
*��  ������
****************************************************/
void PWM_Init(void);

/****************************************************
*��  �ƣ�Set_Pwm
*˵  ��������pwmռ�ձ�
*��  �룺PWM�ṹ��
*��  ������
****************************************************/
void Set_Pwm(ST_PWM_REGS *pwm,uint16_t ccr);



#endif

