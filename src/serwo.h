/*
 * serwo.h
 *
 *  Created on: Aug 1, 2014
 *      Author: Jakub Trzyna
 */

#ifndef SERWO_H_
#define SERWO_H_

#define MAX_SPEED 15
#define TIME_TO_GET_50HZ 2000 //2000

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

#define LEG1TURN_OFF GPIO_ResetBits(GPIOB, GPIO_Pin_0)
#define LEG1LIFT_OFF GPIO_ResetBits(GPIOB, GPIO_Pin_1)
#define LEG2TURN_OFF GPIO_ResetBits(GPIOB, GPIO_Pin_2)
#define LEG4LIFT_OFF GPIO_ResetBits(GPIOB, GPIO_Pin_5)
#define LEG5LIFT_OFF GPIO_ResetBits(GPIOB, GPIO_Pin_6)
#define LEG5TURN_OFF GPIO_ResetBits(GPIOB, GPIO_Pin_7)
#define LEG6LIFT_OFF GPIO_ResetBits(GPIOB, GPIO_Pin_8)
#define LEG6TURN_OFF GPIO_ResetBits(GPIOB, GPIO_Pin_9)
#define LEG2LIFT_OFF GPIO_ResetBits(GPIOB, GPIO_Pin_12)
#define LEG3TURN_OFF GPIO_ResetBits(GPIOB, GPIO_Pin_13)
#define LEG3LIFT_OFF GPIO_ResetBits(GPIOB, GPIO_Pin_14)
#define LEG4TURN_OFF GPIO_ResetBits(GPIOB, GPIO_Pin_15)

#define LEG1TURN_ON GPIO_SetBits(GPIOB, GPIO_Pin_0)
#define LEG1LIFT_ON GPIO_SetBits(GPIOB, GPIO_Pin_1)
#define LEG2TURN_ON GPIO_SetBits(GPIOB, GPIO_Pin_2)
#define LEG4LIFT_ON GPIO_SetBits(GPIOB, GPIO_Pin_5)
#define LEG5LIFT_ON GPIO_SetBits(GPIOB, GPIO_Pin_6)
#define LEG5TURN_ON GPIO_SetBits(GPIOB, GPIO_Pin_7)
#define LEG6LIFT_ON GPIO_SetBits(GPIOB, GPIO_Pin_8)
#define LEG6TURN_ON GPIO_SetBits(GPIOB, GPIO_Pin_9)
#define LEG2LIFT_ON GPIO_SetBits(GPIOB, GPIO_Pin_12)
#define LEG3TURN_ON GPIO_SetBits(GPIOB, GPIO_Pin_13)
#define LEG3LIFT_ON GPIO_SetBits(GPIOB, GPIO_Pin_14)
#define LEG4TURN_ON GPIO_SetBits(GPIOB, GPIO_Pin_15)


#define LEG1LIFT_BASE 150
#define LEG2LIFT_BASE 150
#define LEG3LIFT_BASE 125
#define LEG4LIFT_BASE 148
#define LEG5LIFT_BASE 122
#define LEG6LIFT_BASE 125

#define LEG1TURN_BASE 150
#define LEG2TURN_BASE 150
#define LEG3TURN_BASE 150
#define LEG4TURN_BASE 150
#define LEG5TURN_BASE 150
#define LEG6TURN_BASE 150


volatile long int Counter = 0;

//steering:
//up: L1,L2,L4 +40, L3,L5,L6 -40
//down: L1,L2,L4 -90, L3,L5,L6 +90
volatile  int Leg1Lift = LEG1LIFT_BASE-40;
volatile  int Leg2Lift = LEG2LIFT_BASE-40;
volatile  int Leg3Lift = LEG3LIFT_BASE+40;
volatile  int Leg4Lift = LEG4LIFT_BASE-40;
volatile  int Leg5Lift = LEG5LIFT_BASE+40;
volatile  int Leg6Lift = LEG6LIFT_BASE+40;

volatile  int Leg1Turn = LEG1TURN_BASE;
volatile  int Leg2Turn = LEG2TURN_BASE;
volatile  int Leg3Turn = LEG3TURN_BASE;
volatile  int Leg4Turn = LEG4TURN_BASE;
volatile  int Leg5Turn = LEG5TURN_BASE;
volatile  int Leg6Turn = LEG6TURN_BASE;

