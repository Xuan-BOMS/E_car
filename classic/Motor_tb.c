#include "Motor_tb.h"
#include <stdlib.h>
// 电机状态数组
static MotorState_t motor_states[MOTOR_COUNT];
bool motor_enabled = false;
/**
 * @brief  设置电机A的PWM比较值
 * @param  dat: PWM比较值
 * @retval 无
 */
static void set_motor_a_pwm(uint16_t dat)
{
    DL_TimerG_setCaptureCompareValue(MOTOR_INST, dat, MOTOR_A_PWM_CHANNEL);
}

/**
 * @brief  设置电机B的PWM比较值
 * @param  dat: PWM比较值
 * @retval 无
 */
static void set_motor_b_pwm(uint16_t dat)
{
    DL_TimerG_setCaptureCompareValue(MOTOR_INST, dat, MOTOR_B_PWM_CHANNEL);
}

/**
 * @brief  限制PWM最大值
 * @param  value: 指向PWM值的指针
 * @retval 无
 */
static void restrict_pwm_max_value(uint16_t* value)
{
    if (*value > MOTOR_PWM_MAX) {
        *value = MOTOR_PWM_MAX;
    }
}

/**
 * @brief  设置电机A的方向控制引脚
 * @param  direction: 转动方向
 * @retval 无
 */
static void set_motor_a_direction_pins(MotorDirection_t direction)
{
    switch (direction) {
        case MOTOR_DIR_BACKWARD:
            DL_GPIO_setPins(GPIO_MOTOR_DIR_AIN_1_PORT, GPIO_MOTOR_DIR_AIN_1_PIN);
            DL_GPIO_clearPins(GPIO_MOTOR_DIR_AIN_2_PORT, GPIO_MOTOR_DIR_AIN_2_PIN);
            break;
            
        case MOTOR_DIR_FORWARD:
            DL_GPIO_clearPins(GPIO_MOTOR_DIR_AIN_1_PORT, GPIO_MOTOR_DIR_AIN_1_PIN);
            DL_GPIO_setPins(GPIO_MOTOR_DIR_AIN_2_PORT, GPIO_MOTOR_DIR_AIN_2_PIN);
            break;
            
        case MOTOR_DIR_BRAKE:
            DL_GPIO_setPins(GPIO_MOTOR_DIR_AIN_1_PORT, GPIO_MOTOR_DIR_AIN_1_PIN);
            DL_GPIO_setPins(GPIO_MOTOR_DIR_AIN_2_PORT, GPIO_MOTOR_DIR_AIN_2_PIN);
            break;
            
        case MOTOR_DIR_STOP:
        default:
            DL_GPIO_clearPins(GPIO_MOTOR_DIR_AIN_1_PORT, GPIO_MOTOR_DIR_AIN_1_PIN);
            DL_GPIO_clearPins(GPIO_MOTOR_DIR_AIN_2_PORT, GPIO_MOTOR_DIR_AIN_2_PIN);
            break;
    }
}

/**
 * @brief  设置电机B的方向控制引脚
 * @param  direction: 转动方向
 * @retval 无
 */
static void set_motor_b_direction_pins(MotorDirection_t direction)
{
    switch (direction) {
        case MOTOR_DIR_BACKWARD:
            DL_GPIO_setPins(GPIO_MOTOR_DIR_BIN_1_PORT, GPIO_MOTOR_DIR_BIN_1_PIN);
            DL_GPIO_clearPins(GPIO_MOTOR_DIR_BIN_2_PORT, GPIO_MOTOR_DIR_BIN_2_PIN);
            break;
            
        case  MOTOR_DIR_FORWARD:
            DL_GPIO_clearPins(GPIO_MOTOR_DIR_BIN_1_PORT, GPIO_MOTOR_DIR_BIN_1_PIN);
            DL_GPIO_setPins(GPIO_MOTOR_DIR_BIN_2_PORT, GPIO_MOTOR_DIR_BIN_2_PIN);
            break;
            
        case MOTOR_DIR_BRAKE:
            DL_GPIO_setPins(GPIO_MOTOR_DIR_BIN_1_PORT, GPIO_MOTOR_DIR_BIN_1_PIN);
            DL_GPIO_setPins(GPIO_MOTOR_DIR_BIN_2_PORT, GPIO_MOTOR_DIR_BIN_2_PIN);
            break;
            
        case MOTOR_DIR_STOP:
        default:
            DL_GPIO_clearPins(GPIO_MOTOR_DIR_BIN_1_PORT, GPIO_MOTOR_DIR_BIN_1_PIN);
            DL_GPIO_clearPins(GPIO_MOTOR_DIR_BIN_2_PORT, GPIO_MOTOR_DIR_BIN_2_PIN);
            break;
    }
}

/**
 * @brief  �����ʼ��
 * @param  ��
 * @retval ��
 */
void Motor_Init(void)
{
    // ��ʼ�����״̬
    for (int i = 0; i < MOTOR_COUNT; i++) {
        motor_states[i].direction = MOTOR_DIR_STOP;
        motor_states[i].speed = 0;
        motor_states[i].enabled = false;
    }
    motor_enabled = false;
    // ��ʼ״̬����������Ϊ�͵�ƽ�����ֹͣ
    Motor_Stop_All();
    Motor_Disable();
}

