#include "vision.h"

void vision_init(void)
{
    NVIC_ClearPendingIRQ(UART_0_INST_INT_IRQN);
    //使能串口中断
    NVIC_EnableIRQ(UART_0_INST_INT_IRQN);
    DL_UART_enableInterrupt(UART_0_INST, DL_UART_IIDX_RX | DL_UART_IIDX_TX);
    // 初始化视觉模块
}
