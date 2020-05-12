#ifndef _ULTRA_H
#define _ULTRA_H
#include "board_drive.h"



typedef struct
{
	bool overflow;					//=== 距离是否超过限定值
	uint8_t ultra_count;			//=== 超声波传输的定时器计数
	float ultra_distance;			//=== 超声波测量出来的距离
}ST_ULTRA_REGS;

extern ST_ULTRA_REGS ultra;


#define ULTRA_ZONE			100			//=== 表示发送超声波到接收，需要的定时器计数  N*(psc/APB2)秒

#define ECHO_PIN			GPIO_Pin_1
#define ECHO_GPIO_PORT		GPIOB
#define ECHO_CLK			RCC_APB2Periph_GPIOB

#define TRIG_PIN			GPIO_Pin_0
#define TRIG_GPIO_PORT		GPIOB
#define TRIG_CLK			RCC_APB2Periph_GPIOB


#define ULTRA_TIMx			TIM1
#define ULTRA_TIM_CLK 		RCC_APB2Periph_TIM1
#define ULTRA_TIM_ARR		5000
#define ULTRA_TIM_PSC		720			//=== 装载一次 t=arr*(psc/APB2)=50ms


/****************************************************
*名  称：
*说  明：
*输  入：
*输  出：
****************************************************/
void Ultra_Init(void);

/****************************************************
*名  称：
*说  明：
*输  入：
*输  出：
****************************************************/
void Ultra_Trigger(void);

/****************************************************
*名  称：void Get_Distance( ST_ULTRA_REGS *ultra)
*说  明：获取超声波测距
*输  入：超声波结构体
*输  出：无
****************************************************/
void Get_Distance( ST_ULTRA_REGS *ultra);


#endif


