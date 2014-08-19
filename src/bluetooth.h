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
	if(USART_GetFlagStatus(USART3, USART_FLAG_RXNE) != RESET)
	{
		USART_ClearFlag(USART3,USART_FLAG_RXNE);

		if(USART_ReceiveData(USART3) == 'M')
		{
			long unsigned int Legs=0;
			int Lift=0;
			int Turn=0;
			int Speed=0;

			USART_SendData(USART3, USART_ReceiveData(USART3));

			//getting legs information
			while(USART_GetFlagStatus(USART3, USART_FLAG_RXNE) == RESET);

			USART_ClearFlag(USART3,USART_FLAG_RXNE);
			if(USART_ReceiveData(USART3) != '0') Legs += 100000;
			USART_SendData(USART3, USART_ReceiveData(USART3));

			while(USART_GetFlagStatus(USART3, USART_FLAG_RXNE) == RESET);

			USART_ClearFlag(USART3,USART_FLAG_RXNE);
			if(USART_ReceiveData(USART3) != '0') Legs += 20000;
			USART_SendData(USART3, USART_ReceiveData(USART3));


			while(USART_GetFlagStatus(USART3, USART_FLAG_RXNE) == RESET);

			USART_ClearFlag(USART3,USART_FLAG_RXNE);
			if(USART_ReceiveData(USART3) != '0') Legs += 3000;
			USART_SendData(USART3, USART_ReceiveData(USART3));

			while(USART_GetFlagStatus(USART3, USART_FLAG_RXNE) == RESET);

			USART_ClearFlag(USART3,USART_FLAG_RXNE);
			if(USART_ReceiveData(USART3) != '0') Legs += 400;
			USART_SendData(USART3, USART_ReceiveData(USART3));

			while(USART_GetFlagStatus(USART3, USART_FLAG_RXNE) == RESET);

			USART_ClearFlag(USART3,USART_FLAG_RXNE);
			if(USART_ReceiveData(USART3) != '0') Legs += 50;
			USART_SendData(USART3, USART_ReceiveData(USART3));

			while(USART_GetFlagStatus(USART3, USART_FLAG_RXNE) == RESET);

			USART_ClearFlag(USART3,USART_FLAG_RXNE);
			if(USART_ReceiveData(USART3) != '0') Legs += 6;
			USART_SendData(USART3, USART_ReceiveData(USART3));
			//getting legs information


			//getting lift information
			while(USART_GetFlagStatus(USART3, USART_FLAG_RXNE) == RESET);

			USART_ClearFlag(USART3,USART_FLAG_RXNE);
			Lift += 10* ( USART_ReceiveData(USART3) - '0' );
			USART_SendData(USART3, USART_ReceiveData(USART3));

			while(USART_GetFlagStatus(USART3, USART_FLAG_RXNE) == RESET);

			USART_ClearFlag(USART3,USART_FLAG_RXNE);
			Lift += USART_ReceiveData(USART3) - '0';
			USART_SendData(USART3, USART_ReceiveData(USART3));

			Lift -= 50;
			if(Lift<-50 || Lift>80)
				Lift = 0;
			//getting lift information



			//getting turn information
			while(USART_GetFlagStatus(USART3, USART_FLAG_RXNE) == RESET);

			USART_ClearFlag(USART3,USART_FLAG_RXNE);
			Turn += 10* ( USART_ReceiveData(USART3) - '0' );
			USART_SendData(USART3, USART_ReceiveData(USART3));

			while(USART_GetFlagStatus(USART3, USART_FLAG_RXNE) == RESET);

			USART_ClearFlag(USART3,USART_FLAG_RXNE);
			Turn += USART_ReceiveData(USART3) - '0';
			USART_SendData(USART3, USART_ReceiveData(USART3));

			Turn -= 30;
			if(Turn<-30 || Turn>30)
				Turn = 0;
			//getting turn information



			//getting speed information
			while(USART_GetFlagStatus(USART3, USART_FLAG_RXNE) == RESET);

			USART_ClearFlag(USART3,USART_FLAG_RXNE);
			Speed = USART_ReceiveData(USART3) - '0';
			USART_SendData(USART3, USART_ReceiveData(USART3));
			//getting speed information


			//getting power cut down information
			while(USART_GetFlagStatus(USART3, USART_FLAG_RXNE) == RESET);

			USART_ClearFlag(USART3,USART_FLAG_RXNE);
			EmergencyStop = USART_ReceiveData(USART3) - '0';
			USART_SendData(USART3, USART_ReceiveData(USART3));
			//getting power cut down information



			legTurn(Legs, Turn, Speed);
			legLift(Legs, Lift, Speed);

		}
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
