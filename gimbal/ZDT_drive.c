#include "ZDT_drive.h"
static uint8_t enable[]={0x01,0xF3,0xAB,0x01,0x00,0x6B};
static uint8_t speed[]={0x01,0xF6,0x01,0x00,0x00,0xFF,0x00,0x6B};
static uint8_t angle_relative[]={0x01,0xFD,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x6B};
static uint8_t angle_absolute[]={0x01,0xFD,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x00,0x6B};
static uint8_t receive[4]={0x01,0x00,0x00,0x6B};
static uint8_t receive_enable[]={0x01,0xF3,0x02,0x6B},receive_speed[]={0x01,0xF6,0x02,0x6B},receive_angle_relative[]={0x01,0xFD,0x02,0x6B},receive_angle_absolute[]={0x01,0xFD,0x02,0x6B};
void ZDT_init(int16_t mode_set,int16_t address,ZDT_motor* motor)
{   
    motor->mode=mode_set;
    enable[0]=address;receive_enable[0]=address;receive_speed[0]=address;receive_angle_relative[0]=address;receive_angle_absolute[0]=address;
    switch (motor->mode)
    {
    case usart1_mode:
        uart1_send_bytes(enable, sizeof(enable));
        break;
    case usart2_mode:
        break;
    case can1_mode:
        break;
    case can2_mode:
        break;
    default:
        break;
    }
}
void ZDT_speed(int16_t speed_set,int16_t address,ZDT_motor* motor)
{   
    motor->move_mode=speed_mode;
    speed[0]=address;
    switch (motor->mode)
    {
    case usart1_mode:
    motor->direction=(speed_set>0)?0x01:0x00;
    motor->speed=(speed_set>0)?speed_set:-speed_set;
    speed[2]=motor->direction;speed[3]=motor->speed>>8;speed[4]=motor->speed & 0xFF;//speed[4]=motor->speed-speed[3]*16;
    uart1_send_bytes(speed, sizeof(speed));
        break;
    case usart2_mode:
    motor->direction=(speed_set>0)?0x01:0x00;
    motor->speed=(speed_set>0)?speed_set:-speed_set;
    speed[2]=motor->direction;speed[3]=motor->speed>>8;speed[4]=motor->speed & 0xFF;//speed[4]=motor->speed-speed[3]*16;
    break;
    case can1_mode:
        break;
    case can2_mode:
        break;
    default:
        break;
    }
}
void ZDT_angle_absolute(int16_t angle_set,int16_t speed_set,int16_t address,ZDT_motor* motor)
{   
    motor->move_mode=angle_absolute_mode;
    angle_absolute[10]=1;
    angle_absolute[0]=address;
    switch (motor->mode)
    {
    case usart1_mode:
    motor->direction=(angle_set>0)?0x01:0x00;
    motor->angle=(angle_set>0)?(int)(angle_set*angle_per_turn/360):-(int)(angle_set*angle_per_turn/360);
    angle_absolute[2]=motor->direction;angle_absolute[3] = (uint8_t)(speed_set >> 8);angle_absolute[4] = (uint8_t)(speed_set & 0xFF);
    angle_absolute[6] = (uint8_t)(motor->angle >> 24);angle_absolute[7] = (uint8_t)(motor->angle >> 16);angle_absolute[8] = (uint8_t)(motor->angle >> 8);angle_absolute[9] = (uint8_t)motor->angle;
    uart1_send_bytes(angle_absolute, sizeof(angle_absolute));
        break;
    case usart2_mode:
    motor->direction=(angle_set>0)?0x01:0x00;
    motor->angle=(angle_set>0)?(int)(angle_set*angle_per_turn/360):-(int)(angle_set*angle_per_turn/360);
    angle_absolute[2]=motor->direction;angle_absolute[3]=speed_set>>8;angle_absolute[4]=speed_set-angle_absolute[3]*16;
    angle_absolute[6] = (uint8_t)(motor->angle >> 24);angle_absolute[7] = (uint8_t)(motor->angle >> 16);angle_absolute[8] = (uint8_t)(motor->angle >> 8);angle_absolute[9] = (uint8_t)motor->angle;
    break;
    case can1_mode:
        break;
    case can2_mode:
        break;
    default:
        break;
    }
}
void ZDT_angle_relative(int16_t angle_set,int16_t speed_set,int16_t address,ZDT_motor* motor)
{   
    motor->move_mode=angle_relative_mode;
    angle_relative[10]=0;
    angle_relative[0]=address;
    switch (motor->mode)
    {
    case usart1_mode:
    motor->direction=(angle_set>0)?0x01:0x00;
    motor->angle=(angle_set>0)?(int)(angle_set*angle_per_turn/360):-(int)(angle_set*angle_per_turn/360);
    angle_relative[2]=motor->direction;angle_relative[3]=speed_set>>8;angle_relative[4]=speed_set-angle_relative[3]*16;
    angle_relative[6] = (uint8_t)(motor->angle >> 24);angle_relative[7] = (uint8_t)(motor->angle >> 16);angle_relative[8] = (uint8_t)(motor->angle >> 8);angle_relative[9] = (uint8_t)motor->angle;
    uart1_send_bytes(angle_relative, sizeof(angle_relative));
        break;
    case usart2_mode:
    motor->direction=(angle_set>0)?0x01:0x00;
    motor->angle=(angle_set>0)?(int)(angle_set*angle_per_turn/360):-(int)(angle_set*angle_per_turn/360);
    angle_relative[2]=motor->direction;angle_relative[3]=speed_set>>8;angle_relative[4]=speed_set-angle_relative[3]*16;
    angle_relative[6] = (uint8_t)(motor->angle >> 24);angle_relative[7] = (uint8_t)(motor->angle >> 16);angle_relative[8] = (uint8_t)(motor->angle >> 8);angle_relative[9] = (uint8_t)motor->angle;
    break;
    case can1_mode:
        break;
    case can2_mode:
        break;
    default:
        break;
    }
}
uint8_t ZDT_receive(ZDT_motor* motor)
{
    switch (motor->mode)
    {
    case usart1_mode:
        break;
    case usart2_mode:
        break;
    case can1_mode:
        break;
    case can2_mode:
        break;
    default:
        break;
    }
    switch (motor->move_mode)
    {
    case speed_mode:
        if(receive[1]==receive_speed[1]&&receive[2]==receive_speed[2])
        {
            return 1;
        }
        break;
    case angle_absolute_mode:
        if(receive[1]==receive_angle_absolute[1]&&receive[2]==receive_angle_absolute[2])
        {
            return 1;
        }
    case angle_relative_mode:
        if(receive[1]==receive_angle_relative[1]&&receive[2]==receive_angle_relative[2])
        {
            return 1;
        }
        break;
    default:
        return 0;

    }
		return 0;
}
void uart1_send_char(char ch)
{
    //当串口0忙的时候等待，不忙的时候再发送传进来的字符
    while( DL_UART_isBusy(UART_1_INST) == true );
    //发送单个字符
    DL_UART_Main_transmitData(UART_1_INST, ch);
}
void uart1_send_string(char* str)
{
    //当前字符串地址不在结尾 并且 字符串首地址不为空
    while(*str!=0&&str!=0)
    {
        //发送字符串首地址中的字符，并且在发送完成之后首地址自增
        uart1_send_char(*str++);
    }
}
void uart1_send_bytes(uint8_t* data, uint16_t length)
{
    for(uint16_t i = 0; i < length; i++)
    {
        // 等待发送缓冲区空闲
        while(DL_UART_isBusy(UART_1_INST));
        // 发送单个字节
        DL_UART_Main_transmitData(UART_1_INST, data[i]);
    }
}
