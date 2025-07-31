#include "Tracking.h"
#include "Motor.h"
#include "PID.h"
#include "max_min.h"
//�ⲿ����
extern uint8_t Gray[16];
//ȫ�ֱ���
double Tracking_Error= 0.0f;       // �Ҷȴ�����ֵ
static PID pid_line_follow;  
int16_t Motor_Speed[2];

void Tracking_PID_Init(void)
{
    // ��ʼ��PID������
    pid_init(&pid_line_follow, PID_KP, PID_KI, PID_KD, PID_MAX_I, PID_MAX_OUTPUT, 0.0);
}
void Tracking_Update(void)
{
    pid_line_follow.output = pid_calc(&pid_line_follow, 0.0f, Tracking_Error);

    // �����ٶ�
    uint16_t base_speed = MOTOR_Target_Speed1;
    int16_t motor_Speed[2];
    // ����PID����������ҵ���ٶ�
    motor_Speed[0] = base_speed - (int16_t)pid_line_follow.output;
    motor_Speed[1] = base_speed + (int16_t)pid_line_follow.output;
    // �����ٶȷ�Χ
    motor_Speed[0] = Limit_Range(motor_Speed[0], MOTOR_MIN_SPEED, MOTOR_MAX_SPEED);
    motor_Speed[1] = Limit_Range(motor_Speed[1], MOTOR_MIN_SPEED, MOTOR_MAX_SPEED);
	
	Motor_Speed[0] = motor_Speed[0];
	Motor_Speed[1] = motor_Speed[1];
	
	// ���Ƶ��
    // Motor_Control(MOTOR_A, MOTOR_DIR_FORWARD, Motor_Speed[0]);
    // Motor_Control(MOTOR_B, MOTOR_DIR_FORWARD, Motor_Speed[1]);

    Motor_Set_dir_Speed(Motor_Speed[0], Motor_Speed[1]);
    Motor_Enable();
}
