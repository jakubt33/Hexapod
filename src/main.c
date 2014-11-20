#include "stm32f10x.h"
#include <stm32f10x_rcc.h>
#include <stm32f10x_gpio.h>
#include <system_stm32f10x.h>


#define FALSE 0
#define TRUE  1
#define DONE  1

volatile int ConnectionEstablished = FALSE;
volatile u8 BatteryDischarged = FALSE;
volatile u8 PowerON = FALSE;

void delay_ms(int LocalCounter);
void delay_us(int LocalCounter);

#include "leds.h"
#include "serwo.h"
#include "movement.h"
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

	basePosition();
	while (1)
	{
		checkBattery();
		checkConnection();
		while(ConnectionEstablished == TRUE)
		{
			checkBattery();
			checkBluetooth();
			checkIfConnectionLost();
		}
	}

}

void checkBattery()
{
	volatile u8  ADC_value = (ADC1->DR) >> 4;

	//USART_SendData(USART3, ADC_value);

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
