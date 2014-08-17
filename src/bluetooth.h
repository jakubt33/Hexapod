/*
 * bluetooth.h
 *
 *  Created on: Aug 7, 2014
 *      Author: Jakub Trzyna
 */

#ifndef BLUETOOTH_H_
#define BLUETOOTH_H_

#define BTPORT GPIOC
#define CONNECTIONPIN GPIO_Pin_15


void checkBluetooth();
void checkConnection();
void connectionEstablishedMessage();
void connectionNotEstablished();


void checkBluetooth()
{
	if(USART_GetFlagStatus(USART3, USART_FLAG_RXNE) != RESET)
	{
		USART_ClearFlag(USART3,USART_FLAG_RXNE);

		if(USART_ReceiveData(USART3) == 'M')
		{
			long unsigned int Legs=0;
			int Lift=0;
			int Turn=0;
			int Speed=0;
			int Power=0;


			while(USART_GetFlagStatus(USART3, USART_FLAG_RXNE) == RESET);

			USART_ClearFlag(USART3,USART_FLAG_RXNE);
			if(USART_ReceiveData(USART3) != '0') Legs += 100000;

			while(USART_GetFlagStatus(USART3, USART_FLAG_RXNE) == RESET);

			USART_ClearFlag(USART3,USART_FLAG_RXNE);
			if(USART_ReceiveData(USART3) != '0') Legs += 20000;

			while(USART_GetFlagStatus(USART3, USART_FLAG_RXNE) == RESET);

			USART_ClearFlag(USART3,USART_FLAG_RXNE);
			if(USART_ReceiveData(USART3) != '0') Legs += 3000;

			while(USART_GetFlagStatus(USART3, USART_FLAG_RXNE) == RESET);

			USART_ClearFlag(USART3,USART_FLAG_RXNE);
			if(USART_ReceiveData(USART3) != '0') Legs += 400;

			while(USART_GetFlagStatus(USART3, USART_FLAG_RXNE) == RESET);

			USART_ClearFlag(USART3,USART_FLAG_RXNE);
			if(USART_ReceiveData(USART3) != '0') Legs += 50;

			while(USART_GetFlagStatus(USART3, USART_FLAG_RXNE) == RESET);

			USART_ClearFlag(USART3,USART_FLAG_RXNE);
			if(USART_ReceiveData(USART3) != '0') Legs += 6;



			while(USART_GetFlagStatus(USART3, USART_FLAG_RXNE) == RESET);

			USART_ClearFlag(USART3,USART_FLAG_RXNE);
			Lift += 10* ( USART_ReceiveData(USART3) - '0' );

			while(USART_GetFlagStatus(USART3, USART_FLAG_RXNE) == RESET);

			USART_ClearFlag(USART3,USART_FLAG_RXNE);
			Lift += USART_ReceiveData(USART3) - '0';

			if(Lift<14 || Lift>40)
				Lift = 23;



			while(USART_GetFlagStatus(USART3, USART_FLAG_RXNE) == RESET);

			USART_ClearFlag(USART3,USART_FLAG_RXNE);
			Turn += 10* ( USART_ReceiveData(USART3) - '0' );

			while(USART_GetFlagStatus(USART3, USART_FLAG_RXNE) == RESET);

			USART_ClearFlag(USART3,USART_FLAG_RXNE);
			Turn += USART_ReceiveData(USART3) - '0';

			if(Turn<20 || Turn>40)
				Turn = 30;



			while(USART_GetFlagStatus(USART3, USART_FLAG_RXNE) == RESET);

			USART_ClearFlag(USART3,USART_FLAG_RXNE);
			Speed = USART_ReceiveData(USART3) - '0';



			while(USART_GetFlagStatus(USART3, USART_FLAG_RXNE) == RESET);

			USART_ClearFlag(USART3,USART_FLAG_RXNE);
			Power = USART_ReceiveData(USART3) - '0';



			legTurn(Legs, Turn, Speed);
			legLift(Legs, Lift, Speed);

		}
		USART_SendData(USART3, 0x31);
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

	if( GPIO_ReadInputDataBit(BTPORT, CONNECTIONPIN  == 1) )
	{
		connectionEstablishedMessage();
	}

}

void connectionNotEstablished()
{
	GPIO_WriteBit(PORT_LED, LED_LEG1 | LED_LEG2 | LED_LEG3 | LED_LEG4 | LED_LEG5 | LED_LEG6, Bit_SET);
	delay_ms(10);
	GPIO_WriteBit(PORT_LED, LED_LEG1 | LED_LEG2 | LED_LEG3 | LED_LEG4 | LED_LEG5 | LED_LEG6, Bit_RESET);
	delay_ms(50);

}

#endif /* BLUETOOTH_H_ */
