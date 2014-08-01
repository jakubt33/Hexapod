//#include <stddef.h>
#include "stm32f10x.h"
#include <stm32f10x_rcc.h>
#include <stm32f10x_gpio.h>
#include "leds.h"
#include "init.h"


void delay_ms(volatile unsigned counter)
{
	counter*=1150;
	while(counter--);
}
void delay_us(volatile unsigned counter)
{
	while(counter--);
}

int main(void)
{
	init_LED();
	init_ADC();
	GPIO_WriteBit(PORT_LED, LED_LEG1 | LED_LEG2 | LED_LEG3 | LED_LEG4 | LED_LEG5 | LED_LEG6, Bit_SET);

	volatile unsigned ADC_value = 0;
	while (1)
	{
		ADC_value = ADC1->DR;
		if(ADC_value<Batt_critical_value)
			batt_critical();
		else if(ADC_value<Batt_1_5_value)
			batt_1_5();
		else if(ADC_value<Batt_2_5_value)
			batt_2_5();
		else if(ADC_value<Batt_3_5_value)
			batt_3_5();
		else if(ADC_value<Batt_4_5_value)
			batt_4_5();
		else
			batt_5_5();
	}
}
