#include "OLED.h"
#include "OLED_FONT.h"

OLED_STATUS_TYPE OLED_STATUS;

static char OLED_Display_Buffer[OLED_Printf_BufferSize];

uint8_t OLED_GRAM[128][8];

#if	OLED_Mode==OLED_USE_SPI
/************************************************

*@brief:		OLED引脚配置函数
*@note:			移植OLED请参考OLED.h中配置引脚配置函数
*********************************************************************/
static void OLED_Pin_Config(void)
{
	GPIO_InitTypeDef	GPIO_InitTypeStructure;

	RCC_APB2PeriphClockCmd(OLED_PIN_Periph,ENABLE);

	GPIO_InitTypeStructure.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_InitTypeStructure.GPIO_Pin=OLED_SCL_Pin;
	GPIO_InitTypeStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(OLED_SCL_Port,&GPIO_InitTypeStructure);

	GPIO_InitTypeStructure.GPIO_Pin=OLED_SDA_Pin;
	GPIO_Init(OLED_SDA_Port,&GPIO_InitTypeStructure);

	GPIO_InitTypeStructure.GPIO_Pin=OLED_CS_Pin;
	GPIO_Init(OLED_CS_Port,&GPIO_InitTypeStructure);

	GPIO_InitTypeStructure.GPIO_Pin=OLED_DC_Pin;
	GPIO_Init(OLED_DC_Port,&GPIO_InitTypeStructure);

	OLED_SCL_High();									//上电保持高电平防止使能芯片
	OLED_DC_High();
	OLED_CS_High();
}

/*********************************************************************
*@brief:		SPI通信格式向OLED发送数据/命令
*@param:		需要写入的数据/命令Data
*@param:		命令写入数据类型数据标识符WR_Command该参数只能为以下：
*				@arg:	Write_Data			表示向OLED写入数据
*				@arg:	Write_Command		表示向OLED写入命令
*@retval:		函数返回获取数据
*********************************************************************/
static void OLED_WriteReadByte(uint8_t Data,uint8_t WR_Command)
{
	uint8_t	bit_ctr;

	if(WR_Command)										//判断是向OLED写入数据还是命令
		OLED_DC_High();
	else
		OLED_DC_Low();

	OLED_SCL_High();
	OLED_CS_Low();
	for(bit_ctr=0;bit_ctr<8;bit_ctr++)
	{
		OLED_SCL_Low();
		if(Data&(0x80>>bit_ctr))
			OLED_SDA_High();
		else
			OLED_SDA_Low();
		OLED_SCL_High();
	}
	OLED_CS_High();
	OLED_DC_High();
}

#elif OLED_Mode==OLED_USE_IIC
/*********************************************************************
*@brief:		OLED引脚配置函数
*@note:			移植OLED请参考OLED.h中配置引脚配置函数
*********************************************************************/
static void OLED_Pin_Config(void)
{

}

/*********************************************************************
*@brief:		OLED IIC开始信号
*********************************************************************/
static void OLED_IIC_Start()
{
	OLED_SCL_High();
	OLED_SDA_High();
	OLED_Delay();
	OLED_SDA_Low();
	OLED_Delay();
	OLED_SCL_Low();
}

/*********************************************************************
*@brief:		OLED IICֹͣ�ź�
*********************************************************************/
static void OLED_IIC_Stop()
{
	OLED_SCL_Low();
	OLED_SDA_Low();
	OLED_Delay();
	OLED_SCL_High();
	OLED_Delay();
	OLED_SDA_High();
}

/*********************************************************************
*@brief:		OLED IIC发送一个字节
*@param:		需要写入的数据Data
*@retval:		None
*********************************************************************/
static void OLED_IIC_WriteByte(uint8_t Byte)
{
	uint8_t Bit_ctr;
	for(Bit_ctr=0;Bit_ctr<8;Bit_ctr++)
	{
		if(Byte&0x80){OLED_SDA_High();}	   
  		else{OLED_SDA_Low();}
		OLED_Delay();
		OLED_SCL_High();
		OLED_Delay();
		OLED_SCL_Low();
		Byte<<=1;
	}

	OLED_SDA_High();										//释放数据信号
	OLED_Delay();
	OLED_SCL_High();
	OLED_Delay();
	OLED_SCL_Low();
}

