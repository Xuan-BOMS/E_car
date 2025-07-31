#include "ti_msp_dl_config.h"

#define PWM1_SetDuty(Duty) DL_TimerG_setCaptureCompareValue(PWM_1_2_INST,Duty,GPIO_PWM_1_2_C0_IDX)
#define PWM2_SetDuty(Duty) DL_TimerG_setCaptureCompareValue(PWM_1_2_INST,Duty,GPIO_PWM_1_2_C1_IDX)
#define PWM3_SetDuty(Duty) DL_TimerA_setCaptureCompareValue(PWM_3_4_INST,Duty,GPIO_PWM_3_4_C0_IDX)
#define PWM4_SetDuty(Duty) DL_TimerA_setCaptureCompareValue(PWM_3_4_INST,Duty,GPIO_PWM_3_4_C1_IDX)