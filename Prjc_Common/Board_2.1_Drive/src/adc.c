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
	RCC_ADCCLKConfig(RCC_PCLK2_Div8);		//=== ADCʼ�����벻�ó���14M   72/8=9M
	
	ADC_DeInit(ADCx); 													//=== ��λ ADCx,������ ADCx ��ȫ���Ĵ�������Ϊȱʡֵ
	ADC_InitStruct.ADC_ContinuousConvMode = DISABLE;					//=== ����ת��ģʽ
	ADC_InitStruct.ADC_DataAlign = ADC_DataAlign_Right;					//=== �����Ҷ���
	ADC_InitStruct.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;	//=== �����ⲿ�������������������
	ADC_InitStruct.ADC_Mode = ADC_Mode_Independent;						//=== ADC����ģʽ
	ADC_InitStruct.ADC_ScanConvMode = DISABLE;							//=== ��ͨ��ģʽ
	ADC_Init(ADCx,&ADC_InitStruct);
	
	ADC_Cmd(ADCx, ENABLE); 										
	ADC_ResetCalibration(ADCx); 										//=== ������λУ׼
	while(ADC_GetResetCalibrationStatus(ADCx));							//=== �ȴ���λУ׼����
	ADC_StartCalibration(ADCx); 										//=== ���� AD У׼
	while(ADC_GetCalibrationStatus(ADCx)); 								//=== �ȴ�У׼����	
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
	ADC_SoftwareStartConvCmd(ADC1,ENABLE);			//=== ʹ��ָ����ADC�����ת������		
	while(ADC_GetSoftwareStartConvStatus(ADC1));	//=== �ȴ����ת�����
	return ADC_GetDualModeConversionValue();		//=== �������һ�ε�ת�������
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
	float b = 0.00626289;					//=== ��ѹ��adc������ϵ
	b *= Get_Adc_Average(ADC_CH,times);
	b = (int)(b*100);						//=== ȡֵ��С�������λ
	b *= 0.01;
	return b;
}

