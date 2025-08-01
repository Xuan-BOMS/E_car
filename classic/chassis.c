#include "chassis.h"
Chassis_t chassis;
void Chassis_Init(void)
{
    // 清除定时器中断标志
    NVIC_ClearPendingIRQ(TIMER_classic_INST_INT_IRQN);
    // 使能定时器中断
    NVIC_EnableIRQ(TIMER_classic_INST_INT_IRQN);
	motor_init(); // 初始化电机
	chassis.motor_enabled = true; // 默认使能电机
    chassis.hwt_data= HWT101_Get_Data_Pointer();
	chassis.motor_speed = Motor_Get_Speed_Pointer();
}
void Chassis_update(void)
{
	// 更新底盘状态
	chassis.Tracking_Error = Gray_CalError();
	chassis.Gray_DetectStartLine = Gray_DetectStartLine();
	// 其他更新逻辑...
}
void TIMER_classic_INST_IRQHandler(void)
{
    // 检查并处理定时器中断
    switch(DL_TimerG_getPendingInterrupt(TIMER_classic_INST))
    {
        case DL_TIMER_IIDX_ZERO:  // 零事件中断
		{
			// 按键扫描（10ms周期）
			Key_Scan();
			// 灰度传感器读取
			Gray_Read();
			Chassis_update();
			motor_setSpeed();
			// 电机控制
			if(chassis.motor_enabled == true)
			{
				// if (tracking_flag == 1) {
				// 	// 如果正在跟踪
					// Tracking_Update();
				// } else {

				// }
			}else
			{
				//Motor_Stop_All();
			}
            
		}
			break;
        default:  // 其他定时器中断
            break;
    }
}
void Chassis_setSpeed(int8_t left_speed, int8_t right_speed)
{
	chassis.motor_speed->Motor_Left_Speed = left_speed;
	chassis.motor_speed->Motor_Right_Speed = right_speed;
}
float get_YAW_Angle(void)
{
	if(chassis.hwt_data->type_mode == 1) // 数据有效
	{
		return chassis.hwt_data->YAW; // 返回偏航角度
	}
	return 0.0f; // 数据无效时返回0
}