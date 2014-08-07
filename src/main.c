volatile unsigned int Counter = 0;
volatile unsigned int SerwoPosition = 0;

void delay_ms(volatile unsigned LocalCounter)
{
	LocalCounter*=300;
	while(LocalCounter--);
}
void delay_us(volatile unsigned LocalCounter)
{
	while(LocalCounter--);
}

void checkBattery();

#include "stm32f10x.h"
#include <stm32f10x_rcc.h>
#include <stm32f10x_gpio.h>
#include "leds.h"
#include "serwo.h"
#include "init.h"
//#include "bluetooth.h"

#define UP 34 //max = 40
#define DOWN 30 //min = 20
#define LAYDOWN 14

int main(void)
{
	init_LED();
	init_Servo();
	init_ADC();
	init_TIM2();
	init_USART();

	//GPIO_WriteBit(PORT_LED, LED_LEG1 | LED_LEG2 | LED_LEG3 | LED_LEG4 | LED_LEG5 | LED_LEG6, Bit_SET);
	//GPIO_WriteBit(PORT_LED, LED_LEG1, Bit_SET);

	checkBattery();
	delay_ms(1000);

	legLift(132456, 40, 3);

	char tmp;
	while (1)
	{
		if(USART_GetFlagStatus(USART3, USART_FLAG_RXNE) != RESET)
		{
			USART_ClearFlag(USART3,USART_FLAG_RXNE);

			tmp=USART_ReceiveData(USART3);
			switch (tmp)
			{
			case '1':
			{
				GPIO_WriteBit(PORT_LED, LED_LEG1, Bit_SET);
				break;
			}
			case '2':
			{
				GPIO_WriteBit(PORT_LED, LED_LEG2, Bit_SET);
				break;
			}
			case '3':
			{
				GPIO_WriteBit(PORT_LED, LED_LEG3, Bit_SET);
				break;
			}
			case '4':
			{
				GPIO_WriteBit(PORT_LED, LED_LEG4, Bit_SET);
				break;
			}
			case '5':
			{
				GPIO_WriteBit(PORT_LED, LED_LEG5, Bit_SET);
				break;
			}
			case '6':
			{
				GPIO_WriteBit(PORT_LED, LED_LEG6, Bit_SET);
				break;
			}
			default:
			{
				GPIO_WriteBit(PORT_LED, LED_LEG2 | LED_LEG5, Bit_SET);
				break;
			}
			}
			USART_SendData(USART3, tmp);

		}


		/*  Sending and receiving data so that diodes are respectively set, RX-TX short
		int LocalCounter=0;
		for(LocalCounter=1; LocalCounter<=6; LocalCounter++)
		{
			if(USART_GetFlagStatus(USART3, USART_FLAG_RXNE) != RESET)
			{
				USART_ClearFlag(USART3,USART_FLAG_RXNE);

				tmp=USART_ReceiveData(USART3);
				switch (tmp)
				{
				case 1:
				{
					GPIO_WriteBit(PORT_LED, LED_LEG2 | LED_LEG3 | LED_LEG4 | LED_LEG5 | LED_LEG6, Bit_RESET);
					break;
				}
				case 2:
				{
					GPIO_WriteBit(PORT_LED, LED_LEG2, Bit_SET);
					break;
				}
				case 3:
				{
					GPIO_WriteBit(PORT_LED, LED_LEG3, Bit_SET);
					break;
				}
				case 4:
				{
					GPIO_WriteBit(PORT_LED, LED_LEG4, Bit_SET);
					break;
				}
				case 5:
				{
					GPIO_WriteBit(PORT_LED, LED_LEG5, Bit_SET);
					break;
				}
				case 6:
				{
					GPIO_WriteBit(PORT_LED, LED_LEG6, Bit_SET);
					break;
				}
				default:
				{
					GPIO_WriteBit(PORT_LED, LED_LEG1 | LED_LEG2 | LED_LEG3 | LED_LEG4 | LED_LEG5 | LED_LEG6, Bit_SET);
					break;
				}
				}
			}
			tmp = LocalCounter;
			USART_SendData(USART3, tmp);
			delay_ms(300);

		}
		*/

		/*
	  uint16_t tmp;
	  //Je¿eli jest to przerwanie od bufora odbiorczego
	  if(USART_GetITStatus(USART3,USART_IT_RXNE) != RESET)
	  {
		  USART_ClearITPendingBit(USART3,USART_IT_RXNE);
		  tmp=USART_ReceiveData(USART3);

		  GPIO_WriteBit(PORT_LED, LED_LEG2 | LED_LEG3 | LED_LEG4 | LED_LEG5 | LED_LEG6, Bit_SET);


		  //do sth
	 	 }

		//Je¿eli jest to przerwanie od bufora nadawczego
		if(USART_GetITStatus(USART3,USART_IT_TXE) != RESET)
		{
			USART_ClearITPendingBit(USART3,USART_IT_TXE);
			USART_SendData(USART3, tmp);
			//do sth
		}
	    */


		/*
		legTurn(132456, 25, 3);
		delay_ms(1000);
		legTurn(132456, 35, 3);
		delay_ms(1000);
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
