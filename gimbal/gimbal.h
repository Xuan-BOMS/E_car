#ifndef GIMBAL_H
#define GIMBAL_H
#include "../ti_msp_dl_config.h"
#include "ZDT_drive.h"
#include "vision.h"
#define OFFSET_SCALE 0.2 // 差值换算
typedef struct {
    int16_t pitch;  // 俯仰角度
    int16_t yaw;    // 偏航角度
    ZDT_motor pitch_motor;
    ZDT_motor yaw_motor;
    vision_data_t* vision_data;
    int16_t turn_angle; // 防止转圈绕线的角度控制
} GimbalPosition;
void gimbal_init(void);
void gimbal_set_position(void);  // 无参数版本
void gimbal_motor_move(void);
void gimbal_get_position(void);
void TIMER_gimbal_INST_IRQHandler(void);
GimbalPosition* gimbal_get_position_struct(void);

#endif // GIMBAL_H
