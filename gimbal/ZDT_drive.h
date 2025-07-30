//zdt电机驱动相关，经测试问题不大，无需更改（
#ifndef __ZDT_drive_H__
#define __ZDT_drive_H__
#include "../ti_msp_dl_config.h"
#define usart1_mode 0
#define usart2_mode 1
#define can1_mode 2
#define can2_mode 3
#define Pitch_motoradd 1
#define Yaw_motoradd 2
#define speed_mode 0
#define angle_absolute_mode 1
#define angle_relative_mode 2
#define angle_per_turn 3200 //单圈所需脉冲数
typedef struct
{
    int16_t mode;                  //电机模式
    int16_t move_mode;             //电机运动模式
    int16_t address;               //电机地址
    int16_t speed;                 //电机速度
    int16_t angle;                 //电机角度
    int16_t direction;             //电机转动方向
    int16_t acceleration;          //电机加速度
}ZDT_motor;
void ZDT_init(int16_t mode_set,int16_t address, ZDT_motor* motor);
void ZDT_speed(int16_t speed_set,int16_t address, ZDT_motor* motor);
void ZDT_angle_relative(int16_t angle_set,int16_t speed_set,int16_t address, ZDT_motor* motor);
void ZDT_angle_absolute(int16_t angle_set,int16_t speed_set,int16_t address, ZDT_motor* motor);
uint8_t ZDT_receive(ZDT_motor* motor);
void uart1_send_char(char ch);
void uart1_send_string(char* str);
void uart1_send_bytes(uint8_t* data, uint16_t length);
#endif
