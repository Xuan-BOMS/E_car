#ifndef __KEY_H
#define __KEY_H

#include "../ti_msp_dl_config.h"
#include <stdbool.h>
#include <stdint.h>

// 按键状态枚举
typedef enum {
    KEY_STATE_IDLE = 0,     // 空闲状态
    KEY_STATE_PRESSED,      // 按下状态
    KEY_STATE_CONFIRMED,    // 确认按下状态
    KEY_STATE_HOLD,         // 长按状态
    KEY_STATE_RELEASED      // 释放状态
} KeyState_t;

// 按键事件枚举
typedef enum {
    KEY_EVENT_NONE = 0,     // 无事件
    KEY_EVENT_CLICK,        // 单击事件
    KEY_EVENT_HOLD,         // 长按事件
    KEY_EVENT_RELEASE       // 释放事件
} KeyEvent_t;

// 按键结构体
typedef struct {
    KeyState_t state;           // 当前状态
    KeyEvent_t event;           // 当前事件
    uint16_t debounce_count;    // 消抖计数器
    uint16_t hold_count;        // 长按计数器
    bool is_pressed;            // 按键是否按下
    bool last_state;            // 上次按键状态
} Key_t;

// 按键索引定义
typedef enum {
    KEY_1 = 0,
    KEY_2,
    KEY_3,
    KEY_4,
    KEY_COUNT
} KeyIndex_t;

// 配置参数
#define KEY_DEBOUNCE_TIME       20      // 消抖时间(ms)
#define KEY_HOLD_TIME           1000    // 长按时间(ms)
#define KEY_SCAN_PERIOD         10      // 扫描周期(ms)

// 计算计数器阈值
#define KEY_DEBOUNCE_COUNT      (KEY_DEBOUNCE_TIME / KEY_SCAN_PERIOD)
#define KEY_HOLD_COUNT          (KEY_HOLD_TIME / KEY_SCAN_PERIOD)

// 按键初始化
void Key_Init(void);

// 按键扫描(在定时器中调用)
void Key_Scan(void);

// 检测按键单击事件
bool Key_IsClicked(KeyIndex_t key);

// 检测按键长按事件
bool Key_IsHold(KeyIndex_t key);

// 检测按键释放事件
bool Key_IsReleased(KeyIndex_t key);

// 检测按键是否按下
bool Key_IsPressed(KeyIndex_t key);

// 清除按键事件标志
void Key_ClearEvent(KeyIndex_t key);

// 清除所有按键事件
void Key_ClearAllEvents(void);

// 获取按键事件
KeyEvent_t Key_GetEvent(KeyIndex_t key);

#endif /* __KEY_H */