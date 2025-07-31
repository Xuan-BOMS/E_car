#include "Motor.h"
#include <stdlib.h>
// ���״̬����
static MotorState_t motor_states[MOTOR_COUNT];
bool motor_enabled = false;

/**
 * @brief  ���õ��A��PWM�Ƚ�ֵ
 * @param  dat: PWM�Ƚ�ֵ
 * @retval ��
 */
static void set_motor_a_pwm(uint16_t dat)
{
    DL_TimerG_setCaptureCompareValue(MOTOR_INST, dat, MOTOR_A_PWM_CHANNEL);
}

/**
 * @brief  ���õ��B��PWM�Ƚ�ֵ
 * @param  dat: PWM�Ƚ�ֵ
 * @retval ��
 */
static void set_motor_b_pwm(uint16_t dat)
{
    DL_TimerG_setCaptureCompareValue(MOTOR_INST, dat, MOTOR_B_PWM_CHANNEL);
}

/**
 * @brief  ����PWM���ֵ
 * @param  value: ָ��PWMֵ��ָ��
 * @retval ��
 */
static void restrict_pwm_max_value(uint16_t* value)
{
    if (*value > MOTOR_PWM_MAX) {
        *value = MOTOR_PWM_MAX;
    }
}

/**
 * @brief  ���õ��A�ķ����������
 * @param  direction: �������
 * @retval ��
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
 * @brief  ���õ��B�ķ����������
 * @param  direction: �������
 * @retval ��
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
 * @brief  ʹ�ܵ������
 * @param  ��
 * @retval ��
 */
void Motor_Enable(void)
{
    DL_GPIO_setPins(MOTOR_STBY_PORT, MOTOR_STBY_PIN);
    motor_enabled = true;
}

/**
 * @brief  ���õ������
 * @param  ��
 * @retval ��
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
 * @brief  ���õ�������ٶ�
 * @param  motor_id: ���ID (MOTOR_A �� MOTOR_B)
 * @param  speed: �ٶ�ֵ (0-MOTOR_PWM_MAX)
 * @retval ��
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
 * @brief  ���õ����������
 * @param  motor_id: ���ID
 * @param  direction: �������
 * @retval ��
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
 * @brief  ���Ƶ������(����+�ٶ�)
 * @param  motor_id: ���ID
 * @param  direction: �������
 * @param  speed: �ٶ�ֵ
 * @retval ��
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
 * @brief  ɲ���������
 * @param  motor_id: ���ID
 * @retval ��
 */
void Motor_Brake(uint8_t motor_id)
{
    if (motor_id >= MOTOR_COUNT) return;
    
    Motor_SetDirection(motor_id, MOTOR_DIR_BRAKE);
    Motor_SetSpeed(motor_id, MOTOR_PWM_MAX);
    motor_states[motor_id].enabled = true;
}

/**
 * @brief  ����˫����ٶ�
 * @param  speed_a: ���A�ٶ�
 * @param  speed_b: ���B�ٶ�
 * @retval ��
 */
void Motor_SetBothSpeed(uint16_t speed_a, uint16_t speed_b)
{
    Motor_SetSpeed(MOTOR_A, speed_a);
    Motor_SetSpeed(MOTOR_B, speed_b);
}

/**
 * @brief  ����˫�������
 * @param  dir_a: ���A����
 * @param  dir_b: ���B����
 * @retval ��
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
 * @brief  ֱ���������ҵ���ٶȣ�����ѭ�����ƣ�
 * @param  left_speed: �����ٶ�
 * @param  right_speed: �ҵ���ٶ�
 * @retval ��
 * @note   ������AΪ���������BΪ�ҵ��
 */
void Motor_Set_Speed(uint16_t left_speed, uint16_t right_speed)
{
    // ���õ������Ϊǰ��
    Motor_SetDirection(MOTOR_A, MOTOR_DIR_FORWARD);
    Motor_SetDirection(MOTOR_B, MOTOR_DIR_FORWARD);
    
    // �����ٶ�
    Motor_SetSpeed(MOTOR_A, left_speed);
    Motor_SetSpeed(MOTOR_B, right_speed);
}