void checkLegs(char WhichLeg, int *Leg1, int *Leg2, int *Leg3, int *Leg4, int *Leg5, int *Leg6);
void applyLegs(int x, int *Leg1, int *Leg2, int *Leg3, int *Leg4, int *Leg5, int *Leg6);
void TIM2_IRQHandler();

void legLift(char WhichLeg, int Position, int Speed); //symetrically \||/
void legTurn(char WhichLeg, int Position, int Speed, int ExtraCase); //symetrically \||/

void TIM2_IRQHandler()
{
	TIM_ClearFlag(TIM2, TIM_FLAG_Update);

	if( (Counter == 0) && (EmergencyStop) )
	{

		LEG1LIFT_ON;
		LEG2LIFT_ON;
		LEG3LIFT_ON;
		LEG4LIFT_ON;
		LEG5LIFT_ON;
		LEG6LIFT_ON;

		LEG1TURN_ON;
		LEG2TURN_ON;
		LEG3TURN_ON;
		LEG4TURN_ON;
		LEG5TURN_ON;
		LEG6TURN_ON;
	}

	Counter++;

	if(Counter>Leg1Lift)
		LEG1LIFT_OFF;

	if(Counter>Leg2Lift)
		LEG2LIFT_OFF;

	if(Counter>Leg3Lift)
		LEG3LIFT_OFF;

	if(Counter>Leg4Lift)
		LEG4LIFT_OFF;

	if(Counter>Leg5Lift)
		LEG5LIFT_OFF;

	if(Counter>Leg6Lift)
		LEG6LIFT_OFF;


	if(Counter>Leg1Turn)
		LEG1TURN_OFF;

	if(Counter>Leg2Turn)
		LEG2TURN_OFF;

	if(Counter>Leg3Turn)
		LEG3TURN_OFF;

	if(Counter>Leg4Turn)
		LEG4TURN_OFF;

	if(Counter>Leg5Turn)
		LEG5TURN_OFF;

	if(Counter>Leg6Turn)
		LEG6TURN_OFF;



	if(Counter >= TIME_TO_GET_50HZ)
		Counter = 0;
}

