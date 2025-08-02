include "Encoder.h"

static ENCODER_RES motor_encoder[2];

//编码器初始化
void encoder_init(void)
{
	//编码器引脚外部中断
	NVIC_ClearPendingIRQ(GPIOA_INT_IRQn);
    NVIC_ClearPendingIRQ(GPIOB_INT_IRQn);
	NVIC_EnableIRQ(GPIOA_INT_IRQn);
	NVIC_EnableIRQ(GPIOB_INT_IRQn);
}

//获取编码器的值
void get_encoder_count(int32_t Encoder_cnt1,int32_t Encoder_cnt2)
{
	Encoder_cnt1 = motor_encoder[0].count;
	Encoder_cnt2 = motor_encoder[1].count;
}

//编码器数据更新
//请间隔一定时间更新
void encoder_update(void)
{
	for(int i=0;i<=1;i++)
	{
		motor_encoder[i].count = motor_encoder[i].temp_count;

		//确定方向
		motor_encoder[i].dir = ( motor_encoder[i].count >= 0 ) ? FORWARD : REVERSAL;

		motor_encoder[i].temp_count = 0;//编码器计数值清零
	}
}

void GROUP1_IRQHandler(void)
{
    uint32_t gpio_status;

	//获取中断信号情况
	gpio_status = DL_GPIO_getEnabledInterruptStatus(GPIO_ENCODERA_PORT, GPIO_ENCODERA_PIN_A_1_PIN | GPIO_ENCODERA_PIN_A_2_PIN);
	//编码器A相上升沿触发
	if((gpio_status & GPIO_ENCODERA_PIN_A_1_PIN) == GPIO_ENCODERA_PIN_A_1_PIN)
	{
		//如果在A相上升沿下，B相为低电平
		if(!DL_GPIO_readPins(GPIO_ENCODERA_PORT,GPIO_ENCODERA_PIN_A_2_PIN))
		{
			motor_encoder[0].temp_count--;
		}
		else
		{
			motor_encoder[0].temp_count++;
		}
	}//编码器B相上升沿触发
	else if((gpio_status & GPIO_ENCODERA_PIN_A_2_PIN)==GPIO_ENCODERA_PIN_A_2_PIN)
	{
		//如果在B相上升沿下，A相为低电平
		if(!DL_GPIO_readPins(GPIO_ENCODERA_PORT,GPIO_ENCODERA_PIN_A_1_PIN))
		{
			motor_encoder[0].temp_count++;
		}
		else
		{
			motor_encoder[0].temp_count--;
		}
	}
	//清除状态
	DL_GPIO_clearInterruptStatus(GPIO_ENCODERA_PORT,GPIO_ENCODERA_PIN_A_1_PIN|GPIO_ENCODERA_PIN_A_2_PIN);
}
