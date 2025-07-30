#ifndef MOTOR_H
#define MOTOR_H

#include "../ti_msp_dl_config.h"
#define LIMIT(value, min, max) ((value) > (max) ? (max) : ((value) < (min) ? (min) : (value)))
typedef struct {
    int8_t Motor_Left_Speed;
    int8_t Motor_Right_Speed;
} MotorSpeed_t;

void motor_init(void);
void motor_setSpeed(void);
MotorSpeed_t* motor_getSpeed(void);
#endif // !MOTOR_H
