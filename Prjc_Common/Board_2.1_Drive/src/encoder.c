#include "board_drive.h"

ST_ENCODER_REGS encM1AB,encM2AB;



/****************************************************
*名  称：M1AB_IRQ
*说  明：中断调用函数
*输  入：
*输  出：
****************************************************/
void M1AB_IRQ()
{

}

/****************************************************
*名  称：M2AB_IRQ
*说  明：中断调用函数
*输  入：
*输  出：
****************************************************/
void M2AB_IRQ()
{

}


void Init_ENCODER_Pram(ST_ENCODER_REGS *m1, ST_ENCODER_REGS *m2)
{
	m1->Gclk = M1AB_GPIO_CLK;
	m1->Gpio = M1AB_GPIO_PORT;
	m1->Pin->encA_Pin = M1A_PIN;
	m1->Pin->encB_Pin = M1B_PIN;
	
	m2->Gclk = M2AB_GPIO_CLK;
	m2->Gpio = M2AB_GPIO_PORT;
	m2->Pin->encA_Pin = M2A_PIN;
	m2->Pin->encB_Pin = M2B_PIN;	
	
	m1->Tclk = M1AB_TIM_CLK;
	m1->Tim = M1AB_TIMx;
	m1->Arr = M1AB_TIM_ARR;
	m1->Psc = M1AB_TIM_PSC;
	
	m2->Tclk = M2AB_TIM_CLK;
	m2->Tim = M2AB_TIMx;
	m2->Arr = M2AB_TIM_ARR;
	m2->Psc = M2AB_TIM_PSC;
}

void ENCODER_GPIO_Config()
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(encM1AB.Gclk|encM2AB.Gclk, ENABLE);
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	
//	GPIO_InitStructure.GPIO_Pin = encM1AB.Pin->encA_Pin|encM1AB.Pin->encB_Pin;
	GPIO_InitStructure.GPIO_Pin = M1A_PIN|M1B_PIN;
	GPIO_Init(encM1AB.Gpio,&GPIO_InitStructure);
	
//	GPIO_InitStructure.GPIO_Pin = encM2AB.Pin->encA_Pin|encM2AB.Pin->encB_Pin;
	GPIO_InitStructure.GPIO_Pin = M2A_PIN|M2B_PIN;
	GPIO_Init(encM2AB.Gpio,&GPIO_InitStructure);	
}


void ENCODER_TIM_IC_Config()
{
	TIM_ICInitTypeDef TIM_ICInitStructure; 
	
	TIM_ICStructInit(&TIM_ICInitStructure);
	TIM_ICInitStructure.TIM_ICFilter = 10;
	TIM_ICInit(encM1AB.Tim,&TIM_ICInitStructure);
	
	TIM_ICInit(encM2AB.Tim,&TIM_ICInitStructure);
	
	TIM_EncoderInterfaceConfig(encM1AB.Tim, TIM_EncoderMode_TI12, TIM_ICPolarity_Rising, TIM_ICPolarity_Rising);
	TIM_EncoderInterfaceConfig(encM2AB.Tim, TIM_EncoderMode_TI12, TIM_ICPolarity_Rising, TIM_ICPolarity_Rising);
}

void ENCODER_TIM_Config()
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure; 
	
	RCC_APB1PeriphClockCmd(encM1AB.Tclk|encM2AB.Tclk, ENABLE);	//=== 开启两编码器的TIM时钟
	
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseStructure.TIM_RepetitionCounter = TIM_CounterMode_Up;
	
	TIM_TimeBaseStructure.TIM_Period = encM1AB.Arr;
	TIM_TimeBaseStructure.TIM_Prescaler = encM1AB.Psc;
	TIM_TimeBaseInit(encM1AB.Tim,&TIM_TimeBaseStructure);
	
	TIM_TimeBaseStructure.TIM_Period = encM2AB.Arr;
	TIM_TimeBaseStructure.TIM_Prescaler = encM2AB.Psc;
	TIM_TimeBaseInit(encM2AB.Tim,&TIM_TimeBaseStructure);
	
	TIM_ClearFlag(encM1AB.Tim, TIM_FLAG_Update);
	TIM_ITConfig(encM2AB.Tim, TIM_IT_Update, ENABLE);
	
	TIM_ClearFlag(encM1AB.Tim, TIM_FLAG_Update);
	TIM_ITConfig(encM2AB.Tim, TIM_IT_Update, ENABLE);	
	
	TIM_Cmd(encM1AB.Tim,ENABLE);
	TIM_Cmd(encM2AB.Tim,ENABLE);
	
}

void Encoder_Init()
{
	Init_ENCODER_Pram(&encM1AB, &encM2AB);
	ENCODER_GPIO_Config();
	ENCODER_TIM_Config();
	ENCODER_TIM_IC_Config();
}
	

void Get_Encoder(ST_ENCODER_REGS *enc1AB,ST_ENCODER_REGS *enc2AB)
{ 
	enc1AB->Encoder = (short)enc1AB->Tim -> CNT;	//=== 注意脉冲值的范围short 
	enc2AB->Encoder = -(short)enc2AB->Tim -> CNT;
	enc1AB->Tim->CNT = 0;
	enc2AB->Tim->CNT = 0;
}

void TIM3_IRQHandler(void)
{ 		
	if(encM1AB.Tim->SR & 0x0001)
	{
		M1AB_IRQ();
	}
	encM1AB.Tim->SR &= ~(1<<0);	
}

void TIM4_IRQHandler(void)
{ 		
	if(encM2AB.Tim->SR & 0x0001)
	{
		M2AB_IRQ();
	}
	encM2AB.Tim->SR &= ~(1<<0);	
}

