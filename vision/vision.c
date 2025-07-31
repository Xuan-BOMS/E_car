#include "vision.h"
#include <string.h>
volatile unsigned char uart0_data = 0;
vision_data_t vision_data;
// 接收缓冲区相关变量
static uint8_t rx_buffer[6];
static volatile uint8_t rx_state = 0;  // 0: 等待0xAA, 1: 接收数据, 2: 数据接收完成
static volatile uint8_t rx_index = 0;
void vision_init(void)
{
    NVIC_ClearPendingIRQ(UART_0_INST_INT_IRQN);
    //使能串口中断
    NVIC_EnableIRQ(UART_0_INST_INT_IRQN);
    // 初始化视觉模块
    vision_data.vision_on = 0;
    vision_data.x_offset = 0;
    vision_data.y_offset = 0;
}
void vision_on(void)
{
    uint8_t command[] = {0xAA, 0xAA, 0xBB}; // 示例命令
    uart0_send_bytes(command, sizeof(command));
    vision_data.vision_on = 1; // 设置视觉模块开启状态
}
void vision_off(void)
{
    uint8_t command[] = {0xAA, 0xFF, 0xBB}; // 示例命令
    uart0_send_bytes(command, sizeof(command));
    vision_data.vision_on = 0; // 设置视觉模块关闭状态
}
void UART_0_INST_IRQHandler(void)
{
    //如果产生了串口中断
    switch( DL_UART_getPendingInterrupt(UART_0_INST) )
    {
        case DL_UART_IIDX_RX://如果是接收中断
            //接发送过来的数据保存在变量中
            uart0_data = DL_UART_Main_receiveData(UART_0_INST);
            // 处理接收状态机
            vision_receive_handler(uart0_data);
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

// 视觉模块接收处理函数
void vision_receive_handler(uint8_t received_byte)
{
    switch(rx_state)
    {
        case 0: // 等待起始字节0xAA
            if(received_byte == 0xAA)
            {
                rx_buffer[0] = received_byte;
                rx_index = 1;
                rx_state = 1;
            }
            break;
            
        case 1: // 接收数据
            rx_buffer[rx_index] = received_byte;
            rx_index++;
            
            // 检查是否接收到结束字节0xBB
            if(received_byte == 0xBB && rx_index == 6) // 至少要有AA + 数据 + BB
            {
                rx_state = 0;
                rx_index = 0;
                vision_get_received_data();
            }
            // 防止缓冲区溢出
            else if(rx_index >= sizeof(rx_buffer))
            {
                rx_state = 0; // 重置状态
                rx_index = 0;
                memset(rx_buffer, 0, sizeof(rx_buffer));
            }
            break;
        default:
            rx_state = 0;
            rx_index = 0;
            break;
    }
}

void vision_get_received_data(void)
{
    if(rx_buffer[0] == 0xAA && rx_buffer[5] == 0xBB)
    {
        __disable_irq();
        vision_data.x_offset = (int16_t)((rx_buffer[1] << 8) | rx_buffer[2]);
        vision_data.y_offset = (int16_t)((rx_buffer[3] << 8) | rx_buffer[4]);
        __enable_irq();
        memset(rx_buffer, 0, sizeof(rx_buffer));
    }
    else
    {
        // 数据格式错误，重置状态
        rx_state = 0;
        rx_index = 0;
    }
}
vision_data_t* vision_get_data(void)
{
    return &vision_data;
}