#ifndef _LED_H
#define _LED_H
#include "stm32f10x.h"

#define LED_GPIO_PORT		GPIOC
#define LED_GPIO_PIN		GPIO_Pin_13
#define LED_GPIO_CLK		RCC_APB2Periph_GPIOC



#define LED					PCout(13)
#define LED_ON() 				GPIO_ResetBits(LED_GPIO_PORT,LED_GPIO_PIN)
#define LED_OFF()				GPIO_SetBits(LED_GPIO_PORT,LED_GPIO_PIN)


void LED_Init(void);



#endif


