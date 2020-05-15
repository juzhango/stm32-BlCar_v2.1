#include "board_drive.h"

/* 一般情况下这个文件写好之后是不会修改了的 */

ST_PWM_REGS PWMA,PWMB;



void Init_PWM_Pram(ST_PWM_REGS *pwmA, ST_PWM_REGS *pwmB)
{
	pwmA->Gclk = PWMA_CLK;
	pwmA->Gpio = PWMA_GPIO_PORT;
	pwmA->Pin = PWMA_PIN;
	
	pwmA->Tim = PWMA_TIMx;
	pwmA->Tclk = PWMA_TIM_CLK;
	pwmA->Arr = PWMA_TIM_ARR;
	pwmA->Psc = PWMA_TIM_PSC;
	pwmA->CCR_val = 0;
	pwmA->TIM_CHx = 3;
	
	pwmB->Gclk = PWMB_CLK;
	pwmB->Gpio = PWMB_GPIO_PORT;
	pwmB->Pin = PWMB_PIN;
	
	pwmB->Tim = PWMB_TIMx;
	pwmB->Tclk = PWMB_TIM_CLK;
	pwmB->Arr = PWMB_TIM_ARR;
	pwmB->Psc = PWMB_TIM_PSC;
	pwmB->CCR_val = 0;
	pwmB->TIM_CHx = 4;
}


void PWM_GPIO_Config()
{	
	GPIO_InitTypeDef gpio_initstruct;
	RCC_APB2PeriphClockCmd(PWMA.Gclk|PWMB.Gclk,ENABLE);
	
	gpio_initstruct.GPIO_Mode = GPIO_Mode_AF_PP;
	gpio_initstruct.GPIO_Speed = GPIO_Speed_50MHz;
	
	gpio_initstruct.GPIO_Pin = PWMA.Pin;
	GPIO_Init(PWMA.Gpio,&gpio_initstruct);	
	
	gpio_initstruct.GPIO_Pin = PWMB.Pin;
	GPIO_Init(PWMB_GPIO_PORT,&gpio_initstruct);	
	
	GPIO_SetBits(PWMA.Gpio,PWMA.Pin);
	GPIO_SetBits(PWMB.Gpio,PWMB.Pin);
}	

void PWM_TIM_OC_Init(ST_PWM_REGS *pwm)
{
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_Pulse = pwm->CCR_val;
	
	switch(pwm->TIM_CHx)
	{
		case(1):
			TIM_OC1Init(pwm->Tim, &TIM_OCInitStructure);
			TIM_OC1PreloadConfig(pwm->Tim, TIM_OCPreload_Enable);
			break;
		case(2):
			TIM_OC2Init(pwm->Tim, &TIM_OCInitStructure);
			TIM_OC2PreloadConfig(pwm->Tim, TIM_OCPreload_Enable);
			break;
		case(3):
			TIM_OC3Init(pwm->Tim, &TIM_OCInitStructure);
			TIM_OC3PreloadConfig(pwm->Tim, TIM_OCPreload_Enable);
			break;
		case(4):
			TIM_OC4Init(pwm->Tim, &TIM_OCInitStructure);
			TIM_OC4PreloadConfig(pwm->Tim, TIM_OCPreload_Enable);
			break;
		default:
			break;		
	}
}

void PWM_TIM_Config()
{
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
		
	RCC_APB1PeriphClockCmd(PWMA.Tclk|PWMB.Tclk, ENABLE);
	
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;

	TIM_TimeBaseStructure.TIM_Period = PWMA_TIM_ARR;
	TIM_TimeBaseStructure.TIM_Prescaler = PWMA_TIM_PSC;
	TIM_TimeBaseInit(PWMA_TIMx,&TIM_TimeBaseStructure);
		
	TIM_TimeBaseStructure.TIM_Period = PWMB_TIM_ARR;
	TIM_TimeBaseStructure.TIM_Prescaler = PWMB_TIM_PSC;
	TIM_TimeBaseInit(PWMB_TIMx,&TIM_TimeBaseStructure);
	
	TIM_ARRPreloadConfig(PWMA.Tim,ENABLE);
	TIM_Cmd(PWMA.Tim,ENABLE);
	
	TIM_ARRPreloadConfig(PWMA.Tim,ENABLE);
	TIM_Cmd(PWMA.Tim,ENABLE);
	
	/* PWM ----------------------------------*/
	PWM_TIM_OC_Init(&PWMA);
	PWM_TIM_OC_Init(&PWMB);	
}





void PWM_Init()
{
	Init_PWM_Pram(&PWMA, &PWMB);	//=== 相关参数配置
	PWM_GPIO_Config();				//=== 相关GPIO配置
	PWM_TIM_Config();				//=== 定时器与PWM输出配置
}


void Set_Pwm(ST_PWM_REGS *pwm,uint16_t ccr)
{
	pwm->CCR_val = ccr;
	
	//=== 限幅
	if(pwm->CCR_val > pwm->Arr){
		pwm->CCR_val = pwm->Arr;
	}

	switch (pwm->TIM_CHx)
	{
		case (1):
			TIM_SetCompare1(pwm->Tim, pwm->CCR_val);
			break;
		case (2):
			TIM_SetCompare2(pwm->Tim, pwm->CCR_val);
			break;
		case (3):
			TIM_SetCompare3(pwm->Tim, pwm->CCR_val);
			break;
		case (4):
			TIM_SetCompare4(pwm->Tim, pwm->CCR_val);
			break;	
		default:
			break;
	}
}











