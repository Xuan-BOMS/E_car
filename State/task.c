#include "task.h"

// 全局变量
static uint8_t current_task = 1;        // 当前任务号 (1-6)
static uint8_t circle_count_target = 1;        // 圈数 (1-6圈)
static uint8_t speed_level = 1;         // 速度档位 (1-3档)
volatile bool task_running = false;       // 任务运行状态

static uint16_t completed_circles = 0;
static uint8_t corner_cnt = 0;

uint8_t corner_flag = 0; // 0: 未检测到角落, 1: 检测到角落
uint8_t tracking_flag =0;// 0: 未开始跟踪, 1: 开始跟踪
uint8_t foward_flag = 0; //直行标志位
// 速度档位对应的PWM值
static const uint16_t speed_table[3] = {
    1500,  // 1档：低速
    2000,  // 2档：中速
    2500   // 3档：高速
};

//外部变量
extern double Tracking_Error;
extern int16_t Motor_Speed[2];

// 任务1的具体实现 - 基础循迹行驶
void Task1(void)
{
    // 计时用变量
    static uint8_t corner_count = 0;
    static bool task_initialized = false;
    static uint32_t line_time = 0;
    static uint32_t first_line_time = 0;
    static bool first_line_time_initialized = false;
    
    // 任务启动时初始化
    if(!task_initialized && task_running) {
        corner_count = 4 * circle_count_target;
        corner_cnt = 0;
        task_initialized = true;
    }

    // 任务停止时重置初始化标志
    if(!task_running) {
        task_initialized = false;
        return;
    }

    tracking_flag =1; // 设置为已开始跟踪

    if(Tracking_Error>=(P_Error1+P_Error2+P_Error3+P_Error4+P_Error5+P_Error6))//到达拐角
    {
        first_line_time_initialized = true;
        corner_flag = 1; // 检测到角落
        tracking_flag =0; // 停止跟踪
        corner_cnt++;
        
//        // 实时显示当前进度 (已完成的角数和圈数)
//        OLED_Set_Printfmt(0, 48, 16, 0);
//        OLED_Printf("Progress:%d/%d", corner_cnt/4, circle_count_target);
    }

    if(corner_flag ==1){
		
		Motor_MoveForward(1000);//直行
		Delay_ms(150); // 等待转向完成
        Motor_Spin_Left(850); // 左转
        Buzzer_on(1);
        Delay_ms(200); // 等待转向完成
        corner_flag = 0; // 重置角落标志
        tracking_flag = 1; // 开始跟踪
        corner_count--;
        if(corner_count == 0) {
            corner_cnt = 0; // 重置角落计数
            while(first_line_time <line_time){
            Tracking_Update();
            Delay_ms(10);
            first_line_time++; // 延时10ms，模拟任务间隔
            }
            task_running = false; // 任务完成，停止任务
            first_line_time_initialized = false;
            first_line_time = 0; // 重置第一次跟踪时间
            Motor_Stop_All(); // 停止电机
            return; // 任务完成，退出
        }else {
            line_time= 0; // 重置计时
        }
    }

    if(tracking_flag == 1) {
        // 如果正在跟踪
        Tracking_Update();
        if(first_line_time_initialized == false) {
            first_line_time++; // 记录第一次跟踪的时间
        }
        Delay_ms(10); // 延时10ms，模拟任务间隔
    }

//     // 检查是否达到目标圈数 (每圈4个角)
//     if(corner_cnt >= circle_count_target * 4) {
//         // 到达目标圈数，停止任务
//         task_running = false;
//         Motor_Stop_All();
        
//         // 重置相关变量
//         corner_cnt = 0;
//         corner_flag = 0;
//         tracking_flag = 0;
//         completed_circles = circle_count_target;
        
//         // 蜂鸣器提示任务完成
//         Buzzer_on(2);
        
// //        // 显示任务完成信息
// //        OLED_Set_Printfmt(80, 0, 16, 0);
// //        OLED_Printf("     ");
// //        OLED_Set_Printfmt(80, 0, 16, 0);
// //        OLED_Printf("Done!");
        
//         // 显示完成的圈数
//         OLED_Set_Printfmt(0, 48, 16, 0);
//         OLED_Printf("Finished:%d", completed_circles);
        
//         return; // 退出任务函数
//     }
    completed_circles = corner_cnt / 4; // 更新已完成的圈数
}

// 初始化任务
void Task_Init(void)
{
    // 初始化按键系统
    Key_Init();
    
    // 初始化电机
    Motor_Init();
    Motor_Enable();
    
    // 其他初始化
	TIMER_Init();
	Buzzer_on(3);
	encoder_init();
	Tracking_PID_Init();
	//OLED初始化
    OLED_Init(); 
    OLED_Set_Printfmt(0,0,16,0);

    // 初始化变量
    current_task = 1;
    circle_count_target = 1;
    speed_level = 1;
    task_running = false;
    
    // 重置任务相关变量
    corner_cnt = 0;
    corner_flag = 0;
    tracking_flag = 0;
    completed_circles = 0;

	OLED_Set_Printfmt(80, 0, 16, 0);
    OLED_Printf("ready");
	// 显示当前任务
	OLED_Set_Printfmt(0, 0, 16, 0);
	OLED_Printf("Task:%d", current_task);
	// 显示圈数
	OLED_Set_Printfmt(0, 16 , 16, 0);
	OLED_Printf("Circles:%d", circle_count_target);
	// 显示速度档位
	OLED_Set_Printfmt(0, 32, 16, 0);
	OLED_Printf("Speed:%d", speed_level);
	// 清除进度显示区域
	OLED_Set_Printfmt(0, 48, 16, 0);
	OLED_Printf("         ");
}

