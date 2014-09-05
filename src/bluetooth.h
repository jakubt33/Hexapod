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
		if( (USART_ReceiveData(USART3) >> 6) == 0b00 ) //Manual mode
		{
			USART_ClearFlag(USART3,USART_FLAG_RXNE);

			char Legs = USART_ReceiveData(USART3) & 0b00111111;

			while( USART_GetFlagStatus(USART3, USART_FLAG_RXNE) == RESET );

			if( (USART_ReceiveData(USART3) >> 6) == 0b10 )
			{
				USART_ClearFlag(USART3,USART_FLAG_RXNE);

				unsigned int Lift = 0;
				Lift = (USART_ReceiveData(USART3) & 0b00111111) << 1; //lift is a 7-bit number

				while( USART_GetFlagStatus(USART3, USART_FLAG_RXNE) == RESET );

				if( (USART_ReceiveData(USART3) >> 6) == 0b10 )
				{
					USART_ClearFlag(USART3,USART_FLAG_RXNE);

					Lift += (USART_ReceiveData(USART3) >> 5) & 0b00000001;

					unsigned int Turn = 0;
					Turn = (USART_ReceiveData(USART3) & 0b00011111) << 1;

					while( USART_GetFlagStatus(USART3, USART_FLAG_RXNE) == RESET );

					if( (USART_ReceiveData(USART3) >> 6) == 0b11 )
					{
						USART_ClearFlag(USART3,USART_FLAG_RXNE);

						EmergencyStop = USART_ReceiveData(USART3) & 0b00000001;

						int Speed = 0;
						Speed = (USART_ReceiveData(USART3) >> 1) & 0b00011111;


						legTurn(Legs, Turn-30, Speed, NO_CURVE); //-100: go straight
						legLift(Legs, Lift-50, Speed);

					}
					else
						USART_ClearFlag(USART3,USART_FLAG_RXNE);

				}
				else
					USART_ClearFlag(USART3,USART_FLAG_RXNE);

			}
			else
				USART_ClearFlag(USART3,USART_FLAG_RXNE);


		}
		else if( (USART_ReceiveData(USART3) >> 6) == 0b01 ) //Auto mode
		{
			USART_ClearFlag(USART3,USART_FLAG_RXNE);

			int Command = USART_ReceiveData(USART3) & 0b00111111;
			int Curve = ((Command >> 2) & 0b000001111) << 1;

			while( USART_GetFlagStatus(USART3, USART_FLAG_RXNE) == RESET );

			if( (USART_ReceiveData(USART3) >> 6) == 0b11 ) // whole message received
			{
				EmergencyStop = USART_ReceiveData(USART3) & 0b00000001;

				int Speed = (USART_ReceiveData(USART3) >> 1) & 0b00001111;

				Curve += (USART_ReceiveData(USART3) >> 5) & 0b00000001;
				Curve -= 14;

				switch(Command & 0b00000011)
				{
					case 1:
					{
						goAhead(Speed, Curve);
						break;
					}
					case 2:
					{
						goBack(Speed, Curve);
						break;
					}
					case 3:
					{
						basePosition(Speed);
						break;
					}
					default:
					{
						if(Curve != 0)
							goAhead(Speed, Curve);
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
