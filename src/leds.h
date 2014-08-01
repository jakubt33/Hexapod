/*
 * leds.h
 *
 *  Created on: Jul 31, 2014
 *      Author: Kuba
 */

#ifndef LEDS_H_
#define LEDS_H_

#define PORT_LED GPIOA
#define LED_LEG1 GPIO_Pin_1
#define LED_LEG2 GPIO_Pin_2
#define LED_LEG3 GPIO_Pin_3
#define LED_LEG4 GPIO_Pin_4
#define LED_LEG5 GPIO_Pin_5
#define LED_LEG6 GPIO_Pin_6

#define LED_BAT_R2 GPIO_Pin_8
#define LED_BAT_R1 GPIO_Pin_9
#define LED_BAT_G3 GPIO_Pin_10
#define LED_BAT_G2 GPIO_Pin_11
#define LED_BAT_G1 GPIO_Pin_12

#define LED_LEG1_OFF GPIO_ResetBits(GPIOA, GPIO_Pin_1)
#define LED_LEG2_OFF GPIO_ResetBits(GPIOA, GPIO_Pin_2)
#define LED_LEG3_OFF GPIO_ResetBits(GPIOA, GPIO_Pin_3)
#define LED_LEG4_OFF GPIO_ResetBits(GPIOA, GPIO_Pin_4)
#define LED_LEG5_OFF GPIO_ResetBits(GPIOA, GPIO_Pin_5)
#define LED_LEG6_OFF GPIO_ResetBits(GPIOA, GPIO_Pin_6)

#define LED_BAT_R2_OFF GPIO_ResetBits(GPIOA, GPIO_Pin_8)
#define LED_BAT_R1_OFF GPIO_ResetBits(GPIOA, GPIO_Pin_9)
#define LED_BAT_G3_OFF GPIO_ResetBits(GPIOA, GPIO_Pin_10)
#define LED_BAT_G2_OFF GPIO_ResetBits(GPIOA, GPIO_Pin_11)
#define LED_BAT_G1_OFF GPIO_ResetBits(GPIOA, GPIO_Pin_12)

#define LED_LEG1_ON GPIO_SetBits(GPIOA, GPIO_Pin_1)
#define LED_LEG2_ON GPIO_SetBits(GPIOA, GPIO_Pin_2)
#define LED_LEG3_ON GPIO_SetBits(GPIOA, GPIO_Pin_3)
#define LED_LEG4_ON GPIO_SetBits(GPIOA, GPIO_Pin_4)
#define LED_LEG5_ON GPIO_SetBits(GPIOA, GPIO_Pin_5)
#define LED_LEG6_ON GPIO_SetBits(GPIOA, GPIO_Pin_6)


#define LED_BAT_R2_ON GPIO_SetBits(GPIOA, GPIO_Pin_8)
#define LED_BAT_R1_ON GPIO_SetBits(GPIOA, GPIO_Pin_9)
#define LED_BAT_G3_ON GPIO_SetBits(GPIOA, GPIO_Pin_10)
#define LED_BAT_G2_ON GPIO_SetBits(GPIOA, GPIO_Pin_11)
#define LED_BAT_G1_ON GPIO_SetBits(GPIOA, GPIO_Pin_12)

void batt_5_5()
{
	LED_BAT_G1_ON;
	LED_BAT_G2_ON;
	LED_BAT_G3_ON;

	LED_BAT_R1_OFF;
	LED_BAT_R2_OFF;
}
void batt_4_5()
{
	LED_BAT_G1_OFF;
	LED_BAT_G2_ON;
	LED_BAT_G3_ON;

	LED_BAT_R1_OFF;
	LED_BAT_R2_OFF;
}
void batt_3_5()
{
	LED_BAT_G1_OFF;
	LED_BAT_G2_OFF;
	LED_BAT_G3_ON;

	LED_BAT_R1_OFF;
	LED_BAT_R2_OFF;
}
void batt_2_5()
{
	LED_BAT_G1_OFF;
	LED_BAT_G2_OFF;
	LED_BAT_G3_ON;

	LED_BAT_R1_ON;
	LED_BAT_R2_OFF;
}
void batt_1_5()
{
	LED_BAT_G1_OFF;
	LED_BAT_G2_OFF;
	LED_BAT_G3_ON;

	LED_BAT_R1_ON;
	LED_BAT_R2_ON;
}
void batt_critical()
{
	LED_BAT_G1_OFF;
	LED_BAT_G2_OFF;
	LED_BAT_G3_OFF;

	//make it blinking, add flag disabling servo
	LED_BAT_R1_ON;
	LED_BAT_R2_ON;
}

#endif /* LEDS_H_ */
