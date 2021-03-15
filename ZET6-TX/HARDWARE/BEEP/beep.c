#include "beep.h"
#include "delay.h"

//初始化PE2为输出口.并使能这个口的时钟
//蜂鸣器初始化
void BEEP_Init(void)
{
    GPIO_InitTypeDef  GPIO_InitStructure;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE, ENABLE);   //使能GPIOE端口时钟

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;               //BEEP-->PE2 端口配置
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;        //推挽输出
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;   //速度为50MHz
    GPIO_Init(GPIOE, &GPIO_InitStructure);  //根据参数初始化GPIOE2

    GPIO_SetBits(GPIOE, GPIO_Pin_2); //输出1，关闭蜂鸣器输出
}


void BEEP_Power_ON(void)
{
    u16 i;
    for (i = 0; i < 400; i++)
    {
        BEEP = 0;
        delay_us(500);
        BEEP = 1;
        delay_us(500);
    }
}

void BEEP_Normal(void)
{
    u16 i;
    for (i = 0; i < 100; i++)
    {
        BEEP = 0;
        delay_us(400);
        BEEP = 1;
        delay_us(400);
    }
}
