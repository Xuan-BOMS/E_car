#include "PID.h"



/************************************************
功能：初始化PID各参数
参数：pid = 对应pid的结构体地址
      p = pid的静态kp值
      i = pid的静态ki值
      d = pid的静态kd值
      maxI = pid计算后的I最大值，即最大误差累加值
      maxOut = PID最大输出值
      target = 目标值
************************************************/
void pid_init(PID* pid, double p, double i, double d, double maxI, double maxOut, int target)
{
    pid->kp = p;
    pid->ki = i;
    pid->kd = d;
    pid->max_change_i = maxI;
    pid->max_output = maxOut;
    pid->target = target;
}

/****************************************************
功能：PID计算
参数：pid = pid的参数输入
     target = 目标值
     current = 当前值
返回：PID计算后的结果
****************************************************/
double pid_calc(PID *pid, double target, double current)
{
    //用上一次的误差值更新 之前误差last_error
    pid->last_error = pid->error;
    pid->target = target;
    //获取新的误差 = 目标值 - 当前值
    pid->error = pid->target - current;

    //计算比例P = 目标值与实际值之间的误差e
    double pout = pid->error;
    //计算积分I = 误差e的累加
    pid->change_i += pid->error;
    //计算微分D = 当前误差e - 之前的误差last_e
    double dout = pid->error - pid->last_error;

    //积分I 限制不能超过正负最大值
    if(pid->change_i > pid->max_change_i)
    {
      pid->change_i = pid->max_change_i;
    }
    else if(pid->change_i < -pid->max_change_i)
    {
      pid->change_i = -pid->max_change_i;
    }

    //计算输出PID_OUT = （Kp x P）+ （Ki x I）+（Kd x D）
    pid->output = (pid->kp * pout) + (pid->ki * pid->change_i) + (pid->kd * dout);

    //输出 限制不能超过正负最大值
    if(pid->output > pid->max_output) pid->output = pid->max_output;
    else if(pid->output < -pid->max_output) pid->output = -pid->max_output;

    //返回PID计算的结果
    return pid->output;
}
