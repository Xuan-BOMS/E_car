/**
 * HWT101陀螺仪模块使用示例
 * 
 * 数据包格式：
 * 0x55 0x53 0x00 0x00 0x00 0x00 YawL YawH VL VH SUM
 * 
 * 字节说明：
 * 0-1: 帧头 0x55 0x53
 * 2-5: 保留字节（0x00）
 * 6: YawL - 偏航角低8位
 * 7: YawH - 偏航角高8位  
 * 8: VL - 版本号低8位
 * 9: VH - 版本号高8位
 * 10: SUM - 校验和
 * 
 * 角度计算公式：YAW = ((YawH<<8)|YawL)/32768*180°
 */

#include "HWT101/hwt101.h"

void hwt101_example_usage(void)
{
    // 初始化HWT101模块
    HWT101_Init();
    
    // 在主循环中使用
    while(1)
    {
        // 获取角度数据
        HWT101_Data_t hwt_data = HWT101_Get_Data();
        
        if(hwt_data.type_mode == 1) // 数据有效
        {
            // 使用角度数据
            float current_yaw = hwt_data.YAW;
            
            // 显示角度（如果有OLED或串口）
            // printf("YAW: %.2f degrees\n", current_yaw);
            
            // 或者获取指针直接访问
            HWT101_Data_t* hwt_ptr = HWT101_Get_Data_Pointer();
            if(hwt_ptr->type_mode == 1)
            {
                // 直接使用指针访问数据
                float yaw_angle = hwt_ptr->YAW;
            }
        }
        
        // 延时
        delay_ms(10);
    }
}

/**
 * 数据包解析流程：
 * 1. 串口中断接收字节
 * 2. HWT101_Angle_Get()状态机处理
 * 3. 检测帧头 0x55 0x53
 * 4. 接收完整11字节数据包
 * 5. 校验和验证
 * 6. 提取YAW数据并计算角度
 * 7. 更新hwt101_data结构体
 * 
 * 使用注意事项：
 * - 确保UART2波特率设置正确（通常9600或115200）
 * - 串口中断已正确配置
 * - HWT101模块电源和通信正常
 * - 校验和验证失败时数据被丢弃
 */
