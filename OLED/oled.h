/*********************************************************************
*@file:			OLED.h
*@brief:		OLED屏幕驱动头文件
*@author:		Pan Zhikang
*@date:			2022-10-26
*@note:			移植OLED模块请修改OLED.h中的配置信息以及
*				以及OLED.c中的OLED_Pin_Config函数
*********************************************************************/
#ifndef	__OLED_H__
#define	__OLED_H__

#include "../ti_msp_dl_config.h"
#include <stdint.h>
#include <stdio.h>
#include <stdarg.h>
#include <stdbool.h>

/*********************************************************************
*					前置宏定义和类型定义(需要修改)
*********************************************************************/
#define	OLED_USE_IIC				1
#define	OLED_USE_SPI				0

#define	Write_Data					1
#define	Write_Command				0

#define	OLED_PixelFill				1
#define	OLED_PixelClear				0

typedef struct
{
	union
	{
		uint32_t WORD;

		struct
		{
			uint32_t RAM_BUSY		:1;		//记录当前的GRAM占用写入状态，1表示当前被占用

			uint32_t fmt_mode		:1;		//格式化显示模式
			uint32_t fmt_sizey		:8;		//格式化字号
			uint32_t fmt_x			:8;		//格式化坐标x
			uint32_t fmt_y			:8;		//格式化坐标y

			uint32_t RESERVEED		:6;
		}BIT;
	}STA;
}OLED_STATUS_TYPE;

/*********************************************************************
*					 OLED驱动方式宏定义(移植需要修改)
*********************************************************************/
#define	OLED_Mode 					OLED_USE_IIC
//OLED_USE_IIC:		使用IIC通讯
//OLED_USE_SPI:		使用SPI通讯

/********************************************************************/
#if		OLED_Mode==OLED_USE_SPI		//7线SPI通讯
/*********************************************************************
*						使用SPI方式通讯
*********************************************************************/
#define	OLED_PIN_Periph				RCC_APB2Periph_GPIOB

#define	OLED_SCL_Port				GPIOB
#define	OLED_SCL_Pin				GPIO_Pin_8

#define	OLED_SDA_Port				GPIOB
#define	OLED_SDA_Pin				GPIO_Pin_9

#define	OLED_DC_Port				GPIOB
#define	OLED_DC_Pin					GPIO_Pin_12

#define	OLED_CS_Port				GPIOB
#define	OLED_CS_Pin					GPIO_Pin_13

#define	OLED_SCL_High()				GPIO_SetBits(OLED_SCL_Port,OLED_SCL_Pin)
#define	OLED_SCL_Low()				GPIO_ResetBits(OLED_SCL_Port,OLED_SCL_Pin)

#define	OLED_SDA_High()				GPIO_SetBits(OLED_SDA_Port,OLED_SDA_Pin)
#define	OLED_SDA_Low()				GPIO_ResetBits(OLED_SDA_Port,OLED_SDA_Pin)



#define	OLED_DC_High()				GPIO_SetBits(OLED_DC_Port,OLED_DC_Pin)
#define	OLED_DC_Low()				GPIO_ResetBits(OLED_DC_Port,OLED_DC_Pin)

#define	OLED_CS_High()				GPIO_SetBits(OLED_CS_Port,OLED_CS_Pin)
#define	OLED_CS_Low()				GPIO_ResetBits(OLED_CS_Port,OLED_CS_Pin)

/*注意：如果你用RES管脚，应该将RES管脚拉高*/
#define OLED_USE_RES				1

#if OLED_USE_RES == 1

#define	OLED_RES_Port				GPIOB
#define	OLED_RES_Pin				GPIO_Pin_7

#define	OLED_RES_High()				GPIO_SetBits(OLED_RES_Port,OLED_RES_Pin)
#define	OLED_RES_Low()				GPIO_ResetBits(OLED_RES_Port,OLED_RES_Pin)

#endif
/********************************************************************/
#elif   OLED_Mode==OLED_USE_IIC		//4线IIC通讯
/*********************************************************************
*						使用IIC方式通讯
*********************************************************************/
#define	OLED_SCL_Port				GPIO_OLED_PORT
#define	OLED_SCL_Pin				GPIO_OLED_SCL_PIN

