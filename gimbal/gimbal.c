#include "gimbal.h"
#include "time.h"
GimbalPosition gimbal;
uint8_t angle_text[]={0x01,0xFB,0x00,0x01,0x20,0x00,0x00,0x0A,0x0A,0x00,0x00,0x6B};
void gimbal_init(void)
{
    // 初始化云台位置
    gimbal.pitch = 0;
    gimbal.yaw = 0;
    gimbal.pitch_motor.mode = usart1_mode; // 设置电机模式
    gimbal.pitch_motor.address = Pitch_motoradd; // 设置电机地址
    gimbal.pitch_motor.move_mode = angle_absolute_mode; // 设置电机运动模式
    gimbal.pitch_motor.speed = 0x0120; // 初始速度
    gimbal.pitch_motor.angle = 0; // 初始角度
    gimbal.pitch_motor.direction = 0; // 初始方向
    gimbal.pitch_motor.acceleration = 0; // 初始加速度,0是最大
    gimbal.yaw_motor.mode = usart1_mode; // 设置电机模式
    gimbal.yaw_motor.address = Yaw_motoradd; // 设置电机地址
    gimbal.yaw_motor.move_mode = angle_absolute_mode; // 设置电机运动模式
    gimbal.yaw_motor.speed = 0x0120; // 初始速度
    gimbal.yaw_motor.angle = 0; // 初始角度
    gimbal.yaw_motor.direction = 0; // 初始方向
    gimbal.yaw_motor.acceleration = 0; // 初始加速度,0是最大
    ZDT_init(gimbal.pitch_motor.mode, gimbal.pitch_motor.address, &gimbal.pitch_motor);
    ZDT_init(gimbal.yaw_motor.mode, gimbal.yaw_motor.address, &gimbal.yaw_motor);
    gimbal.vision_data = vision_get_data();
}
void gimbal_set_position(void)
{
    gimbal.pitch += (int16_t)(gimbal.vision_data->y_offset * OFFSET_SCALE); // 使用视觉数据的y偏移
    gimbal.yaw += (int16_t)(gimbal.vision_data->x_offset * OFFSET_SCALE); // 使用视觉数据的x偏移
}
void gimbal_motor_move(void)
{
    gimbal.pitch_motor.angle = gimbal.pitch; 
    gimbal.yaw_motor.angle = gimbal.yaw; 
    // 设置俯仰电机和偏航电机的角度
}
void TIMER_gimbal_INST_IRQHandler(void)
{
    static uint8_t send_mode = 0;
    //如果产生了定时器中断
    switch( DL_TimerG_getPendingInterrupt(TIMER_gimbal_INST) )
    {
        case DL_TIMER_IIDX_ZERO://如果是0溢出中断
            gimbal_set_position();
            gimbal_motor_move(); // 控制云台电机移动
            switch(send_mode)
            {
                case 0:
                    // 发送俯仰电机的角度
                    ZDT_angle_absolute(gimbal.pitch_motor.angle, gimbal.pitch_motor.speed, gimbal.pitch_motor.address, &gimbal.pitch_motor);
                    send_mode = 1;
					NVIC_ClearPendingIRQ(TIMER_gimbal_INST_INT_IRQN);
                    break;
                case 1:
                    // 发送偏航电机的角度
                    ZDT_angle_absolute(gimbal.yaw_motor.angle, gimbal.yaw_motor.speed, gimbal.yaw_motor.address, &gimbal.yaw_motor);
                    send_mode = 0;
					NVIC_ClearPendingIRQ(TIMER_gimbal_INST_INT_IRQN);
                    break;
            }
            break;
        default://其他的定时器中断
            break;
    }
}
GimbalPosition* gimbal_get_position_struct(void)
{
    return &gimbal;
}
