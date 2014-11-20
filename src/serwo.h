/*
 * serwo.h
 *
 *  Created on: Aug 1, 2014
 *      Author: Jakub Trzyna
 */

#ifndef SERWO_H_
#define SERWO_H_

#define MAX_SPEED 15
#define TIME_TO_GET_50HZ 630 //2000

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


#define LEG1LIFT_BASE 48 //145   //   !! prievious x*2 !!
#define LEG2LIFT_BASE 50 //150
#define LEG3LIFT_BASE 44 //150
#define LEG4LIFT_BASE 47 //140
#define LEG5LIFT_BASE 47 //140
#define LEG6LIFT_BASE 50 //150

#define LEG1TURN_BASE 50 //150
#define LEG2TURN_BASE 50 //160
#define LEG3TURN_BASE 60 //170
#define LEG4TURN_BASE 44 //150
#define LEG5TURN_BASE 50 //165
#define LEG6TURN_BASE 50 //165


volatile long int Counter = 0;

volatile int Step = 0;

//steering:
//up: L1,L2,L4 +40, L3,L5,L6 -40
//down: L1,L2,L4 -90, L3,L5,L6 +90
volatile  int Leg1Lift = LEG1LIFT_BASE-13; // !!previous: +- 40 !!
volatile  int Leg2Lift = LEG2LIFT_BASE-13;
volatile  int Leg3Lift = LEG3LIFT_BASE+13;
volatile  int Leg4Lift = LEG4LIFT_BASE-13;
volatile  int Leg5Lift = LEG5LIFT_BASE+13;
volatile  int Leg6Lift = LEG6LIFT_BASE+13;

volatile  int Leg1Turn = LEG1TURN_BASE;
volatile  int Leg2Turn = LEG2TURN_BASE;
volatile  int Leg3Turn = LEG3TURN_BASE;
volatile  int Leg4Turn = LEG4TURN_BASE;
volatile  int Leg5Turn = LEG5TURN_BASE;
volatile  int Leg6Turn = LEG6TURN_BASE;

void checkLegs(char WhichLeg, int *Leg1, int *Leg2, int *Leg3, int *Leg4, int *Leg5, int *Leg6);
void TIM2_IRQHandler();

u8 legLift(char WhichLeg, int Position, int Speed);
u8 legTurn(char WhichLeg, int Position, int Speed, int Curve, u8 Direction);

