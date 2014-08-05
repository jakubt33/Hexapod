/*
 * serwo.h
 *
 *  Created on: Aug 1, 2014
 *      Author: Kuba
 */

#ifndef SERWO_H_
#define SERWO_H_

#define MAX_SPEED 3
#define TIME_TO_GET_50HZ 400

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
#define LEG2LIFT_OFF GPIO_ResetBits(GPIOB, GPIO_Pin_2)
#define LEG4LIFT_OFF GPIO_ResetBits(GPIOB, GPIO_Pin_5)
#define LEG5LIFT_OFF GPIO_ResetBits(GPIOB, GPIO_Pin_6)
#define LEG5TURN_OFF GPIO_ResetBits(GPIOB, GPIO_Pin_7)
#define LEG6LIFT_OFF GPIO_ResetBits(GPIOB, GPIO_Pin_8)
#define LEG6TURN_OFF GPIO_ResetBits(GPIOB, GPIO_Pin_9)
#define LEG2TURN_OFF GPIO_ResetBits(GPIOB, GPIO_Pin_12)
#define LEG3LIFT_OFF GPIO_ResetBits(GPIOB, GPIO_Pin_13)
#define LEG3TURN_OFF GPIO_ResetBits(GPIOB, GPIO_Pin_14)
#define LEG4TURN_OFF GPIO_ResetBits(GPIOB, GPIO_Pin_15)

#define LEG1TURN_ON GPIO_SetBits(GPIOB, GPIO_Pin_0)
#define LEG1LIFT_ON GPIO_SetBits(GPIOB, GPIO_Pin_1)
#define LEG2LIFT_ON GPIO_SetBits(GPIOB, GPIO_Pin_2)
#define LEG4LIFT_ON GPIO_SetBits(GPIOB, GPIO_Pin_5)
#define LEG5LIFT_ON GPIO_SetBits(GPIOB, GPIO_Pin_6)
#define LEG5TURN_ON GPIO_SetBits(GPIOB, GPIO_Pin_7)
#define LEG6LIFT_ON GPIO_SetBits(GPIOB, GPIO_Pin_8)
#define LEG6TURN_ON GPIO_SetBits(GPIOB, GPIO_Pin_9)
#define LEG2TURN_ON GPIO_SetBits(GPIOB, GPIO_Pin_12)
#define LEG3LIFT_ON GPIO_SetBits(GPIOB, GPIO_Pin_13)
#define LEG3TURN_ON GPIO_SetBits(GPIOB, GPIO_Pin_14)
#define LEG4TURN_ON GPIO_SetBits(GPIOB, GPIO_Pin_15)

#define FALSE 0
#define TRUE  1

volatile  int Leg1Lift = 30;
volatile  int Leg2Lift = 30;
volatile  int Leg3Lift = 30;
volatile  int Leg4Lift = 30;
volatile  int Leg5Lift = 30;
volatile  int Leg6Lift = 30;

void applyLegs(int x,int *Leg1,int *Leg2,int *Leg3,int *Leg4,int *Leg5,int *Leg6);
void legLift(int WhichLeg, int Position, int Speed);
void TIM2_IRQHandler();
void checkLiftLegs(int WhichLeg, int *Leg1, int *Leg2, int *Leg3, int *Leg4, int *Leg5, int *Leg6);
void checkLiftSpeed(int Speed, int PostionL, int PositionR, int *Leg1Diff, int *Leg2Diff, int *Leg3Diff, int *Leg4Diff, int *Leg5Diff, int *Leg6Diff);

void TIM2_IRQHandler()
{
	TIM_ClearFlag(TIM2, TIM_FLAG_Update);

	Counter++;

	if(Counter<Leg1Lift)
		LEG1LIFT_ON;
	else if(Counter<TIME_TO_GET_50HZ)
		LEG1LIFT_OFF;

	if(Counter<Leg2Lift)
		LEG2LIFT_ON;
	else if(Counter<TIME_TO_GET_50HZ)
		LEG2LIFT_OFF;

	if(Counter<Leg3Lift)
		LEG3LIFT_ON;
	else if(Counter<TIME_TO_GET_50HZ)
		LEG3LIFT_OFF;

	if(Counter<Leg4Lift)
		LEG4LIFT_ON;
	else if(Counter<TIME_TO_GET_50HZ)
		LEG4LIFT_OFF;

	if(Counter<Leg5Lift)
		LEG5LIFT_ON;
	else if(Counter<TIME_TO_GET_50HZ)
		LEG5LIFT_OFF;

	if(Counter<Leg6Lift)
		LEG6LIFT_ON;
	else if(Counter<TIME_TO_GET_50HZ)
		LEG6LIFT_OFF;

	if(Counter >= TIME_TO_GET_50HZ)
		Counter = 0;
}

