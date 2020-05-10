#include "board_drive.h"




void GPIO_Config()
{
	GPIO_InitTypeDef GPIO_InitStruct;
	RCC_APB2PeriphClockCmd(ADC_GPIO_CLK,ENABLE);
	
	GPIO_InitStruct.GPIO_Mode=GPIO_Mode_AIN;
	GPIO_InitStruct.GPIO_Pin=ADC_GPIO_PIN;
	GPIO_InitStruct.GPIO_Speed=GPIO_Speed_50MHz;
	
	GPIO_Init(ADC_GPIO_PORT,&GPIO_InitStruct);	
}


void ADC_Config()
{
	ADC_InitTypeDef ADC_InitStruct;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1,ENABLE);
	RCC_ADCCLKConfig(RCC_PCLK2_Div8);		//=== ADC始终输入不得超过14M   72/8=9M
	
	ADC_DeInit(ADCx); 													//=== 复位 ADCx,将外设 ADCx 的全部寄存器重设为缺省值
	ADC_InitStruct.ADC_ContinuousConvMode = DISABLE;					//=== 单次转换模式
	ADC_InitStruct.ADC_DataAlign = ADC_DataAlign_Right;					//=== 数据右对齐
	ADC_InitStruct.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;	//=== 不是外部触发启动，由软件启动
	ADC_InitStruct.ADC_Mode = ADC_Mode_Independent;						//=== ADC独立模式
	ADC_InitStruct.ADC_ScanConvMode = DISABLE;							//=== 单通道模式
	ADC_Init(ADCx,&ADC_InitStruct);
	
	ADC_Cmd(ADCx, ENABLE); 										
	ADC_ResetCalibration(ADCx); 										//=== 开启复位校准
	while(ADC_GetResetCalibrationStatus(ADCx));							//=== 等待复位校准结束
	ADC_StartCalibration(ADCx); 										//=== 开启 AD 校准
	while(ADC_GetCalibrationStatus(ADCx)); 								//=== 等待校准结束	
}


void Battery_Init()
{
	GPIO_Config();
	ADC_Config();
}


/**
*@brief	
*@param  
*@retval 		
*/
uint16_t Get_Adc(uint8_t ch)
{
	ADC_RegularChannelConfig(ADC1, ch, 1, ADC_SampleTime_239Cycles5 );
	ADC_SoftwareStartConvCmd(ADC1,ENABLE);			//=== 使能指定的ADC的软件转换功能		
	while(ADC_GetSoftwareStartConvStatus(ADC1));	//=== 等待软件转换完成
	return ADC_GetDualModeConversionValue();		//=== 返回最近一次的转换结果。
}
/**
*@brief	
*@param  
*@retval 		
*/
uint16_t Get_Adc_Average(uint8_t ch,uint8_t times)
{
	u32 temp_val=0;
	u8 t;
	for(t=0;t<times;t++)
	{
		temp_val+=Get_Adc(ch);
		delay_ms(5);
	}
	return temp_val/times;
}
/**
*@brief	
*@param  
*@retval 		
*/
float Get_Bettrty(uint8_t times)
{
	float b = 0.00626289;					//=== 电压与adc比例关系
	b *= Get_Adc_Average(ADC_CH,times);
	b = (int)(b*100);						//=== 取值到小数点后两位
	b *= 0.01;
	return b;
}