/**
 * @brief  使能电机驱动
 * @param  无
 * @retval 无
 */
void Motor_Enable(void)
{
    DL_GPIO_setPins(MOTOR_STBY_PORT, MOTOR_STBY_PIN);
    motor_enabled = true;
}

/**
 * @brief  禁用电机驱动
 * @param  无
 * @retval 无
 */
void Motor_Disable(void)
{
    DL_GPIO_clearPins(MOTOR_STBY_PORT, MOTOR_STBY_PIN);
    motor_enabled = false;
}

/**
 * @brief  ֹͣ���е��
 * @param  ��
 * @retval ��
 */
void Motor_Stop_All(void)
{
    Motor_Stop(MOTOR_A);
    Motor_Stop(MOTOR_B);
}

/**
 * @brief  设置电机转动速度
 * @param  motor_id: 电机ID (MOTOR_A 或 MOTOR_B)
 * @param  speed: 速度值 (0-MOTOR_PWM_MAX)
 * @retval 无
 */
void Motor_SetSpeed(uint8_t motor_id, uint16_t speed)
{
    if (motor_id >= MOTOR_COUNT) return;
    
    restrict_pwm_max_value(&speed);
    motor_states[motor_id].speed = speed;
    
    if (motor_id == MOTOR_A) {
        set_motor_a_pwm(speed);
    } else {
        set_motor_b_pwm(speed);
    }
}

/**
 * @brief  设置电机转动方向
 * @param  motor_id: 电机ID
 * @param  direction: 转动方向
 * @retval 无
 */
void Motor_SetDirection(uint8_t motor_id, MotorDirection_t direction)
{
    if (motor_id >= MOTOR_COUNT) return;
    
    motor_states[motor_id].direction = direction;
    
    if (motor_id == MOTOR_A) {
        set_motor_a_direction_pins(direction);
    } else {
        set_motor_b_direction_pins(direction);
    }
}

/**
 * @brief  控制电机运转(方向+速度)
 * @param  motor_id: 电机ID
 * @param  direction: 转动方向
 * @param  speed: 速度值
 * @retval 无
 */
void Motor_Control(uint8_t motor_id, MotorDirection_t direction, uint16_t speed)
{
    if (motor_id >= MOTOR_COUNT) return;
    
    Motor_SetDirection(motor_id, direction);
    
    if (direction == MOTOR_DIR_STOP) {
        Motor_SetSpeed(motor_id, 0);
    } else {
        Motor_SetSpeed(motor_id, speed);
    }
    
    motor_states[motor_id].enabled = (direction != MOTOR_DIR_STOP);
}
void Motor_Set_dir_Speed(int16_t left_speed, int16_t right_speed)
{
    Motor_SetDirection(MOTOR_A, left_speed > 0 ? MOTOR_DIR_FORWARD : MOTOR_DIR_BACKWARD);
    Motor_SetSpeed(MOTOR_A, abs(left_speed));
    Motor_SetDirection(MOTOR_B, right_speed > 0 ? MOTOR_DIR_FORWARD : MOTOR_DIR_BACKWARD);
    Motor_SetSpeed(MOTOR_B, abs(right_speed));
}

/**
 * @brief  ֹͣ�������
 * @param  motor_id: ���ID
 * @retval ��
 */
void Motor_Stop(uint8_t motor_id)
{
    Motor_Control(motor_id, MOTOR_DIR_STOP, 0);
}

/**
 * @brief  刹车停止电机
 * @param  motor_id: 电机ID
 * @retval 无
 */
void Motor_Brake(uint8_t motor_id)
{
    if (motor_id >= MOTOR_COUNT) return;
    
    Motor_SetDirection(motor_id, MOTOR_DIR_BRAKE);
    Motor_SetSpeed(motor_id, MOTOR_PWM_MAX);
    motor_states[motor_id].enabled = true;
}

/**
 * @brief  设置双电机速度
 * @param  speed_a: 电机A速度
 * @param  speed_b: 电机B速度
 * @retval 无
 */
void Motor_SetBothSpeed(uint16_t speed_a, uint16_t speed_b)
{
    Motor_SetSpeed(MOTOR_A, speed_a);
    Motor_SetSpeed(MOTOR_B, speed_b);
}

/**
 * @brief  设置双电机方向
 * @param  dir_a: 电机A方向
 * @param  dir_b: 电机B方向
 * @retval 无
 */
void Motor_SetBothDirection(MotorDirection_t dir_a, MotorDirection_t dir_b)
{
    Motor_SetDirection(MOTOR_A, dir_a);
    Motor_SetDirection(MOTOR_B, dir_b);
}

void Motor_SetBothDirAndSpeed(MotorDirection_t dir_a, uint16_t speed_a, MotorDirection_t dir_b, uint16_t speed_b)
{
    Motor_SetDirection(MOTOR_A, dir_a);
    Motor_SetSpeed(MOTOR_A, speed_a);
    Motor_SetDirection(MOTOR_B, dir_b);
    Motor_SetSpeed(MOTOR_B, speed_b);
}

