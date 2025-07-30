#include "vision.h"
volatile unsigned char uart0_data = 0;
void vision_init(void)
{
    NVIC_ClearPendingIRQ(UART_0_INST_INT_IRQN);
    //使能串口中断
    NVIC_EnableIRQ(UART_0_INST_INT_IRQN);
    // 初始化视觉模块
}
void UART_0_INST_IRQHandler(void)
{
    //如果产生了串口中断
    switch( DL_UART_getPendingInterrupt(UART_0_INST) )
    {
        case DL_UART_IIDX_RX://如果是接收中断
            //接发送过来的数据保存在变量中
            uart0_data = DL_UART_Main_receiveData(UART_0_INST);
            //将保存的数据再发送出去
            uart0_send_char(uart0_data);
            break;

        default://其他的串口中断
            break;
    }
}
void uart0_send_char(char ch)
{
    //当串口0忙的时候等待，不忙的时候再发送传进来的字符
    while( DL_UART_isBusy(UART_0_INST) == true );
    //发送单个字符
    DL_UART_Main_transmitData(UART_0_INST, ch);
}
void uart0_send_string(char* str)
{
    //当前字符串地址不在结尾 并且 字符串首地址不为空
    while(*str!=0&&str!=0)
    {
        //发送字符串首地址中的字符，并且在发送完成之后首地址自增
        uart0_send_char(*str++);
    }
}
void uart0_send_bytes(uint8_t* data, uint16_t length)
{
    for(uint16_t i = 0; i < length; i++)
    {
        // 等待发送缓冲区空闲
        while(DL_UART_isBusy(UART_0_INST));
        // 发送单个字节
        DL_UART_Main_transmitData(UART_0_INST, data[i]);
    }
}
void uart0_receive_char(void)
{
    // 等待接收缓冲区非空
    while(DL_UART_isBusy(UART_0_INST));
    // 接收单个字符
    uart0_data = DL_UART_Main_receiveData(UART_0_INST);
}
void uart0_receive_string(char* buffer, uint16_t max_length)
{
    uint16_t i = 0;
    while(i < max_length - 1) // 保留一个位置给字符串结束符
    {
        // 等待接收缓冲区非空
        while(DL_UART_isBusy(UART_0_INST));
        // 接收单个字符
        buffer[i] = DL_UART_Main_receiveData(UART_0_INST);
        if(buffer[i] == '\0') break; // 如果遇到字符串结束符则停止
        i++;
    }
    buffer[i] = '\0'; // 确保字符串以'\0'结尾
}