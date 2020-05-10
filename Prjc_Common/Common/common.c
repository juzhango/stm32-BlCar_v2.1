#include "common.h"


/*****************************************************************************
*****************************以下代码参考网上*********************************
*****************************************************************************/
//THUMB指令不支持汇编内联
//采用如下方法实现执行汇编指令WFI  
__asm void WFI_SET(void)
{
	WFI;		  
}
//关闭所有中断(但是不包括fault和NMI中断)
__asm void INTX_DISABLE(void)
{
	CPSID   I
	BX      LR	  
}
//开启所有中断
__asm void INTX_ENABLE(void)
{
	CPSIE   I
	BX      LR  
}
//设置栈顶地址
//addr:栈顶地址
__asm void MSR_MSP(u32 addr) 
{
	MSR MSP, r0 			//set Main Stack value
	BX r14
}

//利用系统滴答定时，编写的延时函数

//static u8  fac_us=0; //us延时倍乘数			   
//static u16 fac_ms=0; //ms延时倍乘数,在ucos下,代表每个节拍的ms数

/****************************************************************************
* 名    称: delay_init()
* 功    能：延时函数初始化
* 入口参数：无
* 返回参数：无
* 说    明：
****************************************************************************/
//void delay_init()
//{
//	SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8);
//	fac_us=SYSCLK/8;	 
//	fac_ms=(u16)fac_us*1000; //每个ms需要的systick时钟数   
//}								    

/****************************************************************************
* 名    称: void delay_us(u32 nus)
* 功    能：延时nus
* 入口参数：要延时的微妙数
* 返回参数：无
* 说    明：nus的值,不要大于798915us
****************************************************************************/
//void delay_us(u32 nus)
//{		
//	u32 temp;	    	 
//	SysTick->LOAD=nus*fac_us; 					//时间加载	  		 
//	SysTick->VAL=0x00;        					//清空计数器
//	SysTick->CTRL|=SysTick_CTRL_ENABLE_Msk ;	//开始倒数	  
//	do
//	{
//		temp=SysTick->CTRL;
//	}while((temp&0x01)&&!(temp&(1<<16)));		//等待时间到达   
//	SysTick->CTRL&=~SysTick_CTRL_ENABLE_Msk;	//关闭计数器
//	SysTick->VAL =0X00;      					 //清空计数器	 
//}
/****************************************************************************
* 名    称: void delay_xms(u16 nms)
* 功    能：延时nms
* 入口参数：要延时的毫妙数
* 返回参数：无
* 说    明：SysTick->LOAD为24位寄存器,所以,最大延时为: nms<=0xffffff*8*1000/SYSCLK
            对168M条件下,nms<=798ms 
****************************************************************************/
//void delay_xms(u16 nms)
//{	 		  	  
//	u32 midtime;		   
//	SysTick->LOAD=(u32)nms*fac_ms;//时间加载(SysTick->LOAD为24bit)
//	SysTick->VAL =0x00;           //清空计数器
//	SysTick->CTRL|=SysTick_CTRL_ENABLE_Msk ;          //开始倒数  
//	do
//	{
//		midtime=SysTick->CTRL;
//	}
//	while((midtime&0x01)&&!(midtime&(1<<16)));//等待时间到达   
//	SysTick->CTRL&=~SysTick_CTRL_ENABLE_Msk;       //关闭计数器
//	SysTick->VAL =0X00;       //清空计数器	  	    
//} 
///****************************************************************************
//* 名    称: void delay_ms(u16 nms)
//* 功    能：延时nms
//* 入口参数：要延时的毫妙数
//* 返回参数：无
//* 说    明：nms:0~65535
//****************************************************************************/
//void delay_ms(u16 nms)
//{	 	 
//	u8 repeat=nms/540;	//这里用540,是考虑到某些客户可能超频使用,
//								  //比如超频到248M的时候,delay_xms最大只能延时541ms左右了
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
//	SysTick->LOAD=(u32)nms*fac_ms;				//时间加载(SysTick->LOAD为24bit)
//	SysTick->VAL =0x00;							//清空计数器
//	SysTick->CTRL|=SysTick_CTRL_ENABLE_Msk ;	//开始倒数  
//	do
//	{
//		temp=SysTick->CTRL;
//	}while((temp&0x01)&&!(temp&(1<<16)));		//等待时间到达   
//	SysTick->CTRL&=~SysTick_CTRL_ENABLE_Msk;	//关闭计数器
//	SysTick->VAL =0X00;       					//清空计数器	  	    
//} 
//			 
void get_ms(unsigned long *timestamp)
{

}


