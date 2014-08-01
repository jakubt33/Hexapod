//#include <stddef.h>
#include "stm32f10x.h"
#include <stm32f10x_rcc.h>
#include <stm32f10x_gpio.h>
#include "leds.h"
#include "init.h"


void delay(volatile unsigned counter)
{
  while(counter--);
}

int main(void)
{
	init_LED();
	GPIO_WriteBit(PORT_LED, LED_LEG1 | LED_LEG2 | LED_LEG3 | LED_LEG4 | LED_LEG5 | LED_LEG6, Bit_SET);

	batt_1_5();
	while (1)
	{

	}
}