void legTurn(char WhichLeg, int Position, int Speed, int ExtraCase)
{
	if(Speed>15) Speed = MAX_SPEED;
	if(Speed<0) Speed = 0;
	Speed = 2*(MAX_SPEED - Speed);

	int Leg1=0,Leg2=0,Leg3=0,Leg4=0,Leg5=0,Leg6=0;

	checkLegs(WhichLeg, &Leg1, &Leg2, &Leg3, &Leg4, &Leg5, &Leg6);


	int PositionL = Position;
	int PositionR = -Position; //mirror view


	int Leg1Diff=0,Leg2Diff=0,Leg3Diff=0,Leg4Diff=0,Leg5Diff=0,Leg6Diff=0;


	if(ExtraCase == 0)
	{
		if(Leg1)
			Leg1Diff = (PositionL - (Leg1Turn-LEG1TURN_BASE));
		if(Leg2)
			Leg2Diff = (PositionL - (Leg2Turn-LEG2TURN_BASE));
		if(Leg3)
			Leg3Diff = (PositionL - (Leg3Turn-LEG3TURN_BASE));
		if(Leg4)
			Leg4Diff = (PositionR - (Leg4Turn-LEG4TURN_BASE));
		if(Leg5)
			Leg5Diff = (PositionR - (Leg5Turn-LEG5TURN_BASE));
		if(Leg6)
			Leg6Diff = (PositionR - (Leg6Turn-LEG6TURN_BASE));
	}
	else if(ExtraCase == 1)
	{
		if(Leg1)
			Leg1Diff = (PositionR - (Leg1Turn-LEG1TURN_BASE));
		if(Leg2)
			Leg2Diff = (PositionL - (Leg2Turn-LEG2TURN_BASE));
		if(Leg3)
			Leg3Diff = (PositionR - (Leg3Turn-LEG3TURN_BASE));
		if(Leg4)
			Leg4Diff = (PositionR - (Leg4Turn-LEG4TURN_BASE));
		if(Leg5)
			Leg5Diff = (PositionL - (Leg5Turn-LEG5TURN_BASE));
		if(Leg6)
			Leg6Diff = (PositionR - (Leg6Turn-LEG6TURN_BASE));
	}


	int MAXDiff=0;
	if( (Leg1Diff > MAXDiff) && (Leg1Diff > 0) )
		MAXDiff = Leg1Diff;
	else if( (-Leg1Diff > MAXDiff) && (Leg1Diff < 0) )
		MAXDiff = -Leg1Diff;

	if( (Leg2Diff > MAXDiff) && (Leg2Diff > 0) )
		MAXDiff = Leg2Diff;
	else if( (-Leg2Diff > MAXDiff) && (Leg2Diff < 0) )
		MAXDiff = -Leg2Diff;

	if( (Leg3Diff > MAXDiff) && (Leg3Diff > 0) )
		MAXDiff = Leg3Diff;
	else if( (-Leg3Diff > MAXDiff) && (Leg3Diff < 0) )
		MAXDiff = -Leg3Diff;

	if( (Leg4Diff > MAXDiff) && (Leg4Diff > 0) )
		MAXDiff = Leg4Diff;
	else if( (-Leg4Diff > MAXDiff) && (Leg4Diff < 0) )
		MAXDiff = -Leg4Diff;

	if( (Leg5Diff > MAXDiff) && (Leg5Diff > 0) )
		MAXDiff = Leg5Diff;
	else if( (-Leg5Diff > MAXDiff) && (Leg5Diff < 0) )
		MAXDiff = -Leg5Diff;

	if( (Leg6Diff > MAXDiff) && (Leg6Diff > 0) )
		MAXDiff = Leg6Diff;
	else if( (-Leg6Diff > MAXDiff) && (Leg6Diff < 0) )
		MAXDiff = -Leg6Diff;
	//mamy +maxDiff


	int LCounter=1;
	for(LCounter=MAXDiff; LCounter>=1; LCounter--)
	{
		if( (Leg1Diff >= LCounter) && (Leg1Diff > 0) )
			Leg1Turn++;
		else if( (-Leg1Diff >= LCounter) && (Leg1Diff < 0) )
			Leg1Turn--;

		if( (Leg2Diff >= LCounter) && (Leg2Diff > 0) )
			Leg2Turn++;
		else if( (-Leg2Diff >= LCounter) && (Leg2Diff < 0) )
			Leg2Turn--;

		if( (Leg3Diff >= LCounter) && (Leg3Diff > 0) )
			Leg3Turn++;
		else if( (-Leg3Diff >= LCounter) && (Leg3Diff < 0) )
			Leg3Turn--;

		if( (Leg4Diff >= LCounter) && (Leg4Diff > 0) )
			Leg4Turn++;
		else if( (-Leg4Diff >= LCounter) && (Leg4Diff < 0) )
			Leg4Turn--;

		if( (Leg5Diff >= LCounter) && (Leg5Diff > 0) )
			Leg5Turn++;
		else if( (-Leg5Diff >= LCounter) && (Leg5Diff < 0) )
			Leg5Turn--;

		if( (Leg6Diff >= LCounter) && (Leg6Diff > 0) )
			Leg6Turn++;
		else if( (-Leg6Diff >= LCounter) && (Leg6Diff < 0) )
			Leg6Turn--;


		delay_ms(Speed);
	}
}