/*********************************************************************
*@brief:		IIC通信格式向OLED发送数据/命令
*@param:		需要写入的数据/命令Data
*@param:		命令写入数据类型数据标识符WR_Command该参数只能为以下：
*				@arg:	Write_Data			表示向OLED写入数据
*				@arg:	Write_Command		表示向OLED写入命令
*@retval:		None
*********************************************************************/
static void OLED_WriteReadByte(uint8_t Data,uint8_t WR_Command)
{
	if(WR_Command==Write_Command)
	{
		OLED_IIC_Start();
		OLED_IIC_WriteByte(0x78);           				//从机默认地址为0x78
		OLED_IIC_WriteByte(0x00);							//写入命令
		OLED_IIC_WriteByte(Data);
		OLED_IIC_Stop();
	}
	else if(WR_Command==Write_Data)
	{
		OLED_IIC_Start();
		OLED_IIC_WriteByte(0x78);
		OLED_IIC_WriteByte(0x40);							//写入数据
		OLED_IIC_WriteByte(Data);
		OLED_IIC_Stop();
	}
}

#endif

/*********************************************************************
*@brief:		设置OLED光标位置
*@param:		X坐标
*@param:		Y坐标0~7
*@retval:		None
*********************************************************************/
static void OLED_Set_Pos(uint8_t X,uint8_t Y) 
{
	OLED_WriteReadByte(0xB0+Y,Write_Command);
	OLED_WriteReadByte(((X&0xF0)>>4)|0x10,Write_Command);
	OLED_WriteReadByte((X&0x0F)|0x01,Write_Command);
}

/*********************************************************************
*@brief:		开启OLED显示
*********************************************************************/
void OLED_Display_On(void)
{
	OLED_WriteReadByte(0X8D,Write_Command);					//SET DCDC命令
	OLED_WriteReadByte(0X14,Write_Command);					//DCDC ON
	OLED_WriteReadByte(0XAF,Write_Command);					//DISPLAY ON
}

/*********************************************************************
*@brief:		关闭OLED显示
*********************************************************************/
void OLED_Display_Off(void)
{
	OLED_WriteReadByte(0X8D,Write_Command);  				//SET DCDC命令
	OLED_WriteReadByte(0X10,Write_Command); 				//DCDC OFF
	OLED_WriteReadByte(0XAE,Write_Command);  				//DISPLAY OFF
}

/*********************************************************************
*@brief:		刷新OLED的GRAM
*@note:			用户手动修改前需要先写入OLED_GRAM[][]数组
*********************************************************************/
void OLED_Refresh_GRAM(void)
{
	uint8_t Page_ctr,Pixel_ctr;

	for(Page_ctr=0;Page_ctr<8;Page_ctr++)
	{
		OLED_WriteReadByte(0xB0+Page_ctr,Write_Command);    //设置页地址(0xB0~0xB7)
		OLED_WriteReadByte(0x00,Write_Command);      		//设置显示位置列低地址
		OLED_WriteReadByte(0x10,Write_Command);      		//设置显示位置列高地址
		for(Pixel_ctr=0;Pixel_ctr<128;Pixel_ctr++)
		{
			OLED_WriteReadByte(OLED_GRAM[127-Pixel_ctr][Page_ctr],Write_Data);
		}
	}
}

/*********************************************************************
*@brief:		OLED全屏清空
*********************************************************************/
void OLED_AllScreen_Clear(void)
{
	uint8_t Page_ctr,Pixel_ctr;
 
	for(Page_ctr=0;Page_ctr<8;Page_ctr++)					//共8页128*8*8个字节数据全部0x00
	{
		for(Pixel_ctr=0;Pixel_ctr<128;Pixel_ctr++)
		{
			OLED_GRAM[Pixel_ctr][Page_ctr]=0X00;
		}
	}
	OLED_Refresh_GRAM();									//修改GRAM
}

/*********************************************************************
*@brief:		OLED修改单一像素点
*@param:		X点		像素点X坐标,参数值有效范围0~127
*@param:		Y点		像素点Y坐标,参数值有效范围0~63
*@param:		OP:		选择是否绘制像素点,true为绘,false为擦
*@retval:		None
*********************************************************************/
void OLED_EditPixel(uint8_t X,uint8_t Y,bool OP)
{
	uint8_t Page;

	if(X>127||Y>63){return;}								//超范围了
	Page=Y/8;												//确定页码
	if(OP)
		OLED_GRAM[127-X][Page]|=(1<<(Y%8));
	else
		OLED_GRAM[127-X][Page]&=~(1<<(Y%8));
}

