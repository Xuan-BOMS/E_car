#include "task.h"

// 任务管理结构体实例
volatile Task_t task;

//外部变量
extern double Tracking_Error;
extern int16_t Motor_Speed[2];
// 初始化任务
void Task_Init(void)
{
    // 先进行其他硬件初始化
    Key_Init();
    motor_init();
    TIMER_Init();
    Buzzer_on(3);
    encoder_init();
    Tracking_PID_Init();
    OLED_Init(); 
    OLED_Set_Printfmt(0,0,16,0);
    OLED_DrawBMP_logo(32, 0);
    delay_ms(500);
    
    // 使用memset清零整个结构体
    memset((void*)&task, 0, sizeof(Task_t));
    
    // 然后逐个赋值
    task.current_task = 1;
    task.circle_count = 1;
    task.speed_level = 1;
    task.task_running = 0;
    task.completed_circles = 0;
    task.corner_cnt = 0;
    task.corner_flag = 0;
    task.tracking_flag = 0;
    task.forward_flag = 0;
    
    // 初始化速度配置表
    task.speed_table[0] = 1500;
    task.speed_table[1] = 2000;
    task.speed_table[2] = 2500;
    
    // 添加调试输出验证初始化
    delay_ms(100);  // 确保初始化完成
    
    // 显示初始化后的值
    OLED_Set_Printfmt(80, 0, 16, 0);
    OLED_Printf("stop");
    OLED_Set_Printfmt(0, 0, 16, 0);
    OLED_Printf("Task:");
    // 使用临时变量避免直接访问task结构体
    uint8_t temp_task = task.current_task;
    OLED_ShowChar(40, 0, '0' + temp_task, 16, 0);
    OLED_Set_Printfmt(0, 16 , 16, 0);
    OLED_Printf("Circle:");
    uint8_t temp_circle = task.circle_count;
    OLED_ShowChar(64, 16, '0' + temp_circle, 16, 0);
    OLED_Set_Printfmt(0, 32, 16, 0);
    OLED_Printf("Speed:");
    uint8_t temp_speed = task.speed_level;
    OLED_ShowChar(48, 32, '0' + temp_speed, 16, 0);
}
// 任务1的具体实现 - 基础循迹行驶
void Task1(void)
{
    task.tracking_flag = 1; // 设置为已开始跟踪
    if(Gray_DetectStartLine() == true)//到达拐角
    {
        task.corner_flag = 1; // 检测到角落
        task.tracking_flag = 0; // 停止跟踪
        task.corner_cnt++;
    }
    if(task.corner_flag == 1){
		
		Chassis_setSpeed(-Basic_Speed,Basic_Speed); 
        float last_yaw_angle = get_YAW_Angle();
        Chassis_setSpeed(Basic_Speed, Basic_Speed); // 停止电机
        delay_ms(500);
		delay_ms(5); // 等待转向完成
        while(1)
        {
            float angle_diff = get_YAW_Angle() - last_yaw_angle;
            // 处理跨界
            if (angle_diff > 180.0f) angle_diff -= 360.0f;
            if (angle_diff < -180.0f) angle_diff += 360.0f;
            // 判断是否达到90度
            if (fabs(angle_diff) >= 80.0f) break;
            delay_ms(1);
        }
        Chassis_setSpeed(Basic_Speed, Basic_Speed); // 停止电机
        delay_ms(1000);
        task.corner_flag = 0; // 重置角落标志
        task.tracking_flag = 1; // 开始跟踪
    }
    if(task.tracking_flag == 1) {
        // 如果正在跟踪
        Tracking_Update();
        delay_ms(10); // 延时10ms，模拟任务间隔
    }
	
}



