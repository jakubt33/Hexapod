/*
 * bluetooth.h
 *
 *  Created on: Aug 7, 2014
 *      Author: Jakub Trzyna
 */

#ifndef BLUETOOTH_H_
#define BLUETOOTH_H_

void USART3_IRQHandler(void)
{
	if(USART_GetITStatus(USART3, USART_FLAG_RXNE) != RESET)
	{
		USART_ClearITPendingBit(USART3,USART_IT_RXNE);

		char tmp;
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
}


#endif /* BLUETOOTH_H_ */