/*********************************************************************
*@brief:		OLED修改区域像素
*@param:		X0：	区域起始X坐标,参数值有效范围0~127
*@param:		Y0：	区域起始Y坐标,参数值有效范围0~63
*@param:		X1：	区域末尾X坐标,参数值有效范围0~127
*@param:		Y1：	区域末尾Y坐标,参数值有效范围0~63
*@param:		OP:		选择是否填充该像素,该参数值只能为如下：
*				@arg:	OLED_Clear
*				@arg:	OLED_Fill
*@retval:		None
*********************************************************************/
void OLED_EditArea(uint8_t X0,uint8_t Y0,uint8_t X1,uint8_t Y1,uint8_t OP)  
{
	uint8_t X,Y;  

	for(X=X0;X<=X1;X++)					//ͨ�������༭���ص����޸�ѡ����������
	{
		for(Y=Y0;Y<=Y1;Y++)
		{
			OLED_EditPixel(X,Y,OP);
		}
	}
	OLED_Refresh_GRAM();				//刷新GRAM
}

/*********************************************************************
*@brief:		OLED画线函数
*@param:		x1:		直线起始X坐标,参数值有效范围0~127
*@param:		y1:		直线起始Y坐标,参数值有效范围0~63
*@param:		x2:		直线末尾X坐标,参数值有效范围0~127
*@param:		y2:		直线末尾Y坐标,参数值有效范围0~63
*@param:		OP:		是否反显,true为反显,false为正显
*@retval:		None
*********************************************************************/
void OLED_DrawLine(uint8_t x1,uint8_t y1,uint8_t x2,uint8_t y2,bool OP)
{
	uint16_t Step; 
	uint16_t X_Current,Y_Current;
	
	int32_t lError_X=0,lError_Y=0,lDelta_X,lDelta_Y,lDistance; 
	int32_t lIncrease_X,lIncrease_Y;

	lDelta_Y=y2-y1;
	lDelta_X=x2-x1;
	
	X_Current=x1;
	Y_Current=y1;

	if(lDelta_X>0) 
		lIncrease_X=1;
	else if(lDelta_X==0) 
		lIncrease_X=0;
	else
	{
		lIncrease_X=-1;
		lDelta_X=-lDelta_X;
	}

	if (lDelta_Y>0)
		lIncrease_Y=1;
	else if(lDelta_Y==0)
		lIncrease_Y=0;
	else
	{
		lIncrease_Y=-1;
		lDelta_Y=-lDelta_Y;
	}

	if(lDelta_X>lDelta_Y)
		lDistance=lDelta_X;
	else 
		lDistance=lDelta_Y; 

	for(Step=0;Step<=lDistance+1;Step++)
	{
		OLED_EditPixel(X_Current,Y_Current,!OP); 
		lError_X += lDelta_X ; 
		lError_Y += lDelta_Y ; 
		if(lError_X>lDistance) 
		{
			lError_X-=lDistance; 
			X_Current+=lIncrease_X; 
		}

		if(lError_Y>lDistance) 
		{
			lError_Y-=lDistance; 
			Y_Current+=lIncrease_Y; 
		}
	}

	OLED_Refresh_GRAM();
}

/*********************************************************************
*@brief:		OLED画圆函数
*@param:		X0:		圆心坐标X,参数值有效范围0~127
*@param:		Y0:		圆心坐标Y,参数值有效范围0~63
*@param:		R:		圆半径
*@retval:		None
*********************************************************************/
void OLED_DrawCircle(uint8_t X,uint8_t Y,uint8_t R)
{
	int a,b,num;
    a=0;
    b=R;
    while(2*b*b>=R*R)      
    {
        OLED_EditPixel(X + a, Y - b,OLED_PixelFill);
        OLED_EditPixel(X - a, Y - b,OLED_PixelFill);
        OLED_EditPixel(X - a, Y + b,OLED_PixelFill);
        OLED_EditPixel(X + a, Y + b,OLED_PixelFill);
        OLED_EditPixel(X + b, Y + a,OLED_PixelFill);
        OLED_EditPixel(X + b, Y - a,OLED_PixelFill);
        OLED_EditPixel(X - b, Y - a,OLED_PixelFill);
        OLED_EditPixel(X - b, Y + a,OLED_PixelFill);
        a++;
        num=(a*a+b*b)-R*R;		//计算画的点到圆心的距离
        if(num>0)
        {
            b--;
            a--;
        }
    }

	OLED_Refresh_GRAM();
}

