#ifndef _CONTROL_H
#define _CONTROL_H
#include "board_drive.h"

typedef struct
{
	uint8_t Time_1HZ;
	uint8_t Time_5HZ;
}STR_TIME_REG;


extern float f32Power;

extern void BlCar_Control(void);


void BlCar_Control(void);







#endif





