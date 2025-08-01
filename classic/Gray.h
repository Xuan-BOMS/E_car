#include "../ti_msp_dl_config.h"

#define P_Error1 5.5
#define P_Error2 5.5
#define P_Error3 5.0
#define P_Error4 5.0
#define P_Error5 5.0
#define P_Error6 5.0
#define P_Error7 5.0
#define P_Error8 5.0

//#define SH_L() DL_GPIO_clearPins(GPIO_Gray_SH_PORT, GPIO_Gray_SH_PIN)
//#define SH_H() DL_GPIO_setPins(GPIO_Gray_SH_PORT, GPIO_Gray_SH_PIN)
//#define CL_L() DL_GPIO_clearPins(GPIO_Gray_CLK_PORT, GPIO_Gray_CLK_PIN)
//#define CL_H() DL_GPIO_setPins(GPIO_Gray_CLK_PORT, GPIO_Gray_CLK_PIN)
//#define DA() DL_GPIO_readPins(GPIO_Gray_DATA_PORT, GPIO_Gray_DATA_PIN)
	
void Gray_Read(void);
double Gray_CalError(void);
bool Gray_DetectStartLine(void);  // 起始线检测函数

//void Inrared_Get(void);