// 选择任务
void Task_Choose(void)
{
    // KEY_1: 任务选择 (1->2->3->4->5->6->1...)
    if (Key_IsClicked(KEY_1)) {
        if (!task.task_running) {  // 只有在任务未运行时才能切换
            task.current_task++;
            if (task.current_task > 6) {
                task.current_task = 1;
            }
            // 显示当前任务
            OLED_Set_Printfmt(0, 0, 16, 0);
            OLED_Printf("Task:");
            uint8_t temp_task = task.current_task;
            OLED_ShowChar(40, 0, '0' + temp_task, 16, 0);
        }
    }
    // 根据任务类型处理KEY_2和KEY_3
    if (task.current_task == 1) {
        // KEY_2: 圈数控制 (1->2->3->...->5->1)
        if ((Key_IsClicked(KEY_2))&&(task.current_task == 1)) {
            if (!task.task_running) {
                task.circle_count++;
                if (task.circle_count > 5) {
                    task.circle_count = 1;
                }
                // 显示圈数
                OLED_Set_Printfmt(0, 16 , 16, 0);
                OLED_Printf("Circle:");
                uint8_t temp_circle_display = task.circle_count;
                OLED_ShowChar(64, 16, '0' + temp_circle_display, 16, 0);
            }
        }
    }
    if (task.current_task == 1 || task.current_task == 4 || task.current_task == 5 || task.current_task == 6) {
        // KEY_3: 速度档位控制 (1->2->3->1)
        if (Key_IsClicked(KEY_3)) {
            if (!task.task_running) {
                task.speed_level++;
                if (task.speed_level > 3) {
                    task.speed_level = 1;
                }
                // 显示速度档位
                OLED_Set_Printfmt(0, 32, 16, 0);
                OLED_Printf("Speed:");
                uint8_t temp_speed_display = task.speed_level;
                OLED_ShowChar(48, 32, '0' + temp_speed_display, 16, 0);
            }
        }
    }
    // KEY_4单击：启动/停止当前任务
    // 改进显示逻辑，确保清除旧内容
    if (Key_IsClicked(KEY_4)) {
        task.task_running = !task.task_running;
        
        // 先清除显示区域
        OLED_Set_Printfmt(80, 0, 16, 0);
        OLED_Printf("    ");  // 清除4个字符位置
        Chassis_setSpeed(0, 0);
        // 重新显示状态
        OLED_Set_Printfmt(80, 0, 16, 0);
        OLED_Printf(task.task_running ? "run" : "stop");
    }
    
    // KEY_4长按：紧急停止并复位所有参数
    if (Key_IsHold(KEY_4)) {
        // 紧急停止
        task.task_running = false;
        //Motor_Stop_All();
        //Motor_Disable();
        
        // 复位参数到默认值
        task.current_task = 1;
        task.circle_count = 1;
        task.speed_level = 1;
        
        // 蜂鸣器报警提示
        Buzzer_Beep(300); // 超长响表示紧急停止
        
        // 显示复位信息
        // OLED_Clear();
        // OLED_ShowString(0, 0, "EMERGENCY STOP!");
        // OLED_ShowString(0, 16, "Parameters Reset");
    }
    
    // 四键组合：系统完全复位
    if (Key_IsPressed(KEY_1) && Key_IsPressed(KEY_2) && 
        Key_IsPressed(KEY_3) && Key_IsPressed(KEY_4)) {
        // 完全停止系统
        task.task_running = false;
        //Motor_Stop_All();
        //Motor_Disable();
        
        // 复位到出厂设置
        task.current_task = 1;
        task.circle_count = 1;
        task.speed_level = 1;

        OLED_Init(); 
    OLED_Set_Printfmt(0,0,16,0);
    OLED_DrawBMP_logo(32, 0);
    delay_ms(500);
    
    // 使用memset清零整个结构体
    memset((void*)&task, 0, sizeof(Task_t));
    
    // 然后逐个赋值
    task.current_task = 1;
    task.circle_count = 1;
    task.speed_level = 1;
    task.task_running = 0;
    task.completed_circles = 0;
    task.corner_cnt = 0;
    task.corner_flag = 0;
    task.tracking_flag = 0;
    task.forward_flag = 0;
    
    // 初始化速度配置表
    task.speed_table[0] = 1500;
    task.speed_table[1] = 2000;
    task.speed_table[2] = 2500;
    OLED_Init(); 
    OLED_Set_Printfmt(0,0,16,0);
    // 添加调试输出验证初始化
    delay_ms(100);  // 确保初始化完成
        
    // 显示初始化后的值
    OLED_Set_Printfmt(80, 0, 16, 0);
    OLED_Printf("stop");
    OLED_Set_Printfmt(0, 0, 16, 0);
    OLED_Printf("Task:");
    // 使用临时变量避免直接访问task结构体
    uint8_t temp_task = task.current_task;
    OLED_ShowChar(40, 0, '0' + temp_task, 16, 0);
    OLED_Set_Printfmt(0, 16 , 16, 0);
    OLED_Printf("Circle:");
    uint8_t temp_circle = task.circle_count;
    OLED_ShowChar(64, 16, '0' + temp_circle, 16, 0);
    OLED_Set_Printfmt(0, 32, 16, 0);
    OLED_Printf("Speed:");
    uint8_t temp_speed = task.speed_level;
    OLED_ShowChar(48, 32, '0' + temp_speed, 16, 0);

        // 系统复位标志
        // SystemReset();
    }
    
    // 执行当前任务
    if (task.task_running) {
        switch (task.current_task) {
            case 1: Task1(); break;
            case 2: Task2(); break;
            case 3: Task3(); break;
            case 4: Task4(); break;
            case 5: Task5(); break;
            case 6: Task6(); break;
        }
    }
}



// 任务2的具体实现 - 特殊任务2
void Task2(void)
{

}

// 任务3的具体实现 - 特殊任务3  
void Task3(void)
{

}
// 任务4的具体实现 - 循迹任务4
void Task4(void)
{

}

// 任务5的具体实现 - 循迹任务5
void Task5(void)
{

}

// 任务6的具体实现 - 循迹任务6
void Task6(void)
{
 
}

// 获取当前任务号
uint8_t Task_GetCurrentTask(void)
{
    return task.current_task;
}

// 获取当前圈数设置
uint8_t Task_GetCircleCount(void)
{
    return task.circle_count;
}

// 获取当前速度档位
uint8_t Task_GetSpeedLevel(void)
{
    return task.speed_level;
}

// 获取任务运行状态
bool Task_IsRunning(void)
{
    return task.task_running;
}
