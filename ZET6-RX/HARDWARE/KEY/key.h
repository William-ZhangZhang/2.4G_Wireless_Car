#ifndef __KEY_H
#define __KEY_H	 
#include "sys.h"
//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//ALIENTEK战舰STM32开发板
//按键驱动代码	   
//正点原子@ALIENTEK
//技术论坛:www.openedv.com
//修改日期:2012/9/3
//版本：V1.0
//版权所有，盗版必究。
//Copyright(C) 广州市星翼电子科技有限公司 2009-2019
//All rights reserved									  
//////////////////////////////////////////////////////////////////////////////////   	 



#define KEY_FW  GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_4)//前
#define KEY_TL  GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_5)//左
#define KEY_TR  GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_6)//右
#define KEY_BW  GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_7)//后
#define KEY_WH  GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_11)//笛
#define KEY_ST  GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_1)//启
#define KEY_SP  GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_0)//停

#define KEY0_PRES 	1	//KEY0按下
#define KEY1_PRES	2	//KEY1按下
#define KEY2_PRES	3	//KEY2按下
#define KEY3_PRES   4	//KEY_UP按下(即WK_UP/KEY_UP)


void KEY_Init(void);//IO初始化
//u8 KEY_Scan(u8);  	//按键扫描函数					    
#endif
