volatile unsigned int Counter = 0;
volatile unsigned int SerwoPosition = 0;

#include "stm32f10x.h"
#include <stm32f10x_rcc.h>
#include <stm32f10x_gpio.h>
#include "leds.h"
#include "serwo.h"
#include "init.h"

#define UP 34 //max = 40
#define DOWN 30 //min = 20
#define LAYDOWN 14

void delay_ms(volatile unsigned LocalCounter)
{
	LocalCounter*=1150;
	while(LocalCounter--);
}
void delay_us(volatile unsigned LocalCounter)
{
	while(LocalCounter--);
}

int main(void)
{
	init_LED();
	init_Servo();
	init_ADC();
	init_TIM2();

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

		legLift(132456, UP, 10);
		delay_ms(1000);
		legLift(132456, DOWN, 10);
		delay_ms(1000);


		//SerwoPosition=10;
		//delay_ms(1000);
		//SerwoPosition=20;
		//delay_ms(1000);

	}
}
