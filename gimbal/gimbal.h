#ifndef GIMBAL_H
#define GIMBAL_H
#include "ti_msp_dl_config.h"
#include "ZDT_drive.h"
#include "vision.h"
//像素计算
#define OFFSET_PITCH_MIN -200
#define OFFSET_PITCH_MAX 200
#define OFFSET_YAW_MIN -200
#define OFFSET_YAW_MAX 200
#define OFFSET_PITCH_SCALE 0.005 // 差值换算
#define OFFSET_YAW_SCALE 0.005 // 差值换算
// 在头文件中添加限位宏
#define GIMBAL_ANGLE_MAX    7200
#define GIMBAL_ANGLE_MIN   -7200
#define GIMBAL_PITCH_MAX   450
#define GIMBAL_PITCH_MIN   -450
#define GIMBAL_YAW_MAX     1800
#define GIMBAL_YAW_MIN    -1800
// 限位宏函数
#define LIMIT_ANGLE(value, min, max) \
    ((value) > (max) ? (max) : ((value) < (min) ? (min) : (value)))
//速度
#define GIMBAL_PITCH_SPEED 0x0A80 // 352
#define GIMBAL_PITCH_ACCELERATION 0x1B00 // 2816
#define GIMBAL_YAW_SPEED 0x0A80 // 352
#define GIMBAL_YAW_ACCELERATION 0x1F00 // 2816
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
