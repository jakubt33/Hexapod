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
  uint16_t tmp;
  //Je¿eli jest to przerwanie od bufora odbiorczego
  if(USART_GetITStatus(USART3,USART_IT_RXNE) != RESET)
  {
      USART_ClearITPendingBit(USART3,USART_IT_RXNE);
      tmp=USART_ReceiveData(USART3);

      //do sth
  }

  //Je¿eli jest to przerwanie od bufora nadawczego
  if(USART_GetITStatus(USART3,USART_IT_TXE) != RESET)
  {
      USART_ClearITPendingBit(USART3,USART_IT_TXE);

      //do sth
  }
}


#endif /* BLUETOOTH_H_ */