#define	OLED_SDA_Port				GPIO_OLED_PORT
#define	OLED_SDA_Pin				GPIO_OLED_SDA_PIN

#define	OLED_SCL_High()				OLED_SCL_Port->DOUTSET31_0 = OLED_SCL_Pin
#define	OLED_SCL_Low()				OLED_SCL_Port->DOUTCLR31_0 = OLED_SCL_Pin

#define	OLED_SDA_High()				OLED_SDA_Port->DOUTSET31_0 = OLED_SDA_Pin
#define	OLED_SDA_Low()				OLED_SDA_Port->DOUTCLR31_0 = OLED_SDA_Pin

#endif

/*********************************************************************
*						 OLED屏幕分辨率定义
*********************************************************************/
#define Max_X_Pixel					127
#define Max_Y_Pixel					63

/*********************************************************************
*						OLED内部延时(移植配置)
*********************************************************************/
#define OLED_Delay();				__NOP();__NOP();__NOP();__NOP();__NOP();\
									__NOP();__NOP();__NOP();__NOP();__NOP();

/*********************************************************************
*						OLED打印缓冲区大小(移植配置)
*********************************************************************/
#define OLED_Printf_BufferSize		256

/*********************************************************************
*				旧版本OLED常用到的分段式打印数字、字符
*********************************************************************/
#define OLED_FUNC_COMPATIBLE		0

/*@line 141*/
#if OLED_FUNC_COMPATIBLE == 1

#define	OLED_Display_Normal 		1
#define	OLED_Display_Repudiation	0

#define	OLED_FONTSIZE_12X6			12
#define OLED_FONTSIZE_16X8			16
#define OLED_FONTSIZE_24X12			24

#define	OLED_Default_FONT			OLED_FONTSIZE_12X6
#define	OLED_Default_DisplayMode	OLED_Display_Normal

#define	OLED_Float_Reserved			"%.2f"

#endif

/*********************************************************************
*					外部API接口及PUBLIC函数
*********************************************************************/
/*初始化*/
void OLED_Init(void);

/*显示函数*/
void OLED_SetContrast(uint8_t Level);
void OLED_Display_On(void);
void OLED_Display_Off(void);
void OLED_AllScreen_Clear(void);
void OLED_ReverseDisplay(bool OP);
void OLED_SetGRAMoffset(uint8_t Level);
void OLED_Refresh_GRAM(void);
void OLED_InverseDisplay(bool OP);

/*图形*/
void OLED_EditPixel(uint8_t X,uint8_t Y,bool OP);
void OLED_EditArea(uint8_t X0,uint8_t Y1,uint8_t X2,uint8_t Y2,uint8_t OP);
void OLED_DrawLine(uint8_t x1,uint8_t y1,uint8_t x2,uint8_t y2,bool OP);
void OLED_DrawCircle(uint8_t X,uint8_t Y,uint8_t R);
void OLED_DrawBMP(uint8_t X0,uint8_t Y0,uint8_t X1,uint8_t Y1,const char BMP[]);

/*字符*/
bool OLED_ShowChar(uint8_t X,uint8_t Y,uint8_t Char,uint8_t Size,bool OP);
bool OLED_ShowChinese(uint8_t X,uint8_t Y,uint8_t *s,uint8_t Sizey,bool OP);
void OLED_Set_Printfmt(uint16_t x,uint16_t y,uint8_t sizey,bool mode);
void OLED_Printf(const char *fmt,...);

/*以下旧数据的功能可能会产生冲突，不建议使用*/
/*如需使用请手动启用@line 141*/
#if OLED_FUNC_COMPATIBLE == 1
void OLED_ShowInt(uint8_t X,uint8_t Y,int32_t Int);
void OLED_ShowFloat(uint8_t X,uint8_t Y,float Float);
void OLED_ShowHex(uint8_t X,uint8_t Y,int32_t Num);
void OLED_ShowString(uint8_t X,uint8_t Y,const char *Str);
#endif

/*外部变量*/
extern OLED_STATUS_TYPE OLED_STATUS;

#endif	

/*********************************************************************
*							End Of File
*********************************************************************/
