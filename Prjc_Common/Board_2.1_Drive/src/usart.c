#include "board_drive.h"
/* һ�����������ļ�д��֮���ǲ����޸��˵� */

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
	
	/* CPU��Сȱ�ݣ��������úã����ֱ��Send�����1���ֽڷ��Ͳ���ȥ
		�����������1���ֽ��޷���ȷ���ͳ�ȥ������ */
	USART_ClearFlag(DEBUG_USARTx, USART_FLAG_TC);     /* �巢����ɱ�־��Transmission Complete flag */
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

//�ض���c�⺯��printf������DEBUG_USART���ض�����ʹ��printf����
int fputc(int ch, FILE *f)
{
		USART_SendData(USART1, (uint8_t) ch);
		while (USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);		
		return (ch);
}

//�ض���c�⺯��scanf������DEBUG_USART����д����ʹ��scanf��getchar�Ⱥ���
int fgetc(FILE *f)
{
	while (USART_GetFlagStatus(USART1, USART_FLAG_RXNE) == RESET);
	return (int)USART_ReceiveData(USART1);
}

void USART1_IRQHandler(void)
{
	if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)			//=== �����ж�
	{
		USART_ClearFlag(USART1, USART_FLAG_RXNE);
	}
}

