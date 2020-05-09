/*
*********************************************************************************************************
*
*	ģ������ : ��ѹ�ɼ�ģ��
*	�ļ����� : adc.c
*	��    �� : V1.0
*	˵    �� : 
*	�޸ļ�¼ :
*		�汾��	����		����		˵��
*		V1.0	2020-4-19	juzhang		��
*
*********************************************************************************************************
*/

#ifndef _ADC_H
#define _ADC_H
#include "board_drive.h"


#define ADC_GPIO_PORT		GPIOA
#define ADC_GPIO_PIN		GPIO_Pin_4
#define ADC_GPIO_CLK		RCC_APB2Periph_GPIOA

#define ADC_CLK				RCC_APB2Periph_ADC1
#define ADCx				ADC1
#define ADC_CH				ADC_Channel_4

/****************************************************
*��  �ƣ�Battery_Init
*˵  ������ѹ�ɼ���ʼ��
*��  �룺��
*��  ������
****************************************************/
void Battery_Init(void);
uint16_t Get_Adc(uint8_t ch);
uint16_t Get_Adc_Average(uint8_t ch,uint8_t times);

/****************************************************
*��  �ƣ�Get_Bettrty
*˵  ������ȡ��ص�ѹ
*��  �룺���ڼ���ƽ��ֵ�Ĵ���
*��  ������ص�ѹ
****************************************************/
float Get_Bettrty(uint8_t times);

#endif