/*********************************************************************
*@brief:		OLED在指定位置显示一个字符(仅限ASCII码)
*@param:		X:				字符X坐标,参数值有效范围0~127
*@param:		Y:				字符行坐标,参数值有效范围0~63
*@param:		Char:			待显示的字符
*@param:		Fonty:			字体格式,可选择的参数如下：
*@arg:							OLED_FONTSIZE_12X6
*@arg:							OLED_FONTSIZE_16X8
*@arg:							OLED_FONTSIZE_24X12
*@param:		OP:				false为正常显示，true为反显
*@retval:		true:显示成功	false:显示显示失败,可能是非法字符号大小
*********************************************************************/
bool OLED_ShowChar(uint8_t X,uint8_t Y,uint8_t Char,uint8_t Fonty,bool OP)
{
	uint8_t Data,Byte_ctr,Bit_ctr;
	uint8_t Y0=Y;										//记录原始Y坐标
	uint8_t Char_Size=(Fonty/8+((Fonty%8)?1:0))*(Fonty/2);	//得到点阵一个字符对应字节数占用的字节数
	Char=Char-' ';										//获取偏移后的值
	for(Byte_ctr=0;Byte_ctr<Char_Size;Byte_ctr++)
	{
		switch(Fonty)
		{
			case 12:	Data=ASCII_1206[Char][Byte_ctr];break;				//调用1206ASCII字库
			case 16:	Data=ASCII_1608[Char][Byte_ctr];break;				//调用1608ASCII字库
			case 24:	Data=ASCII_2412[Char][Byte_ctr];break;				//调用2412ASCII字库
			default: return false;											//不存在该字库
		}

		for(Bit_ctr=0;Bit_ctr<8;Bit_ctr++)					//逐位写入GRAM
		{
			if((Data<<Bit_ctr)&0x80)
			{
				OLED_EditPixel(X,Y,!OP);
			}
			else
			{
				OLED_EditPixel(X,Y,OP);			//清空像素
			}
			Y++;

			if((Y-Y0)==Fonty)
			{
				Y=Y0;
				X++;
				break;
			}
		}
	}

	if(OLED_STATUS.STA.BIT.RAM_BUSY == 0){OLED_Refresh_GRAM();}				//避免外部频繁调用OLED_ShowChar时,造成频繁刷新GRAM

	return true;
}

/************************************************************
*@brief:	OLED设置Printf格式函数为打印设定前置函数
*@param:	x:				打印起始OLED屏x坐标
*@param:	y:				打印起始OLED屏y坐标
*@param:	sizey:			打印内容的字符号大小
*@param:	mode:			打印内容的显示模式(是否需要反显)
*@retval:	None
*@note:		该函数应为OLED_Printf设定前置函数
************************************************************/
__inline void OLED_Set_Printfmt(uint16_t x,uint16_t y,uint8_t sizey,bool mode)
{
	OLED_STATUS.STA.BIT.fmt_x=x;
	OLED_STATUS.STA.BIT.fmt_y=y;
	OLED_STATUS.STA.BIT.fmt_mode=mode;
	OLED_STATUS.STA.BIT.fmt_sizey=sizey;
}