void TIM2_IRQHandler()
{
	TIM_ClearFlag(TIM2, TIM_FLAG_Update);

	if( (!Counter) && (PowerON) && (!BatteryDischarged) )
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

u8 legTurn(char WhichLeg, int Position, int Speed, int Curve, u8 Direction)
{
	if(Speed>15) Speed = MAX_SPEED;
	if(Speed<0) Speed = 0;
	Speed = (MAX_SPEED - Speed);
	delay_ms(Speed);

	if(Position<-11) Position = -11;  //32
	else if(Position>11) Position = 11;

	int Leg1=0,Leg2=0,Leg3=0,Leg4=0,Leg5=0,Leg6=0;

	checkLegs(WhichLeg, &Leg1, &Leg2, &Leg3, &Leg4, &Leg5, &Leg6);

	//serwo 2 has got electric motor connected inversely!!! thats why "-" has to be before Position 2
	int Position1 = Position;
	int Position2 = -Position;
	int Position3 = Position;
	int Position4 = -Position;
	int Position5 = -Position;
	int Position6 = -Position;

	if( ((Curve<=0) && (Direction == 1)) || ((Curve>=0) && (Direction == 2)) )
	{
		if( ((Position>=0) && (Direction == 1)) || ((Position<=0) && (Direction == 2)) )
				Curve = -Curve;

		Position1 = -Position+Curve;//+Position: Turning
		Position2 = -Position+Curve;//+
		Position3 = -Position+Curve;//+
		Position4 = -Position;
		Position5 = Position;
		Position6 = -Position;

	}
	else if( ((Curve>0) && (Direction == 1)) || ((Curve<0) && (Direction == 2)) )
	{
		if( ((Position<0) && (Direction == 1)) || ((Position>0) && (Direction == 2)) )
			Curve = -Curve;

		Position1 = -Position;
		Position2 = -Position;
		Position3 = -Position;
		Position4 = -Position+Curve;
		Position5 = Position-Curve;
		Position6 = -Position+Curve;

	}



	u8 Flag = DONE;
	if(Leg1)
	{
		if(Position1+LEG1TURN_BASE>Leg1Turn)
		{
			Leg1Turn++;
			Flag = 0;
		}
		else if(Position1+LEG1TURN_BASE<Leg1Turn)
		{
			Leg1Turn--;
			Flag = 0;
		}
	}
	if(Leg2)
	{
		if(Position2+LEG2TURN_BASE>Leg2Turn)
		{
			Leg2Turn++;
			Flag = 0;
		}
		else if(Position2+LEG2TURN_BASE<Leg2Turn)
		{
			Leg2Turn--;
			Flag = 0;
		}
	}
	if(Leg3)
	{
		if(Position3+LEG3TURN_BASE>Leg3Turn)
		{
			Leg3Turn++;
			Flag = 0;
		}
		else if(Position3+LEG3TURN_BASE<Leg3Turn)
		{
			Leg3Turn--;
			Flag = 0;
		}
	}
	if(Leg4)
	{
		if(Position4+LEG4TURN_BASE>Leg4Turn)
		{
			Leg4Turn++;
			Flag = 0;
		}
		else if(Position4+LEG4TURN_BASE<Leg4Turn)
		{
			Leg4Turn--;
			Flag = 0;
		}
	}
	if(Leg5)
	{
		if(Position5+LEG5TURN_BASE>Leg5Turn)
		{
			Leg5Turn++;
			Flag = 0;
		}
		else if(Position5+LEG5TURN_BASE<Leg5Turn)
		{
			Leg5Turn--;
			Flag = 0;
		}
	}
	if(Leg6)
	{
		if(Position6+LEG6TURN_BASE>Leg6Turn)
		{
			Leg6Turn++;
			Flag = 0;
		}
		else if(Position6+LEG6TURN_BASE<Leg6Turn)
		{
			Leg6Turn--;
			Flag = 0;
		}
	}

	return Flag;

}

u8 legLift(char WhichLeg, int Position, int Speed)
{
	if(Speed>15) Speed = MAX_SPEED;
	if(Speed<0) Speed = 0;
	Speed = (MAX_SPEED - Speed); //try without this multiplication by 2, change maxspeed to 16
	delay_ms(Speed);

	int Leg1=0,Leg2=0,Leg3=0,Leg4=0,Leg5=0,Leg6=0;

	checkLegs(WhichLeg, &Leg1, &Leg2, &Leg3, &Leg4, &Leg5, &Leg6);

	if(Position<-17) Position = -17; //50
	else if(Position>27) Position = 27; //80

	Position -= 13; //40
	int PositionL = Position;
	int PositionR = -PositionL; //mirror view


	u8 Flag = DONE;
	if(Leg1)
	{
		if(PositionL+LEG1LIFT_BASE>Leg1Lift)
		{
			Leg1Lift++;
			Flag = 0;
		}
		else if(PositionL+LEG1LIFT_BASE<Leg1Lift)
		{
			Leg1Lift--;
			Flag = 0;
		}
	}
	if(Leg2)
	{
		if(PositionL+LEG2LIFT_BASE>Leg2Lift)
		{
			Leg2Lift++;
			Flag = 0;
		}
		else if(PositionL+LEG2LIFT_BASE<Leg2Lift)
		{
			Leg2Lift--;
			Flag = 0;
		}
	}
	if(Leg3)
	{
		if(PositionR+LEG3LIFT_BASE>Leg3Lift)
		{
			Leg3Lift++;
			Flag = 0;
		}
		else if(PositionR+LEG3LIFT_BASE<Leg3Lift)
		{
			Leg3Lift--;
			Flag = 0;
		}
	}
	if(Leg4)
	{
		if(PositionL+LEG4LIFT_BASE>Leg4Lift)
		{
			Leg4Lift++;
			Flag = 0;
		}
		else if(PositionL+LEG4LIFT_BASE<Leg4Lift)
		{
			Leg4Lift--;
			Flag = 0;
		}
	}
	if(Leg5)
	{
		if(PositionR+LEG5LIFT_BASE>Leg5Lift)
		{
			Leg5Lift++;
			Flag = 0;
		}
		else if(PositionR+LEG5LIFT_BASE<Leg5Lift)
		{
			Leg5Lift--;
			Flag = 0;
		}
	}
	if(Leg6)
	{
		if(PositionR+LEG6LIFT_BASE>Leg6Lift)
		{
			Leg6Lift++;
			Flag = 0;
		}
		else if(PositionR+LEG6LIFT_BASE<Leg6Lift)
		{
			Leg6Lift--;
			Flag = 0;
		}
	}

	return Flag;
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
