#ifndef __TIMER_H
#define __TIMER_H
#include "sys.h"

extern u8 spd;
extern u8 auto_flag;
extern u8 avoid_status;
extern u16 distance;
	
void TIM4_Int_Init(u16 arr,u16 psc);
 
#endif
