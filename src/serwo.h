/*
 * serwo.h
 *
 *  Created on: Aug 1, 2014
 *      Author: Kuba
 */

#ifndef SERWO_H_
#define SERWO_H_

#define MAX_DEG 180

#define PORT_SERWO GPIOB
#define SERWO1 GPIO_Pin_0
#define SERWO2 GPIO_Pin_1
#define SERWO3 GPIO_Pin_2
#define SERWO4 GPIO_Pin_5
#define SERWO5 GPIO_Pin_6
#define SERWO6 GPIO_Pin_7
#define SERWO7 GPIO_Pin_8
#define SERWO8 GPIO_Pin_9
#define SERWO9 GPIO_Pin_12
#define SERWO10 GPIO_Pin_13
#define SERWO11 GPIO_Pin_14
#define SERWO12 GPIO_Pin_15

#define SERWO1_OFF GPIO_ResetBits(GPIOB, GPIO_Pin_0)
#define SERWO2_OFF GPIO_ResetBits(GPIOB, GPIO_Pin_1)
#define SERWO3_OFF GPIO_ResetBits(GPIOB, GPIO_Pin_2)
#define SERWO4_OFF GPIO_ResetBits(GPIOB, GPIO_Pin_5)
#define SERWO5_OFF GPIO_ResetBits(GPIOB, GPIO_Pin_6)
#define SERWO6_OFF GPIO_ResetBits(GPIOB, GPIO_Pin_7)
#define SERWO7_OFF GPIO_ResetBits(GPIOB, GPIO_Pin_8)
#define SERWO8_OFF GPIO_ResetBits(GPIOB, GPIO_Pin_9)
#define SERWO9_OFF GPIO_ResetBits(GPIOB, GPIO_Pin_12)
#define SERWO10_OFF GPIO_ResetBits(GPIOB, GPIO_Pin_13)
#define SERWO11_OFF GPIO_ResetBits(GPIOB, GPIO_Pin_14)
#define SERWO12_OFF GPIO_ResetBits(GPIOB, GPIO_Pin_15)

#define SERWO1_ON GPIO_SetBits(GPIOB, GPIO_Pin_0)
#define SERWO2_ON GPIO_SetBits(GPIOB, GPIO_Pin_1)
#define SERWO3_ON GPIO_SetBits(GPIOB, GPIO_Pin_2)
#define SERWO4_ON GPIO_SetBits(GPIOB, GPIO_Pin_5)
#define SERWO5_ON GPIO_SetBits(GPIOB, GPIO_Pin_6)
#define SERWO6_ON GPIO_SetBits(GPIOB, GPIO_Pin_7)
#define SERWO7_ON GPIO_SetBits(GPIOB, GPIO_Pin_8)
#define SERWO8_ON GPIO_SetBits(GPIOB, GPIO_Pin_9)
#define SERWO9_ON GPIO_SetBits(GPIOB, GPIO_Pin_12)
#define SERWO10_ON GPIO_SetBits(GPIOB, GPIO_Pin_13)
#define SERWO11_ON GPIO_SetBits(GPIOB, GPIO_Pin_14)
#define SERWO12_ON GPIO_SetBits(GPIOB, GPIO_Pin_15)


#endif /* SERWO_H_ */