/************************************************************
*@brief:	������OLED��printf,�����볬���ն˵�ͬ
************************************************************/
void OLED_Printf(const char *fmt,...)
{
	uint8_t chinese_buf[3]={'\0'};

	__IO char * dispbuf_ptr=OLED_Display_Buffer;

	va_list ap;
	va_start(ap,fmt);
	vsprintf(OLED_Display_Buffer,fmt,ap);
	va_end(ap);

	OLED_STATUS.STA.BIT.RAM_BUSY=1;

	while(*dispbuf_ptr !='\0')
	{
		if(*dispbuf_ptr > 127)
		{
			chinese_buf[0]=*dispbuf_ptr++;
			chinese_buf[1]=*dispbuf_ptr++;

			/*自动换行*/
			if(OLED_STATUS.STA.BIT.fmt_x+OLED_STATUS.STA.BIT.fmt_sizey/2 > Max_X_Pixel)
			{OLED_STATUS.STA.BIT.fmt_x=0;OLED_STATUS.STA.BIT.fmt_y+=OLED_STATUS.STA.BIT.fmt_sizey;}

			/*调用显示*/
			OLED_ShowChinese(OLED_STATUS.STA.BIT.fmt_x,OLED_STATUS.STA.BIT.fmt_y,chinese_buf,OLED_STATUS.STA.BIT.fmt_sizey,OLED_STATUS.STA.BIT.fmt_mode);

			/*更新坐标*/
			OLED_STATUS.STA.BIT.fmt_x+=OLED_STATUS.STA.BIT.fmt_sizey;
		}
		else if(*dispbuf_ptr == '\n')
		{
			OLED_STATUS.STA.BIT.fmt_x=0;
			OLED_STATUS.STA.BIT.fmt_y+=OLED_STATUS.STA.BIT.fmt_sizey;
			dispbuf_ptr++;
		}
		else if(*dispbuf_ptr == '\t')
		{
			if(OLED_STATUS.STA.BIT.fmt_x+2*OLED_STATUS.STA.BIT.fmt_sizey > Max_X_Pixel)
			{OLED_STATUS.STA.BIT.fmt_x=0;OLED_STATUS.STA.BIT.fmt_y+=OLED_STATUS.STA.BIT.fmt_sizey;}
			else
			{OLED_STATUS.STA.BIT.fmt_x+=2*OLED_STATUS.STA.BIT.fmt_sizey;}
			dispbuf_ptr++;
		}
		else
		{
			/*自动换行*/
			if(OLED_STATUS.STA.BIT.fmt_x+OLED_STATUS.STA.BIT.fmt_sizey/2 > Max_X_Pixel)
			{OLED_STATUS.STA.BIT.fmt_x=0;OLED_STATUS.STA.BIT.fmt_y+=OLED_STATUS.STA.BIT.fmt_sizey;}

			/*ASCII显示*/
			OLED_ShowChar(OLED_STATUS.STA.BIT.fmt_x,OLED_STATUS.STA.BIT.fmt_y,*dispbuf_ptr++,OLED_STATUS.STA.BIT.fmt_sizey,OLED_STATUS.STA.BIT.fmt_mode);

			/*更新坐标*/
			OLED_STATUS.STA.BIT.fmt_x+=OLED_STATUS.STA.BIT.fmt_sizey/2;
		}
	}

	OLED_STATUS.STA.BIT.RAM_BUSY=0;
	OLED_Refresh_GRAM();

}

#if OLED_FUNC_COMPATIBLE == 1
/*********************************************************************
*@brief:		OLED显示整数函数
*@param:		X:			字符X坐标,参数值有效范围0~127
*@param:		Y:			字符行坐标,参数值有效范围0~63
*@param:		Int:		待显示的整数(有符号)
*@retval:		None
*********************************************************************/
void OLED_ShowInt(uint8_t X,uint8_t Y,int32_t Int)
{
	char ConvertedValue[10];
	uint8_t Char_ctr,X0=X,Y0=Y;

	OLED_STATUS.STA.BIT.RAM_BUSY=1;
	sprintf(ConvertedValue,"%d",Int);
	for(Char_ctr=0;ConvertedValue[Char_ctr]!='\0';Char_ctr++)
	{
		OLED_ShowChar(X0,Y0,ConvertedValue[Char_ctr],OLED_Default_FONT,OLED_Default_DisplayMode);
		X0+=(OLED_Default_FONT)/2;
		if(X0>120)																//�����ж�
		{
			X0=0;
			Y0+=OLED_Default_FONT;
		}
	}
	OLED_Refresh_GRAM();

	OLED_STATUS.STA.BIT.RAM_BUSY=0;
}

