/**
 * OLED硬件I2C使用示例
 * 这个文件展示了如何在main函数中使用硬件I2C版本的OLED驱动
 */

#include "ti_msp_dl_config.h"
#include "OLED/oled_hw_i2c.h"
#include "gimbal/gimbal.h"
#include "vision/vision.h"

void oled_test_example(void)
{
    // 初始化OLED（使用硬件I2C）
    OLED_Init();
    
    // 清屏
    OLED_Clear();
    
    // 显示字符串
    OLED_ShowString(0, 0, (uint8_t*)"Gimbal System", 16);
    OLED_ShowString(0, 2, (uint8_t*)"Hardware I2C", 16);
    
    // 显示数字
    OLED_ShowString(0, 4, (uint8_t*)"X:", 16);
    OLED_ShowNum(24, 4, 123, 3, 16);
    
    OLED_ShowString(0, 6, (uint8_t*)"Y:", 16);
    OLED_ShowNum(24, 6, 456, 3, 16);
}

// 在主循环中使用OLED显示云台状态的示例
void oled_display_gimbal_status(void)
{
    vision_data_t vision_data;
    GimbalPosition pos;
    
    // 获取视觉数据
    if (vision_get_received_data(&vision_data)) {
        // 显示视觉偏移量
        OLED_ShowString(0, 0, (uint8_t*)"Vision Data:", 16);
        
        // 显示X偏移
        OLED_ShowString(0, 2, (uint8_t*)"X:", 16);
        if (vision_data.x_offset >= 0) {
            OLED_ShowChar(24, 2, '+', 16);
            OLED_ShowNum(40, 2, vision_data.x_offset, 3, 16);
        } else {
            OLED_ShowChar(24, 2, '-', 16);
            OLED_ShowNum(40, 2, -vision_data.x_offset, 3, 16);
        }
        
        // 显示Y偏移
        OLED_ShowString(0, 4, (uint8_t*)"Y:", 16);
        if (vision_data.y_offset >= 0) {
            OLED_ShowChar(24, 4, '+', 16);
            OLED_ShowNum(40, 4, vision_data.y_offset, 3, 16);
        } else {
            OLED_ShowChar(24, 4, '-', 16);
            OLED_ShowNum(40, 4, -vision_data.y_offset, 3, 16);
        }
    }
    
    // 获取云台位置
    pos = gimbal_get_position();
    
    // 显示云台位置
    OLED_ShowString(0, 6, (uint8_t*)"Gimbal Pos:", 16);
    
    // 显示俯仰角度（第7行，使用8x16字体）
    OLED_ShowString(0, 7, (uint8_t*)"P:", 8);
    OLED_ShowNum(16, 7, (uint32_t)pos.pitch, 3, 8);
    
    // 显示偏航角度
    OLED_ShowString(64, 7, (uint8_t*)"Y:", 8);
    OLED_ShowNum(80, 7, (uint32_t)pos.yaw, 3, 8);
}

/**
 * 使用说明：
 * 
 * 1. 在ti_msp_dl_config.h中需要配置I2C_OLED相关的引脚和实例定义
 * 2. 在ti_msp_dl_config.c中需要实现SYSCFG_DL_I2C_OLED_init()函数
 * 3. 确保oledfont.h文件包含了字体数据数组
 * 
 * 主要优势：
 * - 使用硬件I2C，速度更快，CPU占用更少
 * - 支持I2C总线错误检测和恢复
 * - 更稳定的通信
 * 
 * 函数说明：
 * - OLED_Init(): 初始化OLED显示器
 * - OLED_Clear(): 清屏
 * - OLED_ShowString(): 显示字符串
 * - OLED_ShowNum(): 显示数字
 * - OLED_ShowChar(): 显示单个字符
 * - OLED_ShowChinese(): 显示汉字（需要字库支持）
 */
