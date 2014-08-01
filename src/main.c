//#include <stddef.h>
#include "stm32f10x.h"
#include <stm32f10x_rcc.h>
#include <stm32f10x_gpio.h>
#include "leds.h"
#include "serwo.h"
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

volatile unsigned int counter = 0;
volatile unsigned int deg = 0;

void TIM2_IRQHandler()
{
	TIM_ClearFlag(TIM2, TIM_FLAG_Update);

	counter++;

	if (counter<deg)
	{
		SERWO1_ON;
		SERWO2_ON;
		SERWO3_ON;
		SERWO4_ON;
		SERWO5_ON;
		SERWO6_ON;
		SERWO7_ON;
		SERWO8_ON;
		SERWO9_ON;
		SERWO10_ON;
		SERWO11_ON;
		SERWO12_ON;
	}
	else if(counter<MAX_DEG)
	{
		SERWO1_OFF;
		SERWO2_OFF;
		SERWO3_OFF;
		SERWO4_OFF;
		SERWO5_OFF;
		SERWO6_OFF;
		SERWO7_OFF;
		SERWO8_OFF;
		SERWO9_OFF;
		SERWO10_OFF;
		SERWO11_OFF;
		SERWO12_OFF;
	}
	else
	{
		counter = 0;
	}
}

int main(void)
{
	init_LED();
	init_Servo();
	init_ADC();
	init_TIM2();

	GPIO_WriteBit(PORT_LED, LED_LEG1 | LED_LEG2 | LED_LEG3 | LED_LEG4 | LED_LEG5 | LED_LEG6, Bit_SET);

	//volatile unsigned ADC_value = 0;
	while (1)
	{
		deg=10;
		delay_ms(1000);
		deg=20;
		delay_ms(1000);
		/*
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
		*/
	}
}
