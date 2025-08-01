#ifndef __CHASSIS_H__
#include "../ti_msp_dl_config.h"
#include "time.h"
#include "Timer.h"
#include "motorDK.h"
#include "hwt101.h"
#include "Gray.h"
#include "Tracking.h"
#include "Key.h"
#include "task.h"
typedef enum {
    MOVE_FORWARD = 0,  // 前进
    MOVE_BACKWARD,     // 后退
    MOVE_LEFT,         // 左转
    MOVE_RIGHT,        // 右转
} ChassisType_t;
typedef struct {
    uint8_t motor_enabled; // 电机使能标志
    ChassisType_t type; // 运动类型
    MotorSpeed_t* motor_speed; // 电机速度结构体
    HWT101_Data_t* hwt_data; // 陀螺仪数据结构体
    double Tracking_Error;
    bool Gray_DetectStartLine; // 是否检测到起始线
} Chassis_t;
void Chassis_Init(void);
void Chassis_update(void);
void TIMER_classic_INST_IRQHandler(void);
void Chassis_setSpeed(int8_t left_speed, int8_t right_speed);
#endif // !__CHASSIS_H__