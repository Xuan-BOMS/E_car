#include "hwt101.h"
unsigned char uart2_data = 0;
HWT101_Data_t hwt101_data;
void HWT101_Init(void)
{
    NVIC_ClearPendingIRQ(UART_2_INST_INT_IRQN);
    //使能串口中断
    NVIC_EnableIRQ(UART_2_INST_INT_IRQN);
    // 初始化视觉模块
    hwt101_data.type_mode = 0;
    hwt101_data.YAW = 0;
}
void UART_2_INST_IRQHandler(void)
{
    //如果产生了串口中断
    switch( DL_UART_getPendingInterrupt(UART_2_INST) )
    {
        case DL_UART_IIDX_RX://如果是接收中断
            //接发送过来的数据保存在变量中
            //uart2_data = DL_UART_Main_receiveData(UART_2_INST);
            // 处理接收状态机
            //HWT101_Angle_Get(uart2_data);
            break;

        default://其他的串口中断
            break;
    }
}
void HWT101_Angle_Get(uint8_t data)
{
    static uint8_t rx_buffer[11];  // 接收缓冲区
    static uint8_t rx_index = 0;  // 接收索引
    static uint8_t rx_state = 0;  // 接收状态
    
    switch(rx_state)
    {
        case 0: // 等待帧头1: 0x55
            if(data == 0x55)
            {
                rx_buffer[0] = data;
                rx_index = 1;
                rx_state = 1;
            }
            break;
            
        case 1: // 等待帧头2: 0x53
            if(data == 0x53)
            {
                rx_buffer[1] = data;
                rx_index = 2;
                rx_state = 2;
            }
            else
            {
                rx_state = 0; // 重新开始
                rx_index = 0;
            }
            break;
            
        case 2: // 接收数据部分
            rx_buffer[rx_index] = data;
            rx_index++;
            
            if(rx_index >= 11) // 接收完整包
            {
                // 校验和计算
                uint8_t checksum = 0x55 + 0x53 + rx_buffer[6] + rx_buffer[7] + rx_buffer[8] + rx_buffer[9];
                
                if(checksum == rx_buffer[10]) // 校验成功
                {
                    // 提取YAW数据
                    uint16_t yaw_raw = ((uint16_t)rx_buffer[7] << 8) | rx_buffer[6];
                    
                    // 计算YAW角度: YAW = yaw_raw / 32768 * 180°
                    hwt101_data.YAW = (float)yaw_raw / 32768.0f * 180.0f;
                    
                    // 设置数据有效标志
                    hwt101_data.type_mode = 1; // 标记数据有效
                }
                
                // 重置状态机
                rx_state = 0;
                rx_index = 0;
            }
            break;
            
        default:
            rx_state = 0;
            rx_index = 0;
            break;
    }
}
// 获取HWT101数据指针
HWT101_Data_t* HWT101_Get_Data_Pointer(void)
{
    return &hwt101_data;
}
