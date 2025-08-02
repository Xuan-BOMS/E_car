#ifndef __TASK_H__
#define __TASK_H__

#include "ti_msp_dl_config.h"
#include "Key.h"
#include "Timer.h"
#include "Gray.h"
#include "motorDK.h"
#include "Encoder.h"
#include "Gray.h"
#include "Tracking.h"
#include "time.h"  
#include "OLED.h"
#include "Buzzer.h"
#include "chassis.h"
#include <string.h>

typedef struct {
    // 任务管理参数
    uint8_t current_task;           // 当前任务号 (1-6)
    uint8_t circle_count;           // 圈数 (1-6圈)
    uint8_t speed_level;            // 速度档位 (1-3档)
    uint8_t task_running;           // 任务运行状态
    
    // 任务统计数据
    uint16_t completed_circles;     // 已完成圈数
    uint8_t corner_cnt;             // 角落计数
    
    // 任务状态标志
    uint8_t corner_flag;            // 0: 未检测到角落, 1: 检测到角落
    uint8_t tracking_flag;          // 0: 未开始跟踪, 1: 开始跟踪
    uint8_t forward_flag;           // 直行标志位
    
    // 速度配置表
    uint16_t speed_table[3];        // 速度档位对应的PWM值
} Task_t;

// 外部变量声明
extern volatile Task_t task;

// 函数声明
void Task_Init(void);           // 任务系统初始化
void Task_Choose(void);         // 任务选择和参数设置
void Task1(void);              // 任务1实现
void Task2(void);              // 任务2实现
void Task3(void);              // 任务3实现
void Task4(void);              // 任务4实现
void Task5(void);              // 任务5实现
void Task6(void);              // 任务6实现

// 状态查询函数
uint8_t Task_GetCurrentTask(void);   // 获取当前任务号
uint8_t Task_GetCircleCount(void);   // 获取当前圈数设置
uint8_t Task_GetSpeedLevel(void);    // 获取当前速度档位
bool Task_IsRunning(void);           // 获取任务运行状态

#endif // __TASK_H__