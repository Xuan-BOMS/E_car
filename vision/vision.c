#include "vision.h"

void vision_init(void)
{
    NVIC_ClearPendingIRQ(UART_0_INST_INT_IRQN);
    //使能串口中断
    NVIC_EnableIRQ(UART_0_INST_INT_IRQN);
    // 初始化视觉模块
}
