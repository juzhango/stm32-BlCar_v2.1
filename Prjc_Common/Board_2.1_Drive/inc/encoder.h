#ifndef _ENCODER_H
#define _ENCODER_H
#include "board_drive.h"



typedef struct
{
	uint16_t encA_Pin;
	uint16_t encB_Pin;
}ST_EncPin_REGS;

typedef struct 
{
	GPIO_TypeDef* 		Gpio;
	ST_EncPin_REGS	 	Pin;
	uint32_t 			Gclk;	
	
	TIM_TypeDef* 		Tim;
	uint32_t 			Tclk;
	uint16_t 			Arr;
	uint16_t 			Psc;
	
	int 				Encoder;
	
}ST_ENCODER_REGS;

extern ST_ENCODER_REGS encM1AB,encM2AB;
/* ------------------------------------------------------ */

#define M1AB_GPIO_CLK		RCC_APB2Periph_GPIOA
#define M1AB_GPIO_PORT		GPIOA

#define M1A_PIN				GPIO_Pin_6
#define M1B_PIN				GPIO_Pin_7

#define M2AB_GPIO_CLK		RCC_APB2Periph_GPIOB
#define M2AB_GPIO_PORT		GPIOB

#define M2A_PIN				GPIO_Pin_6
#define M2B_PIN				GPIO_Pin_7



#define M1AB_TIMx		TIM3
#define M1AB_TIM_CLK	RCC_APB1Periph_TIM3
#define M1AB_TIM_ARR	0xffff-1
#define M1AB_TIM_PSC	0



#define M2AB_TIMx		TIM4
#define M2AB_TIM_CLK	RCC_APB1Periph_TIM4
#define M2AB_TIM_ARR	0xffff-1
#define M2AB_TIM_PSC	0

/* ------------------------------------------------------ */

/****************************************************
*��  �ƣ�Encoder_Init
*˵  ������ʼ��������
*��  �룺��
*��  ������
****************************************************/
void Encoder_Init(void);

/****************************************************
*��  �ƣ�Get_Encoder
*˵  ������ȡ��������ֵ
*��  �룺����������ṹ��
*��  ������
****************************************************/
void Get_Encoder(ST_ENCODER_REGS *enc1AB,ST_ENCODER_REGS *enc2AB);


#endif

