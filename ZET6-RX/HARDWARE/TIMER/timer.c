#include "timer.h"
#include "motor.h"

#define SafeDistance  50	//最小安全距离，默认50cm
u16 dist_l, dist_f, dist_r;

//通用定时器4中断初始化
//这里时钟选择为APB1的2倍，而APB1为36M
//arr：自动重装值。
//psc：时钟预分频数
//这里使用的是定时器4!
void TIM4_Int_Init(u16 arr, u16 psc)
{
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
    NVIC_InitTypeDef NVIC_InitStructure;

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE); //时钟使能

    //定时器TIM4初始化
    TIM_TimeBaseStructure.TIM_Period = arr; //设置在下一个更新事件装入活动的自动重装载寄存器周期的值
    TIM_TimeBaseStructure.TIM_Prescaler = psc; //设置用来作为TIMx时钟频率除数的预分频值
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //设置时钟分割:TDTS = Tck_tim
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向上计数模式
    TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure); //根据指定的参数初始化TIMx的时间基数单位

    TIM_ITConfig(TIM4, TIM_IT_Update, ENABLE); //使能指定的TIM4中断,允许更新中断

    //中断优先级NVIC设置
    NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn;  //TIM4中断
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  //先占优先级0级
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 4;  //从优先级4级
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQ通道被使能
    NVIC_Init(&NVIC_InitStructure);  //初始化NVIC寄存器

    TIM_Cmd(TIM4, ENABLE);  //使能TIMx
}



u16 ms_timer;
u16 get_dist_timer, TL_timer, TR_timer, BK_timer;

//定时器4中断服务程序
void TIM4_IRQHandler(void)   //TIM4中断
{	
    if (TIM_GetITStatus(TIM4, TIM_IT_Update) != RESET)  //检查TIM4更新中断发生与否
    {
		if(auto_flag == 1)
		{
			if(ms_timer++ >= 100)
			{
				ms_timer = 0;
				switch(avoid_status)
				{
					case 0:
						dist_f = distance;
						if(dist_f >= SafeDistance)
							Go(spd);
						else
						{
							Stop();
							avoid_status = 1;
						}
						break;
					case 1:
						Turn_Left(1);
						if(TL_timer++ >= 3)
						{
							TL_timer = 0;
							Stop();
							dist_l = distance;
							if(dist_l > SafeDistance)
								avoid_status = 0;
							else
								avoid_status = 2;
						}
						break;
					case 2:
						Turn_Right(1);
						if(TR_timer++ >= 5)
						{
							TR_timer = 0;
							Stop();
							dist_r = distance;
							if(dist_r > SafeDistance)
								avoid_status = 0;
							else
								avoid_status = 3;
						}
						break;
					case 3:
						if(dist_r < SafeDistance && dist_l < SafeDistance)
						{
							Back(spd);
							if(BK_timer++ >= 3)
							{
								Stop();
								avoid_status = 0;
							}
						}
						break;
				}
			}
		}
		
        TIM_ClearITPendingBit(TIM4, TIM_IT_Update);    //清除TIMx更新中断标志
    }
}












