#ifndef VISION_H
#define VISION_H
#include "ti_msp_dl_config.h"
typedef struct
{
    uint8_t vision_on;
    int16_t x_offset;
    int16_t y_offset;
} vision_data_t;

void vision_init(void);
void vision_on(void);
void vision_off(void);
void UART_0_INST_IRQHandler(void);
void uart0_send_char(char ch);
void uart0_send_string(char* str);
void uart0_send_bytes(uint8_t* data, uint16_t length);
void uart0_receive_char(void);

// 新增的视觉模块接收处理函数
void vision_receive_handler(uint8_t received_byte);
void vision_get_received_data(void);
vision_data_t* vision_get_data(void);
#endif // !VISION_H