/*********************************************************************
*@brief:		OLED显示十六进制数
*@param:		X:			字符X坐标,填入值必须在有效范围0~127
*@param:		Y:			字符行坐标,填入值必须在有效范围0~63
*@param:		Num:		装载用的数据(十六进制数)
*@retval:		None
*********************************************************************/
void OLED_ShowHex(uint8_t X,uint8_t Y,int32_t Num)
{
	char ConvertedValue[10];
	uint8_t Char_ctr,X0=X,Y0=Y;

	OLED_STATUS.STA.BIT.RAM_BUSY=1;

	sprintf(ConvertedValue,"%#x",Num);
	for(Char_ctr=0;ConvertedValue[Char_ctr]!='\0';Char_ctr++)
	{
		OLED_ShowChar(X0,Y0,ConvertedValue[Char_ctr],OLED_Default_FONT,OLED_Default_DisplayMode);
		X0+=(OLED_Default_FONT)/2;
		if(X0>120)																//�����ж�
		{
			X0=0;
			Y0+=OLED_Default_FONT;
		}
	}
	OLED_Refresh_GRAM();

	OLED_STATUS.STA.BIT.RAM_BUSY=0;
}

/*********************************************************************
*@brief:		OLED��ʾ������
*@param:		X:			�ַ�X����,����ֵ����Ч��Χ0~127
*@param:		Y:			�ַ������꣬����ֵ����Ч��Χ0~63
*@param:		Float:		����ʾ�ĸ�����
*@retval:		None
*@note:			����С������λ����OLED_Float_Reserved����
*********************************************************************/
void OLED_ShowFloat(uint8_t X,uint8_t Y,float Float)
{
	char ConvertedValue[10];
	uint8_t Char_ctr,X0=X,Y0=Y;

	OLED_STATUS.STA.BIT.RAM_BUSY=1;

	sprintf(ConvertedValue,OLED_Float_Reserved,Float);
	for(Char_ctr=0;ConvertedValue[Char_ctr]!='\0';Char_ctr++)
	{
		OLED_ShowChar(X0,Y0,ConvertedValue[Char_ctr],OLED_Default_FONT,OLED_Default_DisplayMode);
		X0+=(OLED_Default_FONT)/2;
		if(X0>120)																//�����ж�
		{
			X0=0;
			Y0+=OLED_Default_FONT;
		}
	}
	OLED_Refresh_GRAM();

	OLED_STATUS.STA.BIT.RAM_BUSY=0;
}

/*********************************************************************
*@brief:		OLED��ʾ�ַ���
*@param:		X:			�ַ�X����,����ֵ����Ч��Χ0~127
*@param:		Y:			�ַ�������,����ֵ����Ч��Χ0~63
*@param:		*Str:		����ʾ���ַ����׵�ַ
*@retval:		None
*********************************************************************/
void OLED_ShowString(uint8_t X,uint8_t Y,const char *Str)
{
	uint8_t Char_ctr=0,X0=X,Y0=Y;

	OLED_STATUS.STA.BIT.RAM_BUSY=1;
	while(Str[Char_ctr]!='\0')
	{
		OLED_ShowChar(X0,Y0,Str[Char_ctr],OLED_Default_FONT,OLED_Default_DisplayMode);
		X0+=(OLED_Default_FONT)/2;
		if(X0>120)																//�����ж�
		{
			X0=0;
			Y0+=OLED_Default_FONT;
		}
		Char_ctr++;
	}
	OLED_Refresh_GRAM();

	OLED_STATUS.STA.BIT.RAM_BUSY=0;
}

#endif

/*********************************************************************
*@brief:		OLED��ʾ�������ĺ���(16�ֺ�)
*@param:		X:				�ַ�X����,����ֵ����Ч��Χ0~127
*@param:		Y:				�ַ���Ӧҳ����,����ֵ����Ч��Χ0~255
*@param:		*s:				�����ַ�
*@param:		OP:				�Ƿ���
*@retval:		true:	��ӡ�ɹ�		false:	��ӡʧ�ܣ������ǷǷ����ֺŴ�С
*********************************************************************/
void OLED_ShowChinese16x16(uint8_t X,uint8_t Y,uint8_t *s,bool OP)
{
	uint8_t Bit_ctr,Data,Y0=Y;
	uint16_t Byte_ctr,HZnum,Select_Byte;

	HZnum=sizeof(FONT_GB_16)/sizeof(FONT_GB_16_TYPE);				//ͳ�ƺ�����Ŀ

	for(Select_Byte=0;Select_Byte<HZnum;Select_Byte++) 
	{
		if((FONT_GB_16[Select_Byte].Index[0]==*(s))&&(FONT_GB_16[Select_Byte].Index[1]==*(s+1)))
		{
			for(Byte_ctr=0;Byte_ctr<32;Byte_ctr++)
			{
				Data=FONT_GB_16[Select_Byte].Msk[Byte_ctr];
				for(Bit_ctr=0;Bit_ctr<8;Bit_ctr++)					//��λд��GRAM
				{
					if((Data<<Bit_ctr)&0x80)
					{
						OLED_EditPixel(X,Y,!OP);					//������ʾ
					}
					else
					{
						OLED_EditPixel(X,Y,OP);						//����
					}
					Y++;
					if((Y-Y0)==16)
					{
						Y=Y0;
						X++;
						break;
					}
				}
			}
		}
	}
}

