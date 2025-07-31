#include "Gray.h"
#include "time.h"
//uint8_t Infr_data[16];
uint8_t Gray_data[16];
void Gray_Read(void)
{
        if(DL_GPIO_readPins(GPIO_Gray_PIN_1_PORT,GPIO_Gray_PIN_1_PIN))
        {
            Gray_data[0] = 1;
        }
        else
        {
            Gray_data[0] = 0;
        }
        if(DL_GPIO_readPins(GPIO_Gray_PIN_2_PORT,GPIO_Gray_PIN_2_PIN))
        {
            Gray_data[1] = 1;
        }
        else
        {
            Gray_data[1] = 0;
        }
        if(DL_GPIO_readPins(GPIO_Gray_PIN_3_PORT,GPIO_Gray_PIN_3_PIN))
        {
            Gray_data[2] = 1;
        }
        else
        {
            Gray_data[2] = 0;
        }
        if(DL_GPIO_readPins(GPIO_Gray_PIN_4_PORT,GPIO_Gray_PIN_4_PIN))
        {
            Gray_data[3] = 1;
        }
        else
        {
            Gray_data[3] = 0;
        }
        if(DL_GPIO_readPins(GPIO_Gray_PIN_5_PORT,GPIO_Gray_PIN_5_PIN))
        {
            Gray_data[4] = 1;
        }
        else
        {
            Gray_data[4] = 0;
        }
        if(DL_GPIO_readPins(GPIO_Gray_PIN_6_PORT,GPIO_Gray_PIN_6_PIN))
        {
            Gray_data[5] = 1;
        }
        else
        {
            Gray_data[5] = 0;
        }
        if(DL_GPIO_readPins(GPIO_Gray_PIN_7_PORT,GPIO_Gray_PIN_7_PIN))
        {
            Gray_data[6] = 1;
        }
        else
        {
            Gray_data[6] = 0;
        }
        if(DL_GPIO_readPins(GPIO_Gray_PIN_8_PORT,GPIO_Gray_PIN_8_PIN))
        {
            Gray_data[7] = 1;
        }
        else
        {
            Gray_data[7] = 0;
        }
        if(DL_GPIO_readPins(GPIO_Gray_PIN_9_PORT,GPIO_Gray_PIN_9_PIN))
        {
            Gray_data[8] = 1;
        }
        else
        {
            Gray_data[8] = 0;
        }
        if(DL_GPIO_readPins(GPIO_Gray_PIN_10_PORT,GPIO_Gray_PIN_10_PIN))
        {
            Gray_data[9] = 1;
        }
        else
        {
            Gray_data[9] = 0;
        }
        if(DL_GPIO_readPins(GPIO_Gray_PIN_11_PORT,GPIO_Gray_PIN_11_PIN))
        {
            Gray_data[10] = 1;
        }
        else
        {
            Gray_data[10] = 0;
        }
        if(DL_GPIO_readPins(GPIO_Gray_PIN_12_PORT,GPIO_Gray_PIN_12_PIN))
        {
            Gray_data[11] = 1;
        }
        else
        {
            Gray_data[11] = 0;
        }
        if(DL_GPIO_readPins(GPIO_Gray_PIN_13_PORT,GPIO_Gray_PIN_13_PIN))
        {
            Gray_data[12] = 1;
        }
        else
        {
            Gray_data[12] = 0;
        }
        if(DL_GPIO_readPins(GPIO_Gray_PIN_14_PORT,GPIO_Gray_PIN_14_PIN))
        {
            Gray_data[13] = 1;
        }
        else
        {
            Gray_data[13] = 0;
        }
        if(DL_GPIO_readPins(GPIO_Gray_PIN_15_PORT,GPIO_Gray_PIN_15_PIN))
        {
            Gray_data[14] = 1;
        }
        else
        {
            Gray_data[14] = 0;
        }
		if(DL_GPIO_readPins(GPIO_Gray_PIN_16_PORT,GPIO_Gray_PIN_16_PIN))
        {
            Gray_data[15] = 1;
        }
        else
        {
            Gray_data[15] = 0;
        }
}

double Gray_CalError(void)
{
	double Gray_Error=0;
	Gray_Error = (Gray_data[0]-Gray_data[15])*P_Error1 +
                 (Gray_data[1]-Gray_data[14])*P_Error2 +
                 (Gray_data[2]-Gray_data[13])*P_Error3 +
                 (Gray_data[3]-Gray_data[12])*P_Error4 +
                 (Gray_data[4]-Gray_data[11])*P_Error5 +
                 (Gray_data[5]-Gray_data[10])*P_Error6 +
                 (Gray_data[6]-Gray_data[9])*P_Error7 ;
//				+(Gray_data[7]-Gray_data[8])*P_Error8;
    return Gray_Error;
}

/**
 * @brief  检测起始线（全黑线）
 * @param  无
 * @retval true: 检测到起始线, false: 未检测到
 * @note   当大部分传感器都检测到黑线时，认为是起始线
 */
bool Gray_DetectStartLine(void)
{
    uint8_t black_count = 0;
    
    // 统计检测到黑线的传感器数量
    for (int i = 0; i < 16; i++) {
        if (Gray_data[i] == 0) {  // 假设0表示检测到黑线
            black_count++;
        }
    }
    
    // 如果超过12个传感器检测到黑线，认为是起始线
    // 这个阈值可以根据实际情况调整
    if (black_count >= 12) {
        return true;
    }
    
    return false;
}
