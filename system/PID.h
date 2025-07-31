#include "ti_msp_dl_config.h"

typedef struct
{
  double kp, ki, kd; 						      // 三个静态系数
  double change_p, change_i, change_d;	          // 三个动态参数
  double error, last_error; 						  // 误差、之前误差
  double max_change_i; 							  // 积分限幅
  double output, max_output; 				      // 输出、输出限幅
  double target;                                     // 目标
}PID;
void pid_init(PID* pid, double p, double i, double d, double maxI, double maxOut, int target);
double pid_calc(PID *pid, double target, double current);

