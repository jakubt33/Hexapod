/*
 * bluetooth.h
 *
 *  Created on: Aug 7, 2014
 *      Author: Jakub Trzyna
 */

#ifndef BLUETOOTH_H_
#define BLUETOOTH_H_

#define BTPORT GPIOC
#define CONNECTIONPIN GPIO_Pin_13


void checkBluetooth();
void checkConnection();
void connectionEstablishedMessage();
void connectionNotEstablished();


void checkBluetooth()
{
	if( USART_GetFlagStatus(USART3, USART_FLAG_RXNE) != RESET )
	{
		//char Msg1=USART_ReceiveData(USART3);
		if( (USART_ReceiveData(USART3) >> 6) == 0b00 ) //Manual mode
		{

		}
		else if( (USART_ReceiveData(USART3) >> 6) == 0b01 ) //Auto mode
		{
			USART_ClearFlag(USART3,USART_FLAG_RXNE);

			int Command = USART_ReceiveData(USART3) & 0b00111111;

			while( USART_GetFlagStatus(USART3, USART_FLAG_RXNE) == RESET );

			if( (USART_ReceiveData(USART3) >> 6) == 0b11 ) // whole message received
			{
				EmergencyStop = USART_ReceiveData(USART3) & 0b00000001;

				int Speed = (USART_ReceiveData(USART3) >> 1) & 0b00011111;;

				switch(Command)
				{
					case 1:
					{
						goAhead(Speed);
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
						GPIO_WriteBit(PORT_LED, LED_LEG1 | LED_LEG2 | LED_LEG3, Bit_RESET);
						break;
					}
					default:
					{
						break;
					}
				}

			}
			else
				USART_ClearFlag(USART3,USART_FLAG_RXNE);
		}
		else
			USART_ClearFlag(USART3,USART_FLAG_RXNE);
	}
}

void connectionEstablishedMessage()
{

	ConnectionEstablished = TRUE;


	GPIO_WriteBit(PORT_LED, LED_LEG1 | LED_LEG2 | LED_LEG3 | LED_LEG4 | LED_LEG5 | LED_LEG6, Bit_RESET);

	LED_LEG1_ON;
	delay_ms(200);
	LED_LEG2_ON;
	delay_ms(200);
	LED_LEG3_ON;
	delay_ms(200);
	LED_LEG4_ON;
	delay_ms(200);
	LED_LEG5_ON;
	delay_ms(200);
	LED_LEG6_ON;
	delay_ms(200);

	GPIO_WriteBit(PORT_LED, LED_LEG1 | LED_LEG2 | LED_LEG3 | LED_LEG4 | LED_LEG5 | LED_LEG6, Bit_RESET);

}

void checkConnection()
{
	if( GPIO_ReadInputDataBit(BTPORT, CONNECTIONPIN) == SET )
	{
		connectionEstablishedMessage();
	}
	else
	{
		connectionNotEstablished();
	}
}

void checkIfConnectionLost()
{
	if( GPIO_ReadInputDataBit(BTPORT, CONNECTIONPIN) == RESET )
	{
		connectionNotEstablished();
	}
}

void connectionNotEstablished()
{
	ConnectionEstablished = FALSE;

	GPIO_WriteBit(PORT_LED, LED_LEG1 | LED_LEG2 | LED_LEG3 | LED_LEG4 | LED_LEG5 | LED_LEG6, Bit_SET);
	delay_ms(500);
	GPIO_WriteBit(PORT_LED, LED_LEG1 | LED_LEG2 | LED_LEG3 | LED_LEG4 | LED_LEG5 | LED_LEG6, Bit_RESET);
	delay_ms(500);

}

#endif /* BLUETOOTH_H_ */
