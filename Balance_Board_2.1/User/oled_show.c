#include "board_drive.h"


unsigned char i;          //��������
unsigned char Send_Count; //������Ҫ���͵����ݸ���
/**************************************************************************
�������ܣ�OLED��ʾ
��ڲ�������
����  ֵ����
**************************************************************************/
void oled_show(void)
{
	OLED_CLS();
	//=============��һ����ʾС��ģʽ=======================//	
	OLED_ShowStr(0,0,(unsigned char*)"dmp",1);
	OLED_ShowStr(0,1,(unsigned char*)"Putong",1);
	//=============��������ʾ������1=======================//	
	/*
	OLED_ShowStr(0,2,(unsigned char*)"EncoLEFT",1);
	if( Encoder_Left<0)		
		OLED_ShowStr(53,2,(unsigned char*)"-",1),
		OLED_ShowNum(60,2,-Encoder_Left,1);
	else                 	
		OLED_ShowStr(53,2,(unsigned char*)"+",1),
		OLED_ShowNum(60,2, Encoder_Left,1);
	//=============��������ʾ������2=======================//		
	OLED_ShowStr(0,3,(unsigned char*)"EncoLEFT",1);
	if( Encoder_Right<0)
		OLED_ShowStr(53,3,(unsigned char*)"-",1),
		OLED_ShowNum(60,3,-Encoder_Right,1);
	else                 	
		OLED_ShowStr(53,3,(unsigned char*)"+",1),
		OLED_ShowNum(60,3, Encoder_Right,1);
	//=============��������ʾ��ѹ=======================//
	//=============��������ʾ�Ƕ�=======================//
	OLED_ShowStr(0,5,(unsigned char*)"Angle",1);
	if(Angle_Balance<0)		
		OLED_ShowNum(42,5,Angle_Balance+360,1);
	else
		OLED_ShowNum(42,5,Angle_Balance,1);
	//=============��������ʾ������=======================//
	OLED_ShowStr(0,6,(unsigned char*)"Pitch",1);
	if(Angle_Balance<0)	
		OLED_ShowNum(42,6,Pitch,1);
	else	
		OLED_ShowNum(42,6,Pitch,1);
	//=============ˢ��=======================//
	*/

}
