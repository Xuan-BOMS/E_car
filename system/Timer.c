#include "time.h"
#include "Timer.h"
#include "Encoder.h"
#include "Motor_tb.h"
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
    NVIC_ClearPendingIRQ(TIMER_classic_INST_INT_IRQN);
    // 使能定时器中断
    NVIC_EnableIRQ(TIMER_classic_INST_INT_IRQN);
}


