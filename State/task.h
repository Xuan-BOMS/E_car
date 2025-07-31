#include "../ti_msp_dl_config.h"
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