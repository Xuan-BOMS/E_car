#include "Gray.h"
#include "time.h"
uint8_t Gray_data[5];
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
        
}

double Gray_CalError(void)
{
	double Gray_Error=0;
	Gray_Error = (Gray_data[0]-Gray_data[4])*P_Error1 +
                 (Gray_data[1]-Gray_data[3])*P_Error2;
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
    for (int i = 0; i < 5; i++) {
        if (Gray_data[i] == 1) {  // 假设0表示检测到黑线
            black_count++;
        }
    }
    
    // 如果超过12个传感器检测到黑线，认为是起始线
    // 这个阈值可以根据实际情况调整
    if (black_count >= 3) {
        return true;
    }
    
    return false;
}
