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



	while (1)
	{
		connectionNotEstablished();
		/*
		//step1
		legTurn(123456, 20, 3);
		delay_ms(1000);

		//step2
		legLift(24, 30, 3);
		delay_ms(1000);
		legTurn(24, 32, 3);
		delay_ms(1000);
		legLift(24, 23, 3);
		delay_ms(1000);

		//step3
		legLift(15, 30, 3);
		delay_ms(1000);
		legTurn(15, 32, 3);
		delay_ms(1000);
		legLift(15, 23, 3);
		delay_ms(1000);

		//step4
		legLift(36, 30, 3);
		delay_ms(1000);
		legTurn(36, 32, 3);
		delay_ms(1000);
		legLift(36, 23, 3);
		delay_ms(1000);

		//step5
		legTurn(123456, 20, 3);
		delay_ms(1000);
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
