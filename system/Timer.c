#include "Timer.h"
#include "Encoder.h"
#include "Motor.h"
#include "Gray.h"
#include "Tracking.h"
#include "Key.h"
#include "task.h"

//外部变量
extern double Tracking_Error;
extern bool motor_enabled;
extern uint8_t tracking_flag;
//全局变量
int32_t Encoder_cnt[2];

/**
 * @brief  定时器初始化
 * @param  无
 * @retval 无
 */
void TIMER_Init(void)
{
    // 清除定时器中断标志
    NVIC_ClearPendingIRQ(TIMER_0_INST_INT_IRQN);
    // 使能定时器中断
    NVIC_EnableIRQ(TIMER_0_INST_INT_IRQN);
}

/**
 * @brief  定时器中断服务函数 - 每10ms执行一次
 * @param  无
 * @retval 无
 */
void TIMER_0_INST_IRQHandler(void)
{
    // 检查并处理定时器中断
    switch(DL_TimerG_getPendingInterrupt(TIMER_0_INST))
    {
        case DL_TIMER_IIDX_ZERO:  // 零事件中断
		{
			// 按键扫描（10ms周期）
			Key_Scan();
			
			// 编码器更新
			encoder_update();
			get_encoder_count(Encoder_cnt[0],Encoder_cnt[1]);
			
			// 灰度传感器读取
			Gray_Read();
			Tracking_Error = Gray_CalError();
			
			// 电机控制
			if(motor_enabled == true)
			{
				// if (tracking_flag == 1) {
				// 	// 如果正在跟踪
					// Tracking_Update();
				// } else {

				// }
			}else
			{
				Motor_Stop_All();
			}
            
		}
			break;
        default:  // 其他定时器中断
            break;
    }
}
