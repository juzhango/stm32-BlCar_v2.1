#include "board_drive.h"

/* 一般情况下这个文件写好之后是不会修改了的 */



ST_MOTOR_REGS AIN1,AIN2,BIN1,BIN2;		//=== 用于控制电机驱动的四个引脚

void Init_MOTOR_Pram()
{
	AIN1.Clk = AIN1_CLK;
	AIN1.Gpio = AIN1_GPIO_PORT;
	AIN1.Pin = AIN1_PIN;
	
	AIN2.Clk = AIN2_CLK;
	AIN2.Gpio = AIN2_GPIO_PORT;
	AIN2.Pin = AIN2_PIN;
	
	BIN1.Clk = BIN1_CLK;
	BIN1.Gpio = BIN1_GPIO_PORT;
	BIN1.Pin = BIN1_PIN;
	
	BIN2.Clk = BIN2_CLK;
	BIN2.Gpio = BIN2_GPIO_PORT;
	BIN2.Pin = BIN2_PIN;
}

void Motor_Init()
{
	Init_MOTOR_Pram();
	
	GPIO_InitTypeDef gpio_initstruct;
	RCC_APB2PeriphClockCmd(AIN1.Clk|AIN2.Clk|BIN1.Clk|BIN2.Clk,ENABLE);
	
	gpio_initstruct.GPIO_Mode = GPIO_Mode_Out_PP;
	gpio_initstruct.GPIO_Speed = GPIO_Speed_50MHz;
	
	gpio_initstruct.GPIO_Pin = AIN1.Pin;
	GPIO_Init(AIN1_GPIO_PORT,&gpio_initstruct);
	
	gpio_initstruct.GPIO_Pin = AIN2.Pin;
	GPIO_Init(AIN2_GPIO_PORT,&gpio_initstruct);
	
	gpio_initstruct.GPIO_Pin = BIN1.Pin;
	GPIO_Init(BIN1_GPIO_PORT,&gpio_initstruct);
	
	gpio_initstruct.GPIO_Pin = BIN2.Pin;
	GPIO_Init(BIN2_GPIO_PORT,&gpio_initstruct);	
}

void Set_Gpio_Pin(ST_MOTOR_REGS *p, bool Bit)
{
	if(Bit != RESET)
	{
		GPIO_SetBits(p->Gpio,p->Pin);
	}
	else
	{
		GPIO_ResetBits(p->Gpio,p->Pin);
	}
}


