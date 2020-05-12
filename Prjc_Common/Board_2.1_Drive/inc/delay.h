#ifndef _DELAY__H_
#define _DELAY__H_

#include "board_drive.h"

void delay_us(u16 n);
void delay_ms(u32 n);

void get_ms(unsigned long *time);
#endif