/**
 * @brief  直接设置左右电机速度（正向循迹控制）
 * @param  left_speed: 左侧速度
 * @param  right_speed: 右侧速度
 * @retval 无
 * @note   默认电机A为左侧，电机B为右侧
 */
void Motor_Set_Speed(uint16_t left_speed, uint16_t right_speed)
{
    // 设置电机方向为前进
    Motor_SetDirection(MOTOR_A, MOTOR_DIR_FORWARD);
    Motor_SetDirection(MOTOR_B, MOTOR_DIR_FORWARD);
    
    // 设置速度
    Motor_SetSpeed(MOTOR_A, left_speed);
    Motor_SetSpeed(MOTOR_B, right_speed);
}

/**
 * @brief  前进
 * @param  speed: 速度值
 * @retval 无
 */
void Motor_MoveForward(uint16_t speed)
{
    Motor_Control(MOTOR_A, MOTOR_DIR_FORWARD, speed);
    Motor_Control(MOTOR_B, MOTOR_DIR_FORWARD, speed);
}

/**
 * @brief  后退
 * @param  speed: 速度值
 * @retval 无
 */
void Motor_MoveBackward(uint16_t speed)
{
    Motor_Control(MOTOR_A, MOTOR_DIR_BACKWARD, speed);
    Motor_Control(MOTOR_B, MOTOR_DIR_BACKWARD, speed);
}

/**
 * @brief  左转 (电机A减速，电机B正常)
 * @param  speed: 基准速度值
 * @retval 无
 */
void Motor_TurnLeft(uint16_t speed)
{
    Motor_Control(MOTOR_A, MOTOR_DIR_FORWARD, speed / 2);
    Motor_Control(MOTOR_B, MOTOR_DIR_FORWARD, speed);
}

/**
 * @brief  右转 (电机A正常，电机B减速)
 * @param  speed: 基准速度值
 * @retval 无
 */
void Motor_TurnRight(uint16_t speed)
{
    Motor_Control(MOTOR_A, MOTOR_DIR_FORWARD, speed);
    Motor_Control(MOTOR_B, MOTOR_DIR_FORWARD, speed / 2);
}

/**
 * @brief  原地左转 (电机A正转，电机B反转)
 * @param  speed: 速度值
 * @retval 无
 */
void Motor_Spin_Left(uint16_t speed)
{
    Motor_Control(MOTOR_A, MOTOR_DIR_FORWARD, speed);
    Motor_Control(MOTOR_B, MOTOR_DIR_BACKWARD, speed);
}

/**
 * @brief  原地右转 (电机A反转，电机B正转)
 * @param  speed: 速度值
 * @retval 无
 */
void Motor_Spin_Right(uint16_t speed)
{
    Motor_Control(MOTOR_A, MOTOR_DIR_BACKWARD, speed);
    Motor_Control(MOTOR_B, MOTOR_DIR_FORWARD, speed);
}


/**
 * @brief  获取电机状态
 * @param  motor_id: 电机ID
 * @retval 电机状态结构体
 */
MotorState_t Motor_GetState(uint8_t motor_id)
{
    MotorState_t empty_state = {MOTOR_DIR_STOP, 0, false};
    
    if (motor_id >= MOTOR_COUNT) {
        return empty_state;
    }
    
    return motor_states[motor_id];
}

/**
 * @brief  检测电机驱动是否使能
 * @param  无
 * @retval true: 使能, false: 禁用
 */
bool Motor_IsEnabled(void)
{
    return motor_enabled;
}

// ===========================================
// 保留原有接口的函数
// ===========================================

/**
 * @brief  设置fi通道的PWM比较值(保留原接口)
 * @param  dat: PWM比较值
 * @retval 无
 */
static void set_fi(uint16_t dat)
{
    DL_TimerG_setCaptureCompareValue(MOTOR_INST, dat, GPIO_MOTOR_C0_IDX);
}

/**
 * @brief  设置bi通道的PWM比较值(保留原接口)
 * @param  dat: PWM比较值
 * @retval 无
 */
static void set_bi(uint16_t dat)
{
    DL_TimerG_setCaptureCompareValue(MOTOR_INST, dat, GPIO_MOTOR_C1_IDX);
}

/**
 * @brief  设置电机(保留原接口)
 * @param  fi_value: 电机A的PWM值
 * @param  bi_value: 电机B的PWM值
 * @retval 无
 */
void set_motor(uint16_t fi_value, uint16_t bi_value)
{
    restrict_pwm_max_value(&fi_value);
    restrict_pwm_max_value(&bi_value);

    set_fi(fi_value);
    set_bi(bi_value);
    
    // 更新状态
    motor_states[MOTOR_A].speed = fi_value;
    motor_states[MOTOR_B].speed = bi_value;
}

/**
 * @brief  ���ֹͣ(����ԭ�ӿ�)
 * @param  ��
 * @retval ��
 */
void stop_motor(void)
{
    Motor_Stop_All();
}

