/*
 * bluetooth.h
 *
 *  Created on: Aug 7, 2014
 *      Author: Jakub Trzyna
 */

#ifndef BLUETOOTH_H_
#define BLUETOOTH_H_

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
			Lift += 10*USART_ReceiveData(USART3);

			while(USART_GetFlagStatus(USART3, USART_FLAG_RXNE) == RESET);

			USART_ClearFlag(USART3,USART_FLAG_RXNE);
			Lift += USART_ReceiveData(USART3);

			if(Lift<14 || Lift>40)
				Lift = 30;



			while(USART_GetFlagStatus(USART3, USART_FLAG_RXNE) == RESET);

				USART_ClearFlag(USART3,USART_FLAG_RXNE);
				Turn += 10*USART_ReceiveData(USART3);

			while(USART_GetFlagStatus(USART3, USART_FLAG_RXNE) == RESET);

				USART_ClearFlag(USART3,USART_FLAG_RXNE);
				Turn += USART_ReceiveData(USART3);

			if(Turn<20 || Turn>40)
				Turn = 30;



			while(USART_GetFlagStatus(USART3, USART_FLAG_RXNE) == RESET);

				USART_ClearFlag(USART3,USART_FLAG_RXNE);
				Speed = USART_ReceiveData(USART3);



			while(USART_GetFlagStatus(USART3, USART_FLAG_RXNE) == RESET);

				USART_ClearFlag(USART3,USART_FLAG_RXNE);
				Power = USART_ReceiveData(USART3);


			legTurn(Legs, Turn, Speed);
			legLift(Legs, Lift, Speed);

		}
		USART_SendData(USART3, '1');
	}
}


#endif /* BLUETOOTH_H_ */
