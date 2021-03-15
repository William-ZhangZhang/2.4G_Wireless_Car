#ifndef __KEY_H
#define __KEY_H	 
#include "sys.h"  	 


#define KEY_UP  	GPIO_ReadInputDataBit(GPIOF,GPIO_Pin_0)	//UP:前进
#define KEY_DOWN  	GPIO_ReadInputDataBit(GPIOF,GPIO_Pin_2)	//DOWN:后退
#define KEY_LEFT  	GPIO_ReadInputDataBit(GPIOF,GPIO_Pin_4)	//LEFT:左转
#define KEY_RIGHT  	GPIO_ReadInputDataBit(GPIOF,GPIO_Pin_6)	//RIGHT：右转
#define KEY_MID  	GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_10)//MID
#define KEY_SET  	GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_12)//SET
#define KEY_RST  	GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_14)//RST

#define KEY0_PRES 	1	//KEY0按下
#define KEY1_PRES	2	//KEY1按下
#define KEY2_PRES	3	//KEY2按下
#define KEY3_PRES   4	//KEY_UP按下(即WK_UP/KEY_UP)


void KEY_Init(void);//IO初始化
//u8 KEY_Scan(u8);  	//按键扫描函数


#endif
