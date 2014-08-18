#include "stm32f10x.h"
#include <stm32f10x_rcc.h>
#include <stm32f10x_gpio.h>
#include <system_stm32f10x.h>


#define FALSE 0
#define TRUE  1

volatile int ConnectionEstablished = FALSE;
void delay_ms(int LocalCounter);
void delay_us(int LocalCounter);

#include "leds.h"
#include "serwo.h"
#include "bluetooth.h"
#include "init.h"

void checkBattery();

int main(void)
{
	init_Clock();
	init_LED();
	init_Servo();
	init_ADC();
	init_TIM2();
	init_Bluetooth();


	//delay_ms(1000);
	checkBattery();

	//GPIO_WriteBit(PORT_LED, LED_LEG1 | LED_LEG2 | LED_LEG3 | LED_LEG4 | LED_LEG5 | LED_LEG6, Bit_SET);
	//GPIO_WriteBit(PORT_LED, LED_LEG1, Bit_SET);

	delay_ms(1000);

	//step1
	legTurn(123456, 0, 4);
	legLift(123456, 0, 4);
	delay_ms(500);


	while (1)
	{
		/*
		 * walking sequence
		 *
		legLift(135, 25, 4);
		delay_ms(1000);
		legTurn(246, -25, 4);
		legTurn(135, 25, 4);
		delay_ms(1000);
		legLift(135, 0, 4);
		delay_ms(1000);

		legLift(246, 25, 4);
		delay_ms(1000);
		legTurn(135, -25, 4);
		legTurn(246, 25, 4);
		delay_ms(1000);
		legLift(246, 0, 4);
		*/


		/*
		checkConnection();
		//while(ConnectionEstablished == TRUE)
			//checkBluetooth();
		//connectionNotEstablished();
		 */
	}

}

void checkBattery()
{
	volatile unsigned ADC_value = 0;

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