// 选择任务
void Task_Choose(void)
{
    // KEY_1: 任务选择 (1->2->3->4->5->6->1...)
    if (Key_IsClicked(KEY_1)) {
        if (!task_running) {  // 只有在任务未运行时才能切换
            current_task++;
            if (current_task > 6) {
                current_task = 1;
            }
            // 显示当前任务
            OLED_Set_Printfmt(0, 0, 16, 0);
            OLED_Printf("Task:%d", current_task);
        }
    }
    // 根据任务类型处理KEY_2和KEY_3
    if (current_task == 1) {
        // KEY_2: 圈数控制 (1->2->3->...->5->1)
        if ((Key_IsClicked(KEY_2))&&(current_task == 1)) {
            if (!task_running) {
                circle_count_target++;
                if (circle_count_target > 5) {
                    circle_count_target = 1;
                }
                // 显示圈数
                OLED_Set_Printfmt(0, 16 , 16, 0);
                OLED_Printf("Circles:%d", circle_count_target);
            }
        }
    }
    if (current_task == 1 || current_task == 4 || current_task == 5 || current_task == 6) {
        // KEY_3: 速度档位控制 (1->2->3->1)
        if (Key_IsClicked(KEY_3)) {
            if (!task_running) {
                speed_level++;
                if (speed_level > 3) {
                    speed_level = 1;
                }
                // 显示速度档位
                OLED_Set_Printfmt(0, 32, 16, 0);
                OLED_Printf("Speed:%d", speed_level);
            }
        }
    }
    // KEY_4单击：启动/停止当前任务
    if (Key_IsClicked(KEY_4)) {
        // if (task_running) {
        //     // 停止任务
        //     task_running = false;
        //     Motor_Stop_All();
            
        //     // 重置任务相关变量
        //     corner_cnt = 0;
        //     corner_flag = 0;
        //     tracking_flag = 0;
        //     completed_circles = 0;
            
        //     // 清除进度显示
        //     OLED_Set_Printfmt(0, 48, 16, 0);
        //     OLED_Printf("         ");
            
            // Buzzer_Beep(200); // 长响表示停止
        // } else {
            // 启动任务前重置相关变量
            corner_cnt = 0;
            corner_flag = 0;
            tracking_flag = 0;
            completed_circles = 0;
            
            // 启动任务
            task_running = true;
			OLED_Set_Printfmt(80, 0, 16, 0);
			OLED_Printf("     ");
			OLED_Set_Printfmt(108, 0, 16, 0);
			OLED_Printf("ok");
			
			// 清除之前的完成信息
			OLED_Set_Printfmt(0, 48, 16, 0);
			OLED_Printf("         ");

        // }
    }
    
    // // KEY_4长按：紧急停止并复位所有参数
    // if (Key_IsHold(KEY_4)) {
    //     // 紧急停止
    //     task_running = false;
    //     Motor_Stop_All();
    //     Motor_Disable();
        
    //     // 复位参数到默认值
    //     current_task = 1;
    //     circle_count_target = 1;
    //     speed_level = 1;
        
    //     // 重置任务相关变量
    //     corner_cnt = 0;
    //     corner_flag = 0;
    //     tracking_flag = 0;
    //     completed_circles = 0;
        
    //     // 蜂鸣器报警提示
    //     Buzzer_Beep(300); // 超长响表示紧急停止
        
    //     // 显示复位信息
    //     // OLED_Clear();
    //     // OLED_ShowString(0, 0, "EMERGENCY STOP!");
    //     // OLED_ShowString(0, 16, "Parameters Reset");
    // }
    
    // 四键组合：系统完全复位
    if (Key_IsPressed(KEY_1) && Key_IsPressed(KEY_2) && 
        Key_IsPressed(KEY_3) && Key_IsPressed(KEY_4)) {
			
        // 完全停止系统
        task_running = false;
        Motor_Stop_All();
        Motor_Disable();
        
		// 任务系统初始化
		Task_Init();
        // 复位到出厂设置
        current_task = 1;
        circle_count_target = 1;
        speed_level = 1;
        
        // 重置任务相关变量
        corner_cnt = 0;
        corner_flag = 0;
        tracking_flag = 0;
        completed_circles = 0;

        SYSCFG_DL_init();
    
    
	
    // 全局中断使能
    __enable_irq();
        // OLED_Set_Printfmt(80, 0, 16, 0);
        // OLED_Printf("     ");
        // OLED_Set_Printfmt(80, 0, 16, 0);
        // OLED_Printf("ready");
        // // 显示当前任务
        // OLED_Set_Printfmt(0, 0, 16, 0);
        // OLED_Printf("Task:%d", current_task);
        // // 显示圈数
        // OLED_Set_Printfmt(0, 16 , 16, 0);
        // OLED_Printf("Circles:%d", circle_count_target);
        // // 显示速度档位
        // OLED_Set_Printfmt(0, 32, 16, 0);
        // OLED_Printf("Speed:%d", speed_level);
        
        // 蜂鸣器报警提示
        Buzzer_Beep(2000); // 超长响表示紧急停止

        // 系统复位标志
        // SystemReset();
    }
    
    // 执行当前任务
    if (task_running) {
        switch (current_task) {
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
    return current_task;
}

// 获取当前圈数设置
uint8_t Task_GetCircleCount(void)
{
    return circle_count_target;
}

// 获取当前速度档位
uint8_t Task_GetSpeedLevel(void)
{
    return speed_level;
}

// 获取任务运行状态
bool Task_IsRunning(void)
{
    return task_running;
}
