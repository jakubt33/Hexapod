#include "stm32f10x.h"
#include <stm32f10x_rcc.h>
#include <stm32f10x_gpio.h>
#include <system_stm32f10x.h>


#define FALSE 0
#define TRUE  1
#define DONE  1
#define ADC_MeanDivider 7 //64
#define ADC_MaxCounter 127

volatile int ConnectionEstablished = FALSE;
volatile u8 BatteryDischarged = FALSE;
volatile u8 PowerON = FALSE;
volatile u16 ADC_Mean = 0;
volatile u8 ADC_Counter = 0; //max 64->Div'6

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

	if(ADC_Counter < ADC_MaxCounter)
	{
		ADC_Mean += ADC_value;
		ADC_Counter++;
		if(GPIO_ReadInputDataBit(BTPORT, CONNECTIONPIN) == RESET) //connection not
		{
			ADC_Counter = ADC_MaxCounter;
		}
	}
	if(ADC_Counter >= ADC_MaxCounter)
	{
		if(GPIO_ReadInputDataBit(BTPORT, CONNECTIONPIN) == SET) //if connection established
		{
			ADC_Mean = ADC_Mean >> ADC_MeanDivider;
		}


		if(ADC_Mean<Batt_critical_value)
			batt_critical();
		else if(ADC_Mean<Batt_1_5_value)
			batt_1_5();
		else if(ADC_Mean<Batt_2_5_value)
			batt_2_5();
		else if(ADC_Mean<Batt_3_5_value)
			batt_3_5();
		else if(ADC_Mean<Batt_4_5_value)
			batt_4_5();
		else
			batt_5_5();

		ADC_Counter = 0;
		ADC_Mean = 0;
	}

	//USART_SendData(USART3, ADC_value);

}
