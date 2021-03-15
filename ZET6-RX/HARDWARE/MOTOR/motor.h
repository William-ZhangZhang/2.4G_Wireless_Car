#ifndef __MOTOR_H
#define __MOTOR_H	 
#include "sys.h"

#define POWER 		PEout(10)	//电机电源控制：1-闭合，0-断开
#define BK_LEFT  	PEout(12)	//左刹车：输出0-5v对于刹车力度0-100%
#define BK_RIGHT 	PFout(0)	//右刹车：输出0-5v对于刹车力度0-100%
#define FB_LEFT  	PEout(14)	//左轮换向
#define FB_RIGHT 	PFout(2)	//右轮换向


void MOTOR_Init(void);	//IO初始化
void Start(void);	//启动
void Stop(void);	//停止
void Go(u8 spd);	//前进
void Back(u8 spd);	//后退
void Turn_Left(u8 spd);	//左转
void Turn_Right(u8 spd);	//右转



#endif



