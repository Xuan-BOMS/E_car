#include "ti_msp_dl_config.h"
#include "gimbal.h"
#include "time.h"
#include "vision.h"
#include "motor.h"
#include "hwt101.h"
volatile unsigned char uart1_data = 0;
uint8_t send_text_data[] = "Hello, this is a test message.\r\n";
int main(void)
{
    SYSCFG_DL_init();
    //清除串口中断标志
    NVIC_ClearPendingIRQ(UART_1_INST_INT_IRQN);
    //使能串口中断
    NVIC_EnableIRQ(UART_1_INST_INT_IRQN);
    DL_UART_enableInterrupt(UART_1_INST, DL_UART_IIDX_RX | DL_UART_IIDX_TX);
    //使能定时器中断
    NVIC_ClearPendingIRQ(TIMER_gimbal_INST_INT_IRQN);
    NVIC_EnableIRQ(TIMER_gimbal_INST_INT_IRQN);
    vision_init(); // 初始化视觉模块
    gimbal_init(); // 初始化云台
    motor_init(); // 初始化电机
    HWT101_Init(); // 初始化HWT101传感器
    while (1)
    {
        delay_ms(10);
        motor_setSpeed();
        //发送字符串
        //uart1_send_string((char*)send_text_data);
        //gimbal_motor_move(); // 控制云台电机移动
    }
}


//串口的中断服务函数
void UART_1_INST_IRQHandler(void)
{
    //如果产生了串口中断
    switch( DL_UART_getPendingInterrupt(UART_1_INST) )
    {
        case DL_UART_IIDX_RX://如果是接收中断
            //接发送过来的数据保存在变量中
            uart1_data = DL_UART_Main_receiveData(UART_1_INST);
            //将保存的数据再发送出去
            break;
        case DL_UART_IIDX_TX://如果是发送中断
            break;
        default://其他的串口中断
            break;
    }
}
