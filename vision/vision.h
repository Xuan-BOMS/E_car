#ifndef VISION_H
#define VISION_H
#include "../ti_msp_dl_config.h"
void vision_init(void);
void UART_0_INST_IRQHandler(void);
void uart0_send_char(char ch);
void uart0_send_string(char* str);
void uart0_send_bytes(uint8_t* data, uint16_t length);
void uart0_receive_char(void);
void uart0_receive_string(char* buffer, uint16_t max_length);
#endif // !VISION_H