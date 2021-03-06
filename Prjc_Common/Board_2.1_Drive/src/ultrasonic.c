#include "board_drive.h"

		
ST_ULTRA_REGS ultra;

void Init_Ultra_Pram(ST_ULTRA_REGS *ultra)
{
	ultra->overflow = false;
	ultra->ultra_count = 0;
	ultra->ultra_distance = 0.0;
}
void Ultra_TIM_Config()
{   
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1,ENABLE);	
	
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseStructure.TIM_Period = 5000;
	TIM_TimeBaseStructure.TIM_Prescaler = 719;				//=== 一次是 0.01ms   720/Sysclk = 0.00001s
	TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;//重复计数设置 	 
	TIM_TimeBaseInit(TIM1,&TIM_TimeBaseStructure);
	
	TIM_ITConfig(TIM1, TIM_IT_Update | TIM_IT_Trigger,ENABLE);
	
	TIM_ClearFlag(TIM1, TIM_FLAG_Update);//清中断标志位  
			
	NVIC_InitStructure.NVIC_IRQChannel = TIM1_UP_IRQn;  //TIM1中断  
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3;  //先占优先级3级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;  //从优先级0级
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQ通道被使能
	NVIC_Init(&NVIC_InitStructure);  //根据NVIC_InitStruct中指定的参数初始化外设NVIC寄存器	
}

void Ultra_GPIO_Config()
{
	GPIO_InitTypeDef gpio_initstruct;
	RCC_APB2PeriphClockCmd(ECHO_CLK|TRIG_CLK,ENABLE);
	
	gpio_initstruct.GPIO_Speed = GPIO_Speed_50MHz;
	
	gpio_initstruct.GPIO_Mode = GPIO_Mode_IPD;
	gpio_initstruct.GPIO_Pin = ECHO_PIN;
	GPIO_Init(ECHO_GPIO_PORT,&gpio_initstruct);
	
	gpio_initstruct.GPIO_Mode = GPIO_Mode_Out_PP;
	gpio_initstruct.GPIO_Pin = TRIG_PIN;
	GPIO_Init(TRIG_GPIO_PORT,&gpio_initstruct);
}

void Ultra_EXTI_Config()
{
	EXTI_InitTypeDef EXTI_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB|RCC_APB2Periph_AFIO, ENABLE);
	
    GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource1);
	
    EXTI_InitStructure.EXTI_Line=EXTI_Line1;
    EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising_Falling;
    EXTI_InitStructure.EXTI_LineCmd = ENABLE;
    EXTI_Init(&EXTI_InitStructure);			
}


void Ultra_NVIC_Config()
{
	NVIC_InitTypeDef NVIC_InitStructure;
	
	NVIC_InitStructure.NVIC_IRQChannel = EXTI1_IRQn;		
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3;	
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;					
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;							
    NVIC_Init(&NVIC_InitStructure);  
}

void Ultra_Init()
{
	Init_Ultra_Pram(&ultra);
	Ultra_TIM_Config();
	Ultra_GPIO_Config();
	Ultra_EXTI_Config();
	Ultra_NVIC_Config();
	
}


void Ultra_IRQ()
{
	if(GPIO_ReadInputDataBit(ECHO_GPIO_PORT,ECHO_PIN) == 1) //=== 上升沿中断为发出超声波
	{
		TIM_SetCounter(ULTRA_TIMx,0);
		TIM_Cmd(ULTRA_TIMx,ENABLE);
	}
	else													//=== 下降沿中断为收到超声波
	{
		if(TIM_GetCounter(ULTRA_TIMx) > ULTRA_ZONE)	
		{
			TIM_SetCounter(ULTRA_TIMx,0);
			ultra.overflow = true;
			return;
		}
		ultra.ultra_count = TIM_GetCounter(ULTRA_TIMx);
		TIM_Cmd(ULTRA_TIMx,DISABLE);	
		ultra.overflow = false;
	}
}
void EXTI1_IRQHandler(void)
{
	if(EXTI_GetITStatus(EXTI_Line1) != RESET)
	{
		Ultra_IRQ();
		
		EXTI_ClearITPendingBit(EXTI_Line1);
	}
}

void TIM1_UP_IRQHandler(void)   //TIM中断
{
	if(TIM_GetITStatus(ULTRA_TIMx, TIM_IT_Update) != RESET) 
	{
		TIM_ClearITPendingBit(ULTRA_TIMx, TIM_IT_Update);  
	}
}

void Ultra_Trigger(void)
{
	GPIO_SetBits(TRIG_GPIO_PORT,TRIG_PIN); 		  
	delay_us(5);		                   
	GPIO_ResetBits(TRIG_GPIO_PORT,TRIG_PIN);	  
}

void Get_Distance( ST_ULTRA_REGS *ultra)	//=== 超声波速度 340m/s	34cm/ms
{
	Ultra_Trigger();
	if(ultra->overflow == true)		
	{
		ultra->ultra_distance = 100.0;
	}
	else
	{
		ultra->ultra_distance = ultra->ultra_count*0.01*34-3.3;  //--- 距离 = 计次 * 毫秒/次 * 厘米/毫秒 - 误差
	}
}
