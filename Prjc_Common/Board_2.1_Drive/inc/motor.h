/*
*********************************************************************************************************
*
*	ģ������ : �������ģ��
*	�ļ����� : motor.h
*	��    �� : V1.0
*	˵    �� : ƽ�⳵�ĵ�����������������ã��û�ֻ��Ҫ������Ӧ�����ţ������Ŀ��Բ��øġ�
*	�޸ļ�¼ :
*		�汾��  ����        ����      ˵��
*		V1.0    2020-04-16  juzhang_  ��ʽ����
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

/* ������������ -----------------------------*/
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
*��  �ƣ�Motor_Init
*��  �ܣ���ʼ��������������
*��  �룺����������Žṹ��
*��  ������
****************************************************/
void Motor_Init(void);

/****************************************************
*��  �ƣ�Set_Gpio_Pin
*��  �ܣ�����IO��ƽ
*��  �룺*p: �������Žṹ���ַ
*	Bit��1 ����ߵ�ƽ
*	Bit: 0 ����͵�ƽ
*��  ����
****************************************************/
void Set_Gpio_Pin(ST_MOTOR_REGS *p,bool Bit);


#endif


