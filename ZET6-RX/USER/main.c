#include "led.h"
#include "delay.h"
#include "key.h"
#include "sys.h"
#include "usart.h"
#include "24l01.h"
#include "pwm.h"
#include "timer.h"
#include "motor.h"
#include "capture.h"

u8 spd = 0;		//小车速度档位：0~9
u8 auto_flag;
u8 avoid_status;
u16 distance;


int main(void)
{
    u8 tmp_rxbuf[3];

    SystemInit();
    delay_init();           //延时函数初始化
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//设置中断优先级分组为组2：2位抢占优先级，2位响应优先级
    uart1_init(115200);     //串口1打印输出
    LED_Init();             //初始化与LED连接的硬件接口
    KEY_Init();             //初始化按键
    MOTOR_Init();           //初始化电机控制接口
    NRF24L01_Init();        //初始化NRF24L01
    TIM2_PWM_Init(9, 7199); //初始化定时器2，PWM输出
	TIM4_Int_Init(9, 7199);	//初始化通用定时器4，每1ms中断1次
    CAPTURE_Init();         //初始化获取超声波时长定时器3

    while (NRF24L01_Check())
    {
        printf("NRF未连接\r\n");
        LED0 = ~LED0;
        delay_ms(100);
    }

    LED0 = 1;
    printf("NRF已连接\r\n");
    NRF24L01_RX_Mode();

    while (1)
    {
//超声波实时测距
		distance = Hcsr04GetLength();//单位cm
		printf("dist = %dcm\r\n", distance);
//		delay_ms(100);

//接收处理
        if (NRF24L01_RxPacket(tmp_rxbuf) == 0)
        {
            printf("接收数据：");
            if (tmp_rxbuf[0] == '#')
            {
                switch (tmp_rxbuf[1])
                {
                case 'A'://UP
                    printf("前进\r\n");
                    Go(spd);
                    break;
                case 'B'://DOWN
                    printf("后退\r\n");
                    Back(spd);//后退
                    break;
                case 'C'://LEFT
                    printf("左转\r\n");
                    Turn_Left(spd);
                    break;
                case 'D'://RIGHT
                    printf("右转\r\n");
                    Turn_Right(spd);
                    break;
                case 'E'://MID
                    printf("停止\r\n");
                    Stop();
                    break;
                case 'F'://SET
					printf("自动\r\n");
					auto_flag = !auto_flag;
					if(auto_flag == 1)
					{
						LED0 = 0;
						delay_ms(100);
					}
					else
					{
						Stop();
						avoid_status = 0;
						LED0 = 1;
						delay_ms(100);
					}
                    break;
                case 'G'://RST
                    printf("启动\r\n");
					POWER = ~POWER;
					delay_ms(100);
					if(POWER)
						Start();
					else
					{
						Stop();
						auto_flag = 0;
					}
                    break;
                case 0:
                    printf("Speed=0\r\n");
                    spd = 0;
                    break;
                case 1:
                    printf("Speed=1\r\n");
                    spd = 1;
                    break;
                case 2:
                    printf("Speed=2\r\n");
                    spd = 2;
                    break;
                case 3:
                    printf("Speed=3\r\n");
                    spd = 3;
                    break;
                case 4:
                    printf("Speed=4\r\n");
                    spd = 4;
                    break;
                case 5:
                    printf("Speed=5\r\n");
                    spd = 5;
                    break;
                case 6:
                    printf("Speed=6\r\n");
                    spd = 6;
                    break;
                case 7:
                    printf("Speed=7\r\n");
                    spd = 7;
                    break;
                case 8:
                    printf("Speed=8\r\n");
                    spd = 8;
                    break;
                case 9:
                    printf("Speed=9\r\n");
                    spd = 9;
                    break;

                default :
                    printf("Fault Data:%d\r\n", tmp_rxbuf[1]);
                }

                LED1 = 0;
                delay_ms(200);
                LED1 = 1;

                tmp_rxbuf[0] = tmp_rxbuf[1] = tmp_rxbuf[2] = 0;
            }
            else
                printf("#数据错误！\r\n");
        }
    }
}



