/*
*********************************************************************************************************
*
*	模块名称 : 电机驱动模块
*	文件名称 : motor.h
*	版    本 : V1.0
*	说    明 : 平衡车的电机驱动控制引脚配置，用户只需要更改相应的引脚，其他的可以不用改。
*	修改记录 :
*		版本号  日期        作者      说明
*		V1.0    2020-04-16  juzhang_  正式发布
*
*********************************************************************************************************
*/

#ifndef _MOTOR_H
#define _MOTOR_H
#include "board_drive.h"



typedef struct
{
	GPIO_TypeDef* Gpio;
	uint16_t Pin;
	uint32_t Clk;
}ST_MOTOR_REGS;


extern ST_MOTOR_REGS AIN1,AIN2,BIN1,BIN2;

/* 定义驱动引脚 -----------------------------*/
#define AIN1_PIN		GPIO_Pin_14
#define AIN1_GPIO_PORT	GPIOB
#define AIN1_CLK		RCC_APB2Periph_GPIOB

#define AIN2_PIN		GPIO_Pin_15
#define AIN2_GPIO_PORT	GPIOB
#define AIN2_CLK		RCC_APB2Periph_GPIOB
	
#define BIN1_PIN		GPIO_Pin_13
#define BIN1_GPIO_PORT	GPIOB
#define BIN1_CLK		RCC_APB2Periph_GPIOB

#define BIN2_PIN		GPIO_Pin_12
#define BIN2_GPIO_PORT	GPIOB
#define BIN2_CLK		RCC_APB2Periph_GPIOB



#define LEFT_Run()		 	Set_Gpio_Pin(&AIN1,0); \
							Set_Gpio_Pin(&AIN2,1)
							
#define LEFT_Back()			Set_Gpio_Pin(&AIN1,1); \
							Set_Gpio_Pin(&AIN2,0); 
							
#define LEFT_Stop()			Set_Gpio_Pin(&AIN1,1); \
							Set_Gpio_Pin(&AIN2,1)

#define RIGHT_Run()		 	Set_Gpio_Pin(&BIN1,1);\
							Set_Gpio_Pin(&BIN2,0)
							
#define RIGHT_Back()		Set_Gpio_Pin(&BIN1,0);\
							Set_Gpio_Pin(&BIN2,1) 
							
#define RIGHT_Stop()		et_Gpio_Pin(&BIN1,1); \
							Set_Gpio_Pin(&BIN2,1)

/****************************************************
*名  称：Motor_Init
*功  能：初始化驱动控制引脚
*输  入：电机驱动引脚结构体
*输  出：无
****************************************************/
void Motor_Init(void);

/****************************************************
*名  称：Set_Gpio_Pin
*功  能：设置IO电平
*输  入：*p: 驱动引脚结构体地址
*	Bit：1 输出高电平
*	Bit: 0 输出低电平
*输  出：
****************************************************/
void Set_Gpio_Pin(ST_MOTOR_REGS *p,bool Bit);


#endif


