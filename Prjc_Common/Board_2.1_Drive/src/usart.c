#include "board_drive.h"
/* 一般情况下这个文件写好之后是不会修改了的 */

void DEBUG_GPIO_Config()
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(DEBUG_TX_CLK|DEBUG_RX_CLK,ENABLE);
	
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Pin = DEBUG_TX_PIN;
	GPIO_Init(DEBUG_TX_PORT,&GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_InitStructure.GPIO_Pin = DEBUG_RX_PIN;
	GPIO_Init(DEBUG_RX_PORT,&GPIO_InitStructure);
}
void DEBUG_USART_Config()
{
	USART_InitTypeDef USART_InitStructure;
	RCC_APB2PeriphClockCmd(DEBUG_CLK,ENABLE);
	
	USART_InitStructure.USART_BaudRate = DEBUG_BOUND;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_Init(DEBUG_USARTx,&USART_InitStructure);
	
	USART_ITConfig(DEBUG_USARTx, USART_IT_RXNE, ENABLE);
	
	USART_Cmd(DEBUG_USARTx, ENABLE);  
	
	/* CPU的小缺陷：串口配置好，如果直接Send，则第1个字节发送不出去
		如下语句解决第1个字节无法正确发送出去的问题 */
	USART_ClearFlag(DEBUG_USARTx, USART_FLAG_TC);     /* 清发送完成标志，Transmission Complete flag */
}

void NVIC_DEBUG_Config()
{
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	
	NVIC_InitTypeDef NVIC_InitStructure;
	
	NVIC_InitStructure.NVIC_IRQChannel = DEBUG_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
}


void DEBUG_Init()
{
	DEBUG_GPIO_Config();
	DEBUG_USART_Config();
	NVIC_DEBUG_Config();
}

void USART1_Send_Byte(unsigned char byte)  
{
        USART_SendData(USART1, byte);        
        while( USART_GetFlagStatus(USART1,USART_FLAG_TC)!= SET);  
        
}
void printChar(char *s)
{
	char *p;
	p=s;
	while(*p != '\0')
	{
		USART1_Send_Byte(*p);
		p++;
	}
}

//重定向c库函数printf到串口DEBUG_USART，重定向后可使用printf函数
int fputc(int ch, FILE *f)
{
		USART_SendData(USART1, (uint8_t) ch);
		while (USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);		
		return (ch);
}

//重定向c库函数scanf到串口DEBUG_USART，重写向后可使用scanf、getchar等函数
int fgetc(FILE *f)
{
	while (USART_GetFlagStatus(USART1, USART_FLAG_RXNE) == RESET);
	return (int)USART_ReceiveData(USART1);
}

void USART1_IRQHandler(void)
{
	if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)			//=== 接收中断
	{
		USART_ClearFlag(USART1, USART_FLAG_RXNE);
	}
}

