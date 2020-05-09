/*
*********************************************************************************************************
*
*	模块名称 : 电压采集模块
*	文件名称 : adc.c
*	版    本 : V1.0
*	说    明 : 
*	修改记录 :
*		版本号	日期		作者		说明
*		V1.0	2020-4-19	juzhang		无
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
*名  称：Battery_Init
*说  明：电压采集初始化
*输  入：无
*输  出：无
****************************************************/
void Battery_Init(void);
uint16_t Get_Adc(uint8_t ch);
uint16_t Get_Adc_Average(uint8_t ch,uint8_t times);

/****************************************************
*名  称：Get_Bettrty
*说  明：获取电池电压
*输  入：用于计算平均值的次数
*输  出：电池电压
****************************************************/
float Get_Bettrty(uint8_t times);

#endif