/**
 * @brief  ǰ��
 * @param  speed: �ٶ�ֵ
 * @retval ��
 */
void Motor_MoveForward(uint16_t speed)
{
    Motor_Control(MOTOR_A, MOTOR_DIR_FORWARD, speed);
    Motor_Control(MOTOR_B, MOTOR_DIR_FORWARD, speed);
}

/**
 * @brief  ����
 * @param  speed: �ٶ�ֵ
 * @retval ��
 */
void Motor_MoveBackward(uint16_t speed)
{
    Motor_Control(MOTOR_A, MOTOR_DIR_BACKWARD, speed);
    Motor_Control(MOTOR_B, MOTOR_DIR_BACKWARD, speed);
}

/**
 * @brief  ��ת (���A�������B��)
 * @param  speed: �����ٶ�ֵ
 * @retval ��
 */
void Motor_TurnLeft(uint16_t speed)
{
    Motor_Control(MOTOR_A, MOTOR_DIR_FORWARD, speed / 2);
    Motor_Control(MOTOR_B, MOTOR_DIR_FORWARD, speed);
}

/**
 * @brief  ��ת (���A�죬���B��)
 * @param  speed: �����ٶ�ֵ
 * @retval ��
 */
void Motor_TurnRight(uint16_t speed)
{
    Motor_Control(MOTOR_A, MOTOR_DIR_FORWARD, speed);
    Motor_Control(MOTOR_B, MOTOR_DIR_FORWARD, speed / 2);
}

/**
 * @brief  ԭ����ת (���A��ת�����B��ת)
 * @param  speed: �ٶ�ֵ
 * @retval ��
 */
void Motor_Spin_Left(uint16_t speed)
{
    Motor_Control(MOTOR_A, MOTOR_DIR_FORWARD, speed);
    Motor_Control(MOTOR_B, MOTOR_DIR_BACKWARD, speed);
}

/**
 * @brief  ԭ����ת (���A��ת�����B��ת)
 * @param  speed: �ٶ�ֵ
 * @retval ��
 */
void Motor_Spin_Right(uint16_t speed)
{
    Motor_Control(MOTOR_A, MOTOR_DIR_BACKWARD, speed);
    Motor_Control(MOTOR_B, MOTOR_DIR_FORWARD, speed);
}


/**
 * @brief  ��ȡ���״̬
 * @param  motor_id: ���ID
 * @retval ���״̬�ṹ��
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
 * @brief  ����������Ƿ�ʹ��
 * @param  ��
 * @retval true: ʹ��, false: ����
 */
bool Motor_IsEnabled(void)
{
    return motor_enabled;
}

// ===========================================
// ����ԭ�нӿڵĺ���
// ===========================================

/**
 * @brief  ����fi���ŵ�PWM�Ƚ�ֵ(����ԭ�ӿ�)
 * @param  dat: PWM�Ƚ�ֵ
 * @retval ��
 */
static void set_fi(uint16_t dat)
{
    DL_TimerG_setCaptureCompareValue(MOTOR_INST, dat, GPIO_MOTOR_C0_IDX);
}

/**
 * @brief  ����bi���ŵ�PWM�Ƚ�ֵ(����ԭ�ӿ�)
 * @param  dat: PWM�Ƚ�ֵ
 * @retval ��
 */
static void set_bi(uint16_t dat)
{
    DL_TimerG_setCaptureCompareValue(MOTOR_INST, dat, GPIO_MOTOR_C1_IDX);
}

/**
 * @brief  ���õ��(����ԭ�ӿ�)
 * @param  fi_value: ���A��PWMֵ
 * @param  bi_value: ���B��PWMֵ
 * @retval ��
 */
void set_motor(uint16_t fi_value, uint16_t bi_value)
{
    restrict_pwm_max_value(&fi_value);
    restrict_pwm_max_value(&bi_value);

    set_fi(fi_value);
    set_bi(bi_value);
    
    // ����״̬
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

