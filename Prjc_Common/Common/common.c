#include "common.h"


/*****************************************************************************
*****************************���´���ο�����*********************************
*****************************************************************************/
//THUMBָ�֧�ֻ������
//�������·���ʵ��ִ�л��ָ��WFI  
__asm void WFI_SET(void)
{
	WFI;		  
}
//�ر������ж�(���ǲ�����fault��NMI�ж�)
__asm void INTX_DISABLE(void)
{
	CPSID   I
	BX      LR	  
}
//���������ж�
__asm void INTX_ENABLE(void)
{
	CPSIE   I
	BX      LR  
}
//����ջ����ַ
//addr:ջ����ַ
__asm void MSR_MSP(u32 addr) 
{
	MSR MSP, r0 			//set Main Stack value
	BX r14
}

//����ϵͳ�δ�ʱ����д����ʱ����

//static u8  fac_us=0; //us��ʱ������			   
//static u16 fac_ms=0; //ms��ʱ������,��ucos��,����ÿ�����ĵ�ms��

/****************************************************************************
* ��    ��: delay_init()
* ��    �ܣ���ʱ������ʼ��
* ��ڲ�������
* ���ز�������
* ˵    ����
****************************************************************************/
//void delay_init()
//{
//	SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8);
//	fac_us=SYSCLK/8;	 
//	fac_ms=(u16)fac_us*1000; //ÿ��ms��Ҫ��systickʱ����   
//}								    

/****************************************************************************
* ��    ��: void delay_us(u32 nus)
* ��    �ܣ���ʱnus
* ��ڲ�����Ҫ��ʱ��΢����
* ���ز�������
* ˵    ����nus��ֵ,��Ҫ����798915us
****************************************************************************/
//void delay_us(u32 nus)
//{		
//	u32 temp;	    	 
//	SysTick->LOAD=nus*fac_us; 					//ʱ�����	  		 
//	SysTick->VAL=0x00;        					//��ռ�����
//	SysTick->CTRL|=SysTick_CTRL_ENABLE_Msk ;	//��ʼ����	  
//	do
//	{
//		temp=SysTick->CTRL;
//	}while((temp&0x01)&&!(temp&(1<<16)));		//�ȴ�ʱ�䵽��   
//	SysTick->CTRL&=~SysTick_CTRL_ENABLE_Msk;	//�رռ�����
//	SysTick->VAL =0X00;      					 //��ռ�����	 
//}
/****************************************************************************
* ��    ��: void delay_xms(u16 nms)
* ��    �ܣ���ʱnms
* ��ڲ�����Ҫ��ʱ�ĺ�����
* ���ز�������
* ˵    ����SysTick->LOADΪ24λ�Ĵ���,����,�����ʱΪ: nms<=0xffffff*8*1000/SYSCLK
            ��168M������,nms<=798ms 
****************************************************************************/
//void delay_xms(u16 nms)
//{	 		  	  
//	u32 midtime;		   
//	SysTick->LOAD=(u32)nms*fac_ms;//ʱ�����(SysTick->LOADΪ24bit)
//	SysTick->VAL =0x00;           //��ռ�����
//	SysTick->CTRL|=SysTick_CTRL_ENABLE_Msk ;          //��ʼ����  
//	do
//	{
//		midtime=SysTick->CTRL;
//	}
//	while((midtime&0x01)&&!(midtime&(1<<16)));//�ȴ�ʱ�䵽��   
//	SysTick->CTRL&=~SysTick_CTRL_ENABLE_Msk;       //�رռ�����
//	SysTick->VAL =0X00;       //��ռ�����	  	    
//} 
///****************************************************************************
//* ��    ��: void delay_ms(u16 nms)
//* ��    �ܣ���ʱnms
//* ��ڲ�����Ҫ��ʱ�ĺ�����
//* ���ز�������
//* ˵    ����nms:0~65535
//****************************************************************************/
//void delay_ms(u16 nms)
//{	 	 
//	u8 repeat=nms/540;	//������540,�ǿ��ǵ�ĳЩ�ͻ����ܳ�Ƶʹ��,
//								  //���糬Ƶ��248M��ʱ��,delay_xms���ֻ����ʱ541ms������
//	u16 remain=nms%540;
//	while(repeat)
//	{
//		delay_xms(540);
//		repeat--;
//	}
//	if(remain)delay_xms(remain);
//} 
//void delay_ms(u16 nms)
//{	 		  	  
//	u32 temp;		   
//	SysTick->LOAD=(u32)nms*fac_ms;				//ʱ�����(SysTick->LOADΪ24bit)
//	SysTick->VAL =0x00;							//��ռ�����
//	SysTick->CTRL|=SysTick_CTRL_ENABLE_Msk ;	//��ʼ����  
//	do
//	{
//		temp=SysTick->CTRL;
//	}while((temp&0x01)&&!(temp&(1<<16)));		//�ȴ�ʱ�䵽��   
//	SysTick->CTRL&=~SysTick_CTRL_ENABLE_Msk;	//�رռ�����
//	SysTick->VAL =0X00;       					//��ռ�����	  	    
//} 
//			 
void get_ms(unsigned long *timestamp)
{

}