/*********************************************************************
*@brief:		OLED��ʾ�����ַ���
*@param:		X:				�ַ�X����,����ֵ����Ч��Χ0~127
*@param:		Y:				�ַ���Ӧҳ����,����ֵ����Ч��Χ0~255
*@param:		*s:				�����ַ���
*@param:		Sizey:			�����С
*@param:		OP:				�Ƿ���(falseΪ������ʾ��trueΪ��������)
*@retval:		true:	��ӡ�ɹ�		false:	��ӡʧ�ܣ������ǷǷ��������С
*********************************************************************/
bool OLED_ShowChinese(uint8_t X,uint8_t Y,uint8_t *s,uint8_t Sizey,bool OP)
{
	while(*s != '\0')
	{
		switch(Sizey)
		{

			case 16 : OLED_ShowChinese16x16(X,Y,s,OP);break;

			default:	return false;
		}
		s+=2;
		X+=Sizey;
	}

	if(OLED_STATUS.STA.BIT.RAM_BUSY == 0){OLED_Refresh_GRAM();}				//���ⲿƵ������OLED_ShowCharʱ,����Ƶ��ˢ��GRAM

	return true;
}

/*********************************************************************
*@brief:		OLED��ֱ��ת
*@param:		Mode:	��ֱ��ת��ʾ����
*@arg:			false:������ʾ	true:��ֱ��ת��ʾ
*@retval:		None
*********************************************************************/
void OLED_ReverseDisplay(bool OP)
{
	if(OP == false)//������ʾ
	{
		OLED_WriteReadByte(0xC8,Write_Command);
		OLED_WriteReadByte(0xA1,Write_Command);
	}
	else
	{
		OLED_WriteReadByte(0xC0,Write_Command);
		OLED_WriteReadByte(0xA0,Write_Command);
	}
}

/*********************************************************************
*@brief:		OLED��ʾBMP��ʽͼ��
*@param:		X0:		ͼ����ʼX����,����ֵ����Ч��Χ0~127
*@param:		Y0:		ͼ����ʼҳ����,����ֵ����Ч��Χ0~7
*@param:		X1:		ͼ��ĩβX����,����ֵ����Ч��Χ0~127
*@param:		Y1:		ͼ��ĩβҳ����,����ֵ����Ч��Χ0~7
*@param:		BMP[]:	BMP��ʽͼ�������׵�ַ
*@retval:		None
*@note:			������ʾͼ������X0,Y0,X1,Y1������ԭʼbmp���ش�Сд��
*********************************************************************/
void OLED_DrawBMP(uint8_t X0,uint8_t Y0,uint8_t X1,uint8_t Y1,const char BMP[])
{
	uint16_t Pixel_ctr=0;
	uint8_t x,y;

	if(Y1%8==0)
	{
		y=Y1/8;
	}
	else
	{
		y=Y1/8+1;
	}
	for(y=Y0;y<Y1;y++)
	{
		OLED_Set_Pos(X0,y);
		for(x=X0;x<X1;x++)
		{      
			OLED_WriteReadByte(BMP[Pixel_ctr++],Write_Data);
		}
	}
}

/*********************************************************************
*@brief:		OLED�Աȶ�(����)���ں���
*@param:		Level:	���ڵ��ĶԱȶ�(����)ֵ,����ֵ����Ч��Χ0~255
*@retval:		None
*********************************************************************/
void OLED_SetContrast(uint8_t Level)
{
	OLED_WriteReadByte(0x81,Write_Command);
	OLED_WriteReadByte(Level,Write_Command);
}

