#include "Tracking.h"
#include "Gray.h"
#include "motorDK.h"
#include "PID.h"
#include "max_min.h"
#include "chassis.h"
//外部变量
extern uint8_t Gray[5];
//全局变量
double Tracking_Error= 0.0f;       // 灰度传感器误差值
static PID pid_line_follow;  
int16_t Motor_Speed[2];

void Tracking_PID_Init(void)
{
    // 初始化PID控制器
    pid_init(&pid_line_follow, PID_KP, PID_KI, PID_KD, PID_MAX_I, PID_MAX_OUTPUT, 0.0);
}
void Tracking_Update(void)
{
    pid_line_follow.output = pid_calc(&pid_line_follow, 0.0f, Tracking_Error);

    // 基础速度
    uint16_t base_speed = MOTOR_Target_Speed1;
    int8_t motor_Speed[2];
    Tracking_Error = Gray_CalError(); // 获取灰度传感器误差值
    // 根据PID输出调整左右电机速度
    motor_Speed[0] = base_speed - (int8_t)pid_line_follow.output;
    motor_Speed[1] = base_speed + (int8_t)pid_line_follow.output;
    // 限制速度范围
    motor_Speed[0] = Limit_Range(motor_Speed[0], MOTOR_MIN_SPEED, MOTOR_MAX_SPEED);
    motor_Speed[1] = Limit_Range(motor_Speed[1], MOTOR_MIN_SPEED, MOTOR_MAX_SPEED);
	
	Chassis_setSpeed(motor_Speed[0], motor_Speed[1]);
	
	// 控制电机
    // Motor_Control(MOTOR_A, MOTOR_DIR_FORWARD, Motor_Speed[0]);
    // Motor_Control(MOTOR_B, MOTOR_DIR_FORWARD, Motor_Speed[1]);

//    Motor_Set_dir_Speed(Motor_Speed[0], Motor_Speed[1]);
//    Motor_Enable();
}
