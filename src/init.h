/*
 * init.h
 *
 *  Created on: Aug 1, 2014
 *      Author: Kuba
 */

#ifndef INIT_H_
#define INIT_H_

void init_LED()
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE); //enable clock on leds port

	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_StructInit (& GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1 |GPIO_Pin_2 |GPIO_Pin_3 |GPIO_Pin_4 |GPIO_Pin_5 |GPIO_Pin_6| GPIO_Pin_8 |GPIO_Pin_9 |GPIO_Pin_10 |GPIO_Pin_11 |GPIO_Pin_12;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;

	GPIO_Init(GPIOA, &GPIO_InitStructure);
}


#endif /* INIT_H_ */