/*********************************************************************
*@brief:		OLED����GRAM��Y�����ϵ�ƫ��
*@param:		Level:	������GRAM��ƫ�Ƶ�ֵ,����ֵ����Ч��Χ0~63
*@retval:		None
*********************************************************************/
void OLED_SetGRAMoffset(uint8_t Level)
{
	if(Level>63){Level=0;}
	OLED_WriteReadByte(0xD3,Write_Command);
	OLED_WriteReadByte(Level,Write_Command);
}

/*********************************************************************
*@brief:		OLEDȫ������
*@param:		OP:		�Ƿ���ȫ������,true��ʾ��,false��ʾ��
*@retval:		None
*********************************************************************/
void OLED_InverseDisplay(bool OP)
{
	if(OP)
	OLED_WriteReadByte(0xA6,Write_Command);
	else
	OLED_WriteReadByte(0xA7,Write_Command);
}

/*********************************************************************
*@brief:		OLED初始化程序
*@note:			本函数自动初始化其他函数不建议用户修改
*********************************************************************/
void OLED_Init(void)
{
	OLED_Pin_Config();

	#if OLED_USE_RES == 1
	/*复位(如果需要)*/
	OLED_RES_Low();
	OLED_Delay();
	OLED_RES_High();
	#endif

	OLED_Delay();

	OLED_WriteReadByte(0xAE,Write_Command);//--turn off oled panel
	OLED_WriteReadByte(0x00,Write_Command);//---set low column address
	OLED_WriteReadByte(0x10,Write_Command);//---set high column address
	OLED_WriteReadByte(0x40,Write_Command);//--set start line address  Set Mapping RAM Display Start Line (0x00~0x3F)
	OLED_WriteReadByte(0x81,Write_Command);//--set contrast control register
	OLED_WriteReadByte(0xCF,Write_Command);// Set SEG Output Current Brightness
	OLED_WriteReadByte(0xA1,Write_Command);//--Set SEG/Column Mapping     			0xa0���ҷ��� 0xa1����
	OLED_WriteReadByte(0xC8,Write_Command);//Set COM/Row Scan Direction   			0xc0���·��� 0xc8����
	OLED_WriteReadByte(0xA6,Write_Command);//--set normal display
	OLED_WriteReadByte(0xA8,Write_Command);//--set multiplex ratio(1 to 64)
	OLED_WriteReadByte(0x3f,Write_Command);//--1/64 duty
	OLED_WriteReadByte(0xD3,Write_Command);//-set display offset	Shift Mapping RAM Counter (0x00~0x3F)
	OLED_WriteReadByte(0x00,Write_Command);//-not offset
	OLED_WriteReadByte(0xd5,Write_Command);//--set display clock divide ratio/oscillator frequency
	OLED_WriteReadByte(0x80,Write_Command);//--set divide ratio, Set Clock as 100 Frames/Sec
	OLED_WriteReadByte(0xD9,Write_Command);//--set pre-charge period
	OLED_WriteReadByte(0xF1,Write_Command);//Set Pre-Charge as 15 Clocks & Discharge as 1 Clock
	OLED_WriteReadByte(0xDA,Write_Command);//--set com pins hardware configuration
	OLED_WriteReadByte(0x12,Write_Command);
	OLED_WriteReadByte(0xDB,Write_Command);//--set vcomh
	OLED_WriteReadByte(0x40,Write_Command);//Set VCOM Deselect Level
	OLED_WriteReadByte(0x20,Write_Command);//-Set Page Addressing Mode (0x00/0x01/0x02)
	OLED_WriteReadByte(0x02,Write_Command);//
	OLED_WriteReadByte(0x8D,Write_Command);//--set Charge Pump enable/disable
	OLED_WriteReadByte(0x14,Write_Command);//--set(0x10) disable
	OLED_WriteReadByte(0xA4,Write_Command);// Disable Entire Display On (0xa4/0xa5)
	OLED_WriteReadByte(0xA6,Write_Command);// Disable Inverse Display On (0xa6/a7) 
	OLED_WriteReadByte(0xAF,Write_Command);//--turn on oled panel

	OLED_WriteReadByte(0xAF,Write_Command); /*display ON*/

	OLED_AllScreen_Clear();
}

/*********************************************************************
*							End Of File
*********************************************************************/
