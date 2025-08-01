#include "Buzzer.h"
#include "Delay.h"
void Buzzer_on(uint8_t cnt)
{
	for(int i=0;i<cnt;i++)
	{
		DL_GPIO_setPins(GPIO_Buzzer_PORT, GPIO_Buzzer_PIN_A27_PIN);
		Delay_ms(100);
		DL_GPIO_clearPins(GPIO_Buzzer_PORT, GPIO_Buzzer_PIN_A27_PIN);
		Delay_ms(100);
	}
}

void Buzzer_Beep(uint16_t ms)
{
	DL_GPIO_setPins(GPIO_Buzzer_PORT, GPIO_Buzzer_PIN_A27_PIN);
	Delay_ms(ms);
	DL_GPIO_clearPins(GPIO_Buzzer_PORT, GPIO_Buzzer_PIN_A27_PIN);
}