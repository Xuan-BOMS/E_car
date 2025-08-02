#ifndef __HWT101_H__
#define __HWT101_H__
#include "ti_msp_dl_config.h"
typedef struct
{
    uint8_t type_mode; // 数据有效标志，0=无效，1=有效
    float YAW; // 云台偏航角度（度）
} HWT101_Data_t;
void HWT101_Init(void);
void HWT101_Zero_Set(void);
void HWT101_Angle_Get(uint8_t data);
HWT101_Data_t* HWT101_Get_Data_Pointer(void);
#endif // !__HWT101_H
