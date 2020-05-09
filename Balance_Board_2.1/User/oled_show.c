#include "board_drive.h"


unsigned char i;          //计数变量
unsigned char Send_Count; //串口需要发送的数据个数
/**************************************************************************
函数功能：OLED显示
入口参数：无
返回  值：无
**************************************************************************/
void oled_show(void)
{
	OLED_CLS();
	//=============第一行显示小车模式=======================//	
	OLED_ShowStr(0,0,(unsigned char*)"dmp",1);
	OLED_ShowStr(0,1,(unsigned char*)"Putong",1);
	//=============第三行显示编码器1=======================//	
	/*
	OLED_ShowStr(0,2,(unsigned char*)"EncoLEFT",1);
	if( Encoder_Left<0)		
		OLED_ShowStr(53,2,(unsigned char*)"-",1),
		OLED_ShowNum(60,2,-Encoder_Left,1);
	else                 	
		OLED_ShowStr(53,2,(unsigned char*)"+",1),
		OLED_ShowNum(60,2, Encoder_Left,1);
	//=============第四行显示编码器2=======================//		
	OLED_ShowStr(0,3,(unsigned char*)"EncoLEFT",1);
	if( Encoder_Right<0)
		OLED_ShowStr(53,3,(unsigned char*)"-",1),
		OLED_ShowNum(60,3,-Encoder_Right,1);
	else                 	
		OLED_ShowStr(53,3,(unsigned char*)"+",1),
		OLED_ShowNum(60,3, Encoder_Right,1);
	//=============第五行显示电压=======================//
	//=============第六行显示角度=======================//
	OLED_ShowStr(0,5,(unsigned char*)"Angle",1);
	if(Angle_Balance<0)		
		OLED_ShowNum(42,5,Angle_Balance+360,1);
	else
		OLED_ShowNum(42,5,Angle_Balance,1);
	//=============第七行显示俯仰角=======================//
	OLED_ShowStr(0,6,(unsigned char*)"Pitch",1);
	if(Angle_Balance<0)	
		OLED_ShowNum(42,6,Pitch,1);
	else	
		OLED_ShowNum(42,6,Pitch,1);
	//=============刷新=======================//
	*/

}
