#include "led.h"
#include "delay.h"
#include "key.h"
#include "sys.h"
#include "usart.h"
#include "adc.h"
#include "24l01.h"
#include "beep.h"

int main(void)
{
    u8 tmp_txbuf[3];
    u8 key = '0';
    u8 flag = 0;
	u16 adc_value = 0;
	u8 speed_value_0 = 0, speed_value_1 = 0;
	
    SystemInit();
    delay_init();           //延时函数初始化
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//设置中断优先级分组为组2：2位抢占优先级，2位响应优先级
    uart_init(115200);      //串口初始化1
    LED_Init();             //初始化与LED连接的硬件接口
    KEY_Init();             //初始化按键
	BEEP_Init();			//初始化蜂鸣器
	Adc_Init();				//初始化ADC
    NRF24L01_Init();        //初始化NRF24L01
	BEEP_Power_ON();
	
    while (NRF24L01_Check())
    {
        printf("NRF未连接\r\n");
        LED0 = ~LED0;
        delay_ms(100);
    }
	
    LED0 = 1;
    printf("NRF已连接\r\n");
    NRF24L01_TX_Mode();
	
    while (1)
    {
//获取ADC	
		adc_value = Get_Adc_Average(3, 10);
		speed_value_0 = adc_value/400;
		if(speed_value_1 != speed_value_0)
		{
			speed_value_1 = speed_value_0;
			key = speed_value_1;
			BEEP_Normal();
			printf("Speed = %d\r\n", key);
		}
		
//扫描按键
        if (KEY_UP == 0)		//前进
        {
            key = 'A';
            printf("A\r\n");
        }
        else if (KEY_DOWN == 0)	//后退
        {
            key = 'B';
            printf("B\r\n");
        }
        else if (KEY_LEFT == 0)	//左转
        {
            key = 'C';
            printf("C\r\n");
        }
        else if (KEY_RIGHT == 0)//右转
        {
            key = 'D';
            printf("D\r\n");
        }
        else if (KEY_MID == 0)	//中键
        {
            key = 'E';
            printf("E\r\n");
        }
        else if (KEY_SET == 0)	//SET键
        {
            key = 'F';
            printf("F\r\n");
        }
        else if (KEY_RST == 0) //RST键
        {
            key = 'G';
            printf("G\r\n");
        }

        if (key != '0')
        {
            tmp_txbuf[0] = '#';
            tmp_txbuf[1] = key;
            printf("%s", tmp_txbuf);
//发送
            flag = NRF24L01_TxPacket(tmp_txbuf);
            if (flag == TX_OK)
            {
                LED1 = 0;
                delay_ms(200);
                LED1 = 1;
                printf("已发送\r\n");
                key = '0';
            }
            else
            {
                printf("未发送\r\n");
                key = '0';
            }
        }
    }
}


