#include "capture.h"
#include "delay.h"


//超声波计数
u16 msHcCount = 0;

//初始化
void CAPTURE_Init(void)
{
    GPIO_InitTypeDef GPIO_IniStructure;
    TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
    NVIC_InitTypeDef NVIC_InitStructure;

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);

    GPIO_IniStructure.GPIO_Pin = GPIO_Pin_0;//PB0(ECHO)回响信号输入脚
    GPIO_IniStructure.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_Init(GPIOB, &GPIO_IniStructure);
    GPIO_ResetBits(GPIOB, GPIO_Pin_0);

    GPIO_IniStructure.GPIO_Pin = GPIO_Pin_1;//PB1(Trig)输入触发信号脚，持续给10us以上高电平
    GPIO_IniStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_IniStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_IniStructure);
    GPIO_ResetBits(GPIOB, GPIO_Pin_1);


    TIM_TimeBaseInitStructure.TIM_Period = 999;//自动重装载值
    TIM_TimeBaseInitStructure.TIM_Prescaler = 71;//预分频值
    TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;//向上计数
    TIM_TimeBaseInit(TIM3, &TIM_TimeBaseInitStructure);

    NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
    NVIC_Init(&NVIC_InitStructure);//开中断，设置中断触发类型

    TIM_ClearFlag(TIM3, TIM_FLAG_Update);
    TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE);
    TIM_Cmd(TIM3, DISABLE);
}

//打开定时器3
static void OpenTimerForHc()
{
    TIM_SetCounter(TIM3, 0);
    msHcCount = 0;
    TIM_Cmd(TIM3, ENABLE);
}

//关闭定时器3
static void CloseTimerForHc()
{
    TIM_Cmd(TIM3, DISABLE);
}

//定时器3中断服务程序
void TIM3_IRQHandler(void)
{
    if (TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET)
    {
        TIM_ClearITPendingBit(TIM3, TIM_IT_Update);
        msHcCount++;
    }
}

//获取定时器3计数器值
u32 GetEchoTimer(void)
{
    u32 t = 0;

    t = msHcCount * 1000;
    t += TIM_GetCounter(TIM3);
    TIM3->CNT = 0;
    delay_ms(50);

    return t;
}

//通过定时器3计数器值推算距离
float Hcsr04GetLength(void)
{
    u32 t = 0;
    int i = 0;
    float lengthTemp = 0;
    float sum = 0;

    while (i != 5)
    {
        TRIG_OUT = 1;
        delay_us(20);
        TRIG_OUT = 0;
		
        while (ECHO_IN == 0);
        OpenTimerForHc();
        i = i + 1;
        while (ECHO_IN == 1);
        CloseTimerForHc();
        t = GetEchoTimer();
        lengthTemp = ((float)t / 58.0); //cm
        sum = lengthTemp + sum ;
    }
    lengthTemp = sum / 5.0;

    return lengthTemp;
}