void legLift(char WhichLeg, int Position, int Speed) //speed 0-9, position -50 to +80
{
	if(Speed>15) Speed = MAX_SPEED;
	if(Speed<0) Speed = 0;
	Speed = 2*(MAX_SPEED - Speed);

	int Leg1=0,Leg2=0,Leg3=0,Leg4=0,Leg5=0,Leg6=0;

	checkLegs(WhichLeg, &Leg1, &Leg2, &Leg3, &Leg4, &Leg5, &Leg6);

	if(Position<-50) Position = -50;
	if(Position>80) Position = 80;

	Position -= 40;
	int PositionL = Position;
	int PositionR = -PositionL; //mirror view

	int Leg1Diff=0,Leg2Diff=0,Leg3Diff=0,Leg4Diff=0,Leg5Diff=0,Leg6Diff=0;

	if(Leg1)
		Leg1Diff = (PositionL - (Leg1Lift-LEG1LIFT_BASE));
	if(Leg2)
		Leg2Diff = (PositionL - (Leg2Lift-LEG2LIFT_BASE));
	if(Leg3)
		Leg3Diff = (PositionR - (Leg3Lift-LEG3LIFT_BASE));
	if(Leg4)
		Leg4Diff = (PositionL - (Leg4Lift-LEG4LIFT_BASE));
	if(Leg5)
		Leg5Diff = (PositionR - (Leg5Lift-LEG5LIFT_BASE));
	if(Leg6)
		Leg6Diff = (PositionR - (Leg6Lift-LEG6LIFT_BASE));


	int MAXDiff=0;
	if( (Leg1Diff > MAXDiff) && (Leg1Diff > 0) )
		MAXDiff = Leg1Diff;
	else if( (-Leg1Diff > MAXDiff) && (Leg1Diff < 0) )
		MAXDiff = -Leg1Diff;

	if( (Leg2Diff > MAXDiff) && (Leg2Diff > 0) )
		MAXDiff = Leg2Diff;
	else if( (-Leg2Diff > MAXDiff) && (Leg2Diff < 0) )
		MAXDiff = -Leg2Diff;

	if( (Leg3Diff > MAXDiff) && (Leg3Diff > 0) )
		MAXDiff = Leg3Diff;
	else if( (-Leg3Diff > MAXDiff) && (Leg3Diff < 0) )
		MAXDiff = -Leg3Diff;

	if( (Leg4Diff > MAXDiff) && (Leg4Diff > 0) )
		MAXDiff = Leg4Diff;
	else if( (-Leg4Diff > MAXDiff) && (Leg4Diff < 0) )
		MAXDiff = -Leg4Diff;

	if( (Leg5Diff > MAXDiff) && (Leg5Diff > 0) )
		MAXDiff = Leg5Diff;
	else if( (-Leg5Diff > MAXDiff) && (Leg5Diff < 0) )
		MAXDiff = -Leg5Diff;

	if( (Leg6Diff > MAXDiff) && (Leg6Diff > 0) )
		MAXDiff = Leg6Diff;
	else if( (-Leg6Diff > MAXDiff) && (Leg6Diff < 0) )
		MAXDiff = -Leg6Diff;
	//mamy +maxDiff


	int LCounter=1;
	for(LCounter=MAXDiff; LCounter>=1; LCounter--)
	{
		if( (Leg1Diff >= LCounter) && (Leg1Diff > 0) )
			Leg1Lift++;
		else if( (-Leg1Diff >= LCounter) && (Leg1Diff < 0) )
			Leg1Lift--;

		if( (Leg2Diff >= LCounter) && (Leg2Diff > 0) )
			Leg2Lift++;
		else if( (-Leg2Diff >= LCounter) && (Leg2Diff < 0) )
			Leg2Lift--;

		if( (Leg3Diff >= LCounter) && (Leg3Diff > 0) )
			Leg3Lift++;
		else if( (-Leg3Diff >= LCounter) && (Leg3Diff < 0) )
			Leg3Lift--;

		if( (Leg4Diff >= LCounter) && (Leg4Diff > 0) )
			Leg4Lift++;
		else if( (-Leg4Diff >= LCounter) && (Leg4Diff < 0) )
			Leg4Lift--;

		if( (Leg5Diff >= LCounter) && (Leg5Diff > 0) )
			Leg5Lift++;
		else if( (-Leg5Diff >= LCounter) && (Leg5Diff < 0) )
			Leg5Lift--;

		if( (Leg6Diff >= LCounter) && (Leg6Diff > 0) )
			Leg6Lift++;
		else if( (-Leg6Diff >= LCounter) && (Leg6Diff < 0) )
			Leg6Lift--;


		delay_ms(Speed);
	}
}

void checkLegs(char WhichLeg, int *Leg1, int *Leg2, int *Leg3, int *Leg4, int *Leg5, int *Leg6)
{
	if(WhichLeg & 0b00100000)
		*Leg1 = 1;
	if(WhichLeg & 0b00010000)
		*Leg2 = 1;
	if(WhichLeg & 0b00001000)
		*Leg3 = 1;
	if(WhichLeg & 0b00000100)
		*Leg4 = 1;
	if(WhichLeg & 0b00000010)
		*Leg5 = 1;
	if(WhichLeg & 0b00000001)
		*Leg6 = 1;


	if(*Leg1)
		LED_LEG1_ON;
	else
		LED_LEG1_OFF;
	if(*Leg2)
		LED_LEG2_ON;
	else
		LED_LEG2_OFF;
	if(*Leg3)
		LED_LEG3_ON;
	else
		LED_LEG3_OFF;
	if(*Leg4)
		LED_LEG4_ON;
	else
		LED_LEG4_OFF;
	if(*Leg5)
		LED_LEG5_ON;
	else
		LED_LEG5_OFF;
	if(*Leg6)
		LED_LEG6_ON;
	else
		LED_LEG6_OFF;
}


#endif /* SERWO_H_ */
