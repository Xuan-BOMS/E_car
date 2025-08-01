#ifndef _HW_MOTOR_H_
#define _HW_MOTOR_H_

#include "ti_msp_dl_config.h"
#include <stdint.h>
#include <stdbool.h>

// TB6612 电机驱动配置
#define MOTOR_PWM_MAX               3999    // PWM最大值
#define MOTOR_PWM_FREQUENCY         8000    // PWM频率 (Hz)

// 电机编号定义
#define MOTOR_A                     0       // 电机A
#define MOTOR_B                     1       // 电机B
#define MOTOR_COUNT                 2       // 电机总数

// 电机方向定义
typedef enum {
    MOTOR_DIR_STOP = 0,     // 停止
    MOTOR_DIR_FORWARD,      // 正转
    MOTOR_DIR_BACKWARD,     // 反转
    MOTOR_DIR_BRAKE         // 刹车
} MotorDirection_t;

// 电机状态结构体
typedef struct {
    MotorDirection_t direction; // 运行方向
    uint16_t speed;            // 速度 (0-MOTOR_PWM_MAX)
    bool enabled;              // 使能状态
} MotorState_t;

// TB6612控制引脚定义 (需要在ti_msp_dl_config.h中配置对应的GPIO)
// 假设使用以下引脚，请根据实际硬件连接修改
#define MOTOR_A_IN1_PORT           GPIOB
#define MOTOR_A_IN1_PIN            DL_GPIO_PIN_25
#define MOTOR_A_IN2_PORT           GPIOA
#define MOTOR_A_IN2_PIN            DL_GPIO_PIN_25

#define MOTOR_B_IN1_PORT           GPIOA
#define MOTOR_B_IN1_PIN            DL_GPIO_PIN_14
#define MOTOR_B_IN2_PORT           GPIOB
#define MOTOR_B_IN2_PIN            DL_GPIO_PIN_17

// STBY引脚 (standby控制)
#define MOTOR_STBY_PORT            GPIOB
#define MOTOR_STBY_PIN             DL_GPIO_PIN_20

// PWM通道定义
#define MOTOR_A_PWM_CHANNEL        GPIO_MOTOR_C0_IDX  // 电机A使用PWM通道0
#define MOTOR_B_PWM_CHANNEL        GPIO_MOTOR_C1_IDX  // 电机B使用PWM通道1

// 基础控制函数
void Motor_Init(void);
void Motor_Enable(void);
void Motor_Disable(void);
void Motor_Stop_All(void);

// 单个电机控制函数
void Motor_SetSpeed(uint8_t motor_id, uint16_t speed);
void Motor_SetDirection(uint8_t motor_id, MotorDirection_t direction);
void Motor_Control(uint8_t motor_id, MotorDirection_t direction, uint16_t speed);

void Motor_Stop(uint8_t motor_id);
void Motor_Brake(uint8_t motor_id);

// 双电机控制函数
void Motor_SetBothSpeed(uint16_t speed_a, uint16_t speed_b);
void Motor_SetBothDirection(MotorDirection_t dir_a, MotorDirection_t dir_b);
void Motor_SetBothDirAndSpeed(MotorDirection_t dir_a, uint16_t speed_a, MotorDirection_t dir_b, uint16_t speed_b);
void Motor_Set_Speed(uint16_t left_speed, uint16_t right_speed);  // 直接设置左右电机速度
void Motor_MoveForward(uint16_t speed);
void Motor_MoveBackward(uint16_t speed);
void Motor_TurnLeft(uint16_t speed);
void Motor_TurnRight(uint16_t speed);
void Motor_Spin_Left(uint16_t speed);
void Motor_Spin_Right(uint16_t speed);
void Motor_Set_dir_Speed(int16_t left_speed, int16_t right_speed);
// 状态查询函数
MotorState_t Motor_GetState(uint8_t motor_id);
bool Motor_IsEnabled(void);

// 兼容原有接口的函数
void set_motor(uint16_t fi_value, uint16_t bi_value);
void stop_motor(void);

#endif /* _HW_MOTOR_H_ */