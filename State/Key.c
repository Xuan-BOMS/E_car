#include "Key.h"

// 按键状态数组
Key_t keys[KEY_COUNT];

/**
 * @brief  读取按键硬件状态
 * @param  key: 按键索引
 * @retval true=按下, false=释放
 */
static bool Key_ReadHardware(KeyIndex_t key)
{
    switch (key) {
        case KEY_1:
            return !DL_GPIO_readPins(GPIO_KEY_KEY1_PORT, GPIO_KEY_KEY1_PIN);
        case KEY_2:
            return !DL_GPIO_readPins(GPIO_KEY_KEY2_PORT, GPIO_KEY_KEY2_PIN);
        case KEY_3:
            return !DL_GPIO_readPins(GPIO_KEY_KEY3_PORT, GPIO_KEY_KEY3_PIN);
        case KEY_4:
            return !DL_GPIO_readPins(GPIO_KEY_KEY4_PORT, GPIO_KEY_KEY4_PIN);
        default:
            return false;
    }
}

/**
 * @brief  按键初始化
 * @param  无
 * @retval 无
 */
void Key_Init(void)
{
    // 初始化所有按键状态
    for (int i = 0; i < KEY_COUNT; i++) {
        keys[i].state = KEY_STATE_IDLE;
        keys[i].event = KEY_EVENT_NONE;
        keys[i].debounce_count = 0;
        keys[i].hold_count = 0;
        keys[i].is_pressed = false;
        keys[i].last_state = false;
    }
}

/**
 * @brief  按键扫描(非阻塞式)
 * @param  无
 * @retval 无
 * @note   需要在定时器中断中调用，扫描周期为KEY_SCAN_PERIOD(10ms)
 */
void Key_Scan(void)
{
    for (KeyIndex_t i = 0; i < KEY_COUNT; i++) {
        bool current_state = Key_ReadHardware(i);
        
        switch (keys[i].state) {
            case KEY_STATE_IDLE:
                if (current_state) {
                    keys[i].state = KEY_STATE_PRESSED;
                    keys[i].debounce_count = 0;
                }
                break;
                
            case KEY_STATE_PRESSED:
                if (current_state) {
                    keys[i].debounce_count++;
                    if (keys[i].debounce_count >= KEY_DEBOUNCE_COUNT) {
                        keys[i].state = KEY_STATE_CONFIRMED;
                        keys[i].is_pressed = true;
                        keys[i].hold_count = 0;
                        keys[i].event = KEY_EVENT_CLICK;
                    }
                } else {
                    keys[i].state = KEY_STATE_IDLE;
                    keys[i].debounce_count = 0;
                }
                break;
                
            case KEY_STATE_CONFIRMED:
                if (current_state) {
                    keys[i].hold_count++;
                    if (keys[i].hold_count >= KEY_HOLD_COUNT) {
                        keys[i].state = KEY_STATE_HOLD;
                        keys[i].event = KEY_EVENT_HOLD;
                    }
                } else {
                    keys[i].state = KEY_STATE_RELEASED;
                    keys[i].debounce_count = 0;
                }
                break;
                
            case KEY_STATE_HOLD:
                if (!current_state) {
                    keys[i].state = KEY_STATE_RELEASED;
                    keys[i].debounce_count = 0;
                }
                break;
                
            case KEY_STATE_RELEASED:
                if (!current_state) {
                    keys[i].debounce_count++;
                    if (keys[i].debounce_count >= KEY_DEBOUNCE_COUNT) {
                        keys[i].state = KEY_STATE_IDLE;
                        keys[i].is_pressed = false;
                        keys[i].event = KEY_EVENT_RELEASE;
                        keys[i].debounce_count = 0;
                        keys[i].hold_count = 0;
                    }
                } else {
                    keys[i].state = KEY_STATE_CONFIRMED;
                    keys[i].debounce_count = 0;
                }
                break;
        }
        
        keys[i].last_state = current_state;
    }
}

/**
 * @brief  检测按键单击事件
 * @param  key: 按键索引
 * @retval true=有单击事件, false=无单击事件
 */
bool Key_IsClicked(KeyIndex_t key)
{
    if (key >= KEY_COUNT) return false;
    
    if (keys[key].event == KEY_EVENT_CLICK) {
        keys[key].event = KEY_EVENT_NONE;  // 读取后清除事件
        return true;
    }
    return false;
}

/**
 * @brief  检测按键长按事件
 * @param  key: 按键索引
 * @retval true=有长按事件, false=无长按事件
 */
bool Key_IsHold(KeyIndex_t key)
{
    if (key >= KEY_COUNT) return false;
    
    if (keys[key].event == KEY_EVENT_HOLD) {
        keys[key].event = KEY_EVENT_NONE;  // 读取后清除事件
        return true;
    }
    return false;
}

/**
 * @brief  检测按键释放事件
 * @param  key: 按键索引
 * @retval true=有释放事件, false=无释放事件
 */
bool Key_IsReleased(KeyIndex_t key)
{
    if (key >= KEY_COUNT) return false;
    
    if (keys[key].event == KEY_EVENT_RELEASE) {
        keys[key].event = KEY_EVENT_NONE;  // 读取后清除事件
        return true;
    }
    return false;
}

/**
 * @brief  检测按键是否按下(实时状态)
 * @param  key: 按键索引
 * @retval true=按下, false=未按下
 */
bool Key_IsPressed(KeyIndex_t key)
{
    if (key >= KEY_COUNT) return false;
    return keys[key].is_pressed;
}

/**
 * @brief  清除按键事件标志
 * @param  key: 按键索引
 * @retval 无
 */
void Key_ClearEvent(KeyIndex_t key)
{
    if (key >= KEY_COUNT) return;
    keys[key].event = KEY_EVENT_NONE;
}

/**
 * @brief  清除所有按键事件
 * @param  无
 * @retval 无
 */
void Key_ClearAllEvents(void)
{
    for (int i = 0; i < KEY_COUNT; i++) {
        keys[i].event = KEY_EVENT_NONE;
    }
}

/**
 * @brief  获取按键事件(不清除)
 * @param  key: 按键索引
 * @retval 按键事件
 */
KeyEvent_t Key_GetEvent(KeyIndex_t key)
{
    if (key >= KEY_COUNT) return KEY_EVENT_NONE;
    return keys[key].event;
}

