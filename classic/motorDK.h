#ifndef MOTOR_DK_H_
#define MOTOR_DK_H_

#include "../ti_msp_dl_config.h"
#define LIMIT(value, min, max) ((value) > (max) ? (max) : ((value) < (min) ? (min) : (value)))
typedef struct {
    int8_t Motor_Left_Speed;
    int8_t Motor_Right_Speed;
} MotorSpeed_t;

void motor_init(void);
void motor_setSpeed(void);
MotorSpeed_t* Motor_Get_Speed_Pointer(void);
#endif // !MOTOR_H
