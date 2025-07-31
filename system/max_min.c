#include "max_min.h"

int16_t Get_Max(int16_t a, int16_t b)
{
    return (a > b) ? a : b;
}

int16_t Get_Min(int16_t a, int16_t b)
{
    return (a < b) ? a : b;
}

uint16_t Limit_Max(uint16_t value, uint16_t max_value)
{
    return (value > max_value) ? max_value : value;
}

uint16_t Limit_Min(uint16_t value, uint16_t min_value)
{
    return (value < min_value) ? min_value : value;
}
int16_t Limit_Range(int16_t value, int16_t min_value, int16_t max_value)
{
    if (value < min_value) {
        return min_value;
    } else if (value > max_value) {
        return max_value;
    } else {
        return value;
    }
}