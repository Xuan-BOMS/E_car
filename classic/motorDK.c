#include "motorDK.h"
MotorSpeed_t MotorSpeed;
void motor_init(void) {
    MotorSpeed.Motor_Left_Speed = 0;
    MotorSpeed.Motor_Right_Speed = 0;
}

void motor_setSpeed(void) {
    MotorSpeed.Motor_Left_Speed = LIMIT(MotorSpeed.Motor_Left_Speed, -100, 100);
    MotorSpeed.Motor_Right_Speed = LIMIT(MotorSpeed.Motor_Right_Speed, -100, 100);
    if(MotorSpeed.Motor_Right_Speed < 0) {
        DL_TimerG_setCaptureCompareValue(PWM_MotorL_INST, -MotorSpeed.Motor_Right_Speed, GPIO_PWM_MotorL_C0_IDX); // 设置左电机正转
        DL_TimerG_setCaptureCompareValue(PWM_MotorL_INST, 0, GPIO_PWM_MotorL_C1_IDX); // 停止左电机反转
    } else if(MotorSpeed.Motor_Right_Speed == 0) {
        DL_TimerG_setCaptureCompareValue(PWM_MotorL_INST, 0, GPIO_PWM_MotorL_C0_IDX);
        DL_TimerG_setCaptureCompareValue(PWM_MotorL_INST, 0, GPIO_PWM_MotorL_C1_IDX);
    } else if(MotorSpeed.Motor_Right_Speed > 0) {
        DL_TimerG_setCaptureCompareValue(PWM_MotorL_INST, MotorSpeed.Motor_Right_Speed, GPIO_PWM_MotorL_C1_IDX); // 设置左电机反转
        DL_TimerG_setCaptureCompareValue(PWM_MotorL_INST, 0, GPIO_PWM_MotorL_C0_IDX); // 停止左电机正转
    }
    if(MotorSpeed.Motor_Left_Speed < 0) {
        DL_TimerG_setCaptureCompareValue(PWM_MotorR_INST, -MotorSpeed.Motor_Left_Speed, GPIO_PWM_MotorR_C0_IDX); // 设置右电机正转
        DL_TimerG_setCaptureCompareValue(PWM_MotorR_INST, 0, GPIO_PWM_MotorR_C1_IDX); // 停止右电机反转
    } else if(MotorSpeed.Motor_Left_Speed == 0) {
        DL_TimerG_setCaptureCompareValue(PWM_MotorR_INST, 0, GPIO_PWM_MotorR_C0_IDX);
        DL_TimerG_setCaptureCompareValue(PWM_MotorR_INST, 0, GPIO_PWM_MotorR_C1_IDX);
    } else if(MotorSpeed.Motor_Left_Speed > 0) {
        DL_TimerG_setCaptureCompareValue(PWM_MotorR_INST, MotorSpeed.Motor_Left_Speed, GPIO_PWM_MotorR_C1_IDX); // 设置右电机反转
        DL_TimerG_setCaptureCompareValue(PWM_MotorR_INST, 0, GPIO_PWM_MotorR_C0_IDX); // 停止右电机正转
    }
}
MotorSpeed_t* Motor_Get_Speed_Pointer(void) {
    return &MotorSpeed;
}