void legLift(int WhichLeg, int Position, int Speed) //speed 1-3
{
	int Leg1=0,Leg2=0,Leg3=0,Leg4=0,Leg5=0,Leg6=0;

	checkLiftLegs(WhichLeg, &Leg1, &Leg2, &Leg3, &Leg4, &Leg5, &Leg6);


	int Leg1Diff=0,Leg2Diff=0,Leg3Diff=0,Leg4Diff=0,Leg5Diff=0,Leg6Diff=0;

	int PositionL = Position;
	int PositionR = Position - 2*(Position-30); //mirror view

	checkLiftSpeed(Speed, PositionL, PositionR, &Leg1Diff, &Leg2Diff, &Leg3Diff, &Leg4Diff, &Leg5Diff, &Leg6Diff);

	int SpeedCounter=0;
	for(SpeedCounter=Speed;SpeedCounter<=MAX_SPEED;SpeedCounter++)
	{
		if(Leg1)
			Leg1Lift += Leg1Diff;
		if(Leg2)
			Leg2Lift += Leg2Diff;
		if(Leg3)
			Leg3Lift += Leg3Diff;
		if(Leg4)
			Leg4Lift += Leg4Diff;
		if(Leg5)
			Leg5Lift += Leg5Diff;
		if(Leg6)
			Leg6Lift += Leg6Diff;

		delay_ms(50);
	}

}

void checkLiftSpeed(int Speed, int PositionL, int PositionR, int *Leg1Diff, int *Leg2Diff, int *Leg3Diff, int *Leg4Diff, int *Leg5Diff, int *Leg6Diff)
{
	Speed = MAX_SPEED+1 - Speed;
	*Leg1Diff = (PositionL - Leg1Lift)/Speed;
	*Leg2Diff = (PositionL - Leg2Lift)/Speed;
	*Leg3Diff = (PositionL - Leg3Lift)/Speed;
	*Leg4Diff = (PositionR - Leg4Lift)/Speed;
	*Leg5Diff = (PositionR - Leg5Lift)/Speed;
	*Leg6Diff = (PositionR - Leg6Lift)/Speed;
}

void checkLiftLegs(int WhichLeg, int *Leg1, int *Leg2, int *Leg3, int *Leg4, int *Leg5, int *Leg6)
{
	int x=0;
	x = WhichLeg%10;
	applyLegs(x,Leg1,Leg2,Leg3,Leg4,Leg5,Leg6);

	x = (WhichLeg%100)/10;
	applyLegs(x,Leg1,Leg2,Leg3,Leg4,Leg5,Leg6);

	x = (WhichLeg%1000)/100;
	applyLegs(x,Leg1,Leg2,Leg3,Leg4,Leg5,Leg6);

	x = (WhichLeg%10000)/1000;
	applyLegs(x,Leg1,Leg2,Leg3,Leg4,Leg5,Leg6);

	x = (WhichLeg%100000)/10000;
	applyLegs(x,Leg1,Leg2,Leg3,Leg4,Leg5,Leg6);

	x = (WhichLeg%1000000)/100000;
	applyLegs(x,Leg1,Leg2,Leg3,Leg4,Leg5,Leg6);
}

void applyLegs(int x,int *Leg1,int *Leg2,int *Leg3,int *Leg4,int *Leg5,int *Leg6)
{
	switch (x)
	{
	case 1:
		*Leg1 = 1;
		break;
	case 2:
		*Leg2 = 1;
		break;
	case 3:
		*Leg3 = 1;
		break;
	case 4:
		*Leg4 = 1;
		break;
	case 5:
		*Leg5 = 1;
		break;
	case 6:
		*Leg6 = 1;
		break;
	default:
		break;
	}
}

#endif /* SERWO_H_ */
