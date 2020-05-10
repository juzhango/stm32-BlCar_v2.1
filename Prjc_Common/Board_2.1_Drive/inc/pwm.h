/*
*********************************************************************************************************
*
*	模块名称 : PWM调速模块
*	文件名称 : pwm.h
*	版    本 : V1.0
*	说    明 : 
*	修改记录 :
*		版本号  日期        作者      说明
*		V1.0    2020-04-16  juzhang_   无
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
	uint8_t TIM_CHx;			//=== 通道
	uint16_t CCR_val;			//=== 缺省为0
	
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
*名  称：PWM_Init
*说  明：配置两路pwm控制
*输  入：无
*输  出：无
****************************************************/
void PWM_Init(void);

/****************************************************
*名  称：Set_Pwm
*说  明：设置pwm占空比
*输  入：PWM结构体
*输  出：无
****************************************************/
void Set_Pwm(ST_PWM_REGS *pwm,uint16_t ccr);



#endif

