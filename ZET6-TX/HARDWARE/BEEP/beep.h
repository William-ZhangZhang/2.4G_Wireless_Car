#ifndef __BEEP_H
#define __BEEP_H	 
#include "sys.h"

//蜂鸣器端口定义
#define BEEP PEout(2)	// BEEP,蜂鸣器接口		   

void BEEP_Init(void);	//初始化
void BEEP_Power_ON(void);	//开机提示音
void BEEP_Normal(void);	//速度改变提示音
		 				    
#endif

