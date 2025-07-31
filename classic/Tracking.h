#include "../ti_msp_dl_config.h"

#define MOTOR_Target_Speed0 500  //目标速度0
#define MOTOR_Target_Speed1 1000 //目标速度1
#define MOTOR_Target_Speed2 1500 //目标速度2
#define MOTOR_Target_Speed3 2000 //目标速度3
#define MOTOR_Target_Speed4 2500 //目标速度4
#define MOTOR_Target_Speed5 3000 //目标速度5
#define MOTOR_Target_Speed6 3500 //目标速度6

#define MOTOR_MAX_SPEED 3999 //电机最大速度
#define MOTOR_MIN_SPEED 0    //电机最小速度

#define PID_KP 30.0f
#define PID_KI 0.0f
#define PID_KD 0.0f
#define PID_MAX_I 1000.0f
#define PID_MAX_OUTPUT 2000.0f

void Tracking_PID_Init(void);
void Tracking_Update(void);
