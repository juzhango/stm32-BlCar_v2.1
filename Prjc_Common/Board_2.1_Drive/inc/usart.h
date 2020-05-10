#ifndef _USART_H
#define _USART_H
#include "board_drive.h"


#define DEBUG_TX_PORT	GPIOA
#define DEBUG_TX_PIN	GPIO_Pin_9
#define DEBUG_TX_CLK	RCC_APB2Periph_GPIOA

#define DEBUG_RX_PORT	GPIOA
#define DEBUG_RX_PIN	GPIO_Pin_10
#define DEBUG_RX_CLK	RCC_APB2Periph_GPIOA	

#define DEBUG_USARTx	USART1
#define DEBUG_CLK		RCC_APB2Periph_USART1
#define DEBUG_BOUND		115200
#define DEBUG_IRQn		USART1_IRQn


#define user_info(format, ...) 			printf(__FILE__"\t[info]:"format"\r\n", ##__VA_ARGS__)
#define user_warn(format, ...)			printf(__FILE__"\t[warn]:"format"\r\n", ##__VA_ARGS__)
#define user_error(format, ...) 		printf(__FILE__"\t[error]:"format"\r\n", ##__VA_ARGS__)






void DEBUG_Init(void);
void USART1_Send_Byte(unsigned char byte);
void printChar(char *s);




#endif

