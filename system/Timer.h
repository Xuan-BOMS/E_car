#ifndef __TIMER_H
#define __TIMER_H

#include "ti_msp_dl_config.h"
#include <stdint.h>

// 定时器配置
#define TIMER_KEY_SCAN_PERIOD_MS    10  // 按键扫描周期(ms)

// 函数声明
void TIMER_Init(void);
void TIMER_KeyScan_Init(void);
void TIMER_KeyScan_Start(void);
void TIMER_KeyScan_Stop(void);

#endif /* __TIMER_H */
