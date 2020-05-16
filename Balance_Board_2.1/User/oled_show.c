#include "board_drive.h"


unsigned char i;          //��������
unsigned char Send_Count; //������Ҫ���͵����ݸ���

/**
*@brief	
*@param  
*@retval 		
*/
void oled_show_init()
{
	//=============��һ����ʾ=======================//	
	OLED_ShowStr(0,0,(unsigned char*)"mode:",1);
	OLED_ShowStr(59,0,(unsigned char*)"power:    v",1);
	//=============�ڶ�����ʾ=======================//	
	OLED_ShowStr(0,1,(unsigned char*)"Obstacle:",1);
	//=============��������ʾ=======================//	
	OLED_ShowStr(0,2,(unsigned char*)"an_P:",1);
	OLED_ShowStr(63,2,(unsigned char*)"an_D:",1);
	
	//=============��������ʾ=======================//	
	OLED_ShowStr(0,3,(unsigned char*)"spd_P:",1);
	OLED_ShowStr(63,3,(unsigned char*)"spd_I:",1);
	//=============��������ʾ=======================//	

	//=============��������ʾ=======================//
	OLED_ShowStr(0,5,(unsigned char*)"enc_L:",1);
	OLED_ShowStr(63,5,(unsigned char*)"enc_R:",1);
	//=============��������ʾ=======================//
	OLED_ShowStr(0,6,(unsigned char*)"roll:",1);
	//=============�ڰ�����ʾ=======================//	
	OLED_ShowStr(0,7,(unsigned char*)"gyro:",1);
}
/**************************************************************************
�������ܣ�OLED��ʾ
��ڲ�������
����  ֵ����
**************************************************************************/
void oled_show_reflesh(void)
{
	char buf[8];
	//=============��һ����ʾ=======================//
					
	OLED_ShowStr(31,0,(unsigned char*)"dmp",1);
	
	sprintf(buf,"%4.1f",f32Power);						//=== ����4������С�����1λ
	OLED_ShowStr(95,0,(unsigned char*)buf,1);
	memset(buf,0,sizeof(buf));
	//=============�ڶ�����ʾ=======================//
	sprintf(buf,"%.1f   ",ultra.ultra_distance);
	OLED_ShowStr(55,1,(unsigned char*)buf,1);
	memset(buf,0,sizeof(buf));
	//=============��������ʾ=======================//		
	sprintf(buf,"%d ",(int)strBlCar.PD_P);
	OLED_ShowStr(31,2,(unsigned char*)buf,1);
	memset(buf,0,sizeof(buf));
	
	sprintf(buf,"%4.2f ",strBlCar.PD_D);
	OLED_ShowStr(94,2,(unsigned char*)buf,1);
	memset(buf,0,sizeof(buf));
	//=============��������ʾ=======================//			
	sprintf(buf,"%d ",(int)strBlCar.PI_P);
	OLED_ShowStr(37,3,(unsigned char*)buf,1);
	memset(buf,0,sizeof(buf));
	
	sprintf(buf,"%4.2f ",strBlCar.PI_I);
	OLED_ShowStr(100,3,(unsigned char*)buf,1);
	memset(buf,0,sizeof(buf));
	//=============��������ʾ=======================//	
	sprintf(buf,"%d ",encM1AB.Encoder);
	OLED_ShowStr(37,5,(unsigned char*)buf,1);
	memset(buf,0,sizeof(buf));
	
	sprintf(buf,"%d ",encM2AB.Encoder);
	OLED_ShowStr(99,5,(unsigned char*)buf,1);
	memset(buf,0,sizeof(buf));
	//=============��������ʾ=======================//	
	sprintf(buf,"%.3f   ",Roll);
	OLED_ShowStr(31,6,(unsigned char*)buf,1);
	memset(buf,0,sizeof(buf));
	//=============�ڰ�����ʾ=======================//	
	sprintf(buf,"%d   ",(int)gyro[0]);
	OLED_ShowStr(31,7,(unsigned char*)buf,1);
	memset(buf,0,sizeof(buf));
	//=============ˢ��=======================//

}
