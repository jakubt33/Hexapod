/*
 * movement.h
 *
 *  Created on: Aug 18, 2014
 *      Author: Jakub Trzyna
 */

#ifndef MOVEMENT_H_
#define MOVEMENT_H_


void basePosition(int Speed)
{
	Speed = 13;

	char Leg=0;

	for(Leg=0b00000001; Leg<=0b00100000; Leg*=2)
	{
		if( (legLift(Leg, 0, MAX_SPEED) != DONE) || (legTurn(Leg, 0, MAX_SPEED, -1) != DONE) )
		{
			while( legLift(Leg, 35, Speed) != DONE );
			while( legTurn(Leg, 0, Speed, -1) != DONE );
			while( legLift(Leg, 0, Speed) != DONE );
		}
	}
}


void goAhead(int Speed, int Curve)
{
	if(Speed>14) Speed = 14;

	if( (Step < 11) || (Step > 16) ) //it means that different action was previously done
		Step = 10;


	if(Step == 10)
	{
		basePosition(14);
		Step = 11;
	}

	if(Step == 11)
		if( legLift(0b101010, 25, Speed) == DONE )
			Step = 12;
	if(Step == 12)
		if( legTurn(0b111111, -28, Speed, Curve) == DONE )
			Step = 13;
	if(Step == 13)
		if( legLift(0b101010, 0, Speed) == DONE )
			Step = 14;

	if(Step == 14)
		if(	legLift(0b010101, 25, Speed) == DONE )
			Step = 15;
	if(Step == 15)
		if(	legTurn(0b111111, 28, Speed, Curve) == DONE )
			Step = 16;
	if(Step == 16)
		if( legLift(0b010101, 0, Speed) == DONE )
			Step = 11;
}

void goBack(int Speed)
{
	if(Speed>14) Speed = 14;

	if( (Step < 21) || (Step > 26) ) //it means that different action was previously done
		Step = 20;


	if(Step == 20)
	{
		basePosition(14);
		Step = 21;
	}

	if(Step == 21)
		if( legLift(0b101010, 25, Speed) == DONE )
			Step = 22;
	if(Step == 22)
		if( legTurn(0b111111, 25, Speed, 0) == DONE )
			Step = 23;
	if(Step == 23)
		if( legLift(0b101010, 0, Speed) == DONE )
			Step = 24;

	if(Step == 24)
		if( legLift(0b010101, 25, Speed) == DONE )
			Step = 25;
	if(Step == 25)
		if( legTurn(0b111111, -25, Speed, 0) == DONE )
			Step = 26;
	if(Step == 26)
		if( legLift(0b010101, 0, Speed) == DONE )
			Step = 21;
}

void turnLeft(int Speed)
{
	if(Speed>14) Speed = 14;

	if( (Step < 31) || (Step > 36) ) //it means that different action was previously done
		Step = 30;


	if(Step == 30)
	{
		basePosition(14);
		Step = 31;
	}

	if(Step == 31)
		if( legLift(0b010101, 25, Speed) == DONE )
			Step = 32;
	if(Step == 32)
		if( legTurn(0b111111, 25, Speed, 2) == DONE )
			Step = 33;
	if(Step == 33)
		if( legLift(0b010101, 0, Speed) == DONE )
			Step = 34;

	if(Step == 34)
		if( legLift(0b101010, 25, Speed) == DONE )
			Step = 35;
	if(Step == 35)
		if( legTurn(0b111111, -25, Speed, 2) == DONE )
			Step = 36;
	if(Step == 36)
		if( legLift(0b101010, 0, Speed) == DONE )
			Step = 31;
}

void turnRight(int Speed)
{
	if(Speed>14) Speed = 14;

	if( (Step < 41) || (Step > 46) ) //it means that different action was previously done
		Step = 40;


	if(Step == 40)
	{
		basePosition(14);
		Step = 41;
	}

	if(Step == 41)
		if( legLift(0b101010, 25, Speed) == DONE )
			Step = 42;
	if(Step == 42)
		if( legTurn(0b111111, 25, Speed, 2) == DONE )
			Step = 43;
	if(Step == 43)
		if( legLift(0b101010, 0, Speed) == DONE )
			Step = 44;

	if(Step == 44)
		if( legLift(0b010101, 25, Speed) == DONE )
			Step = 45;
	if(Step == 45)
		if( legTurn(0b111111, -25, Speed, 2) == DONE )
			Step = 46;
	if(Step == 46)
		if( legLift(0b010101, 0, Speed) == DONE )
			Step = 41;
}

void goLeft(int Speed)
{
	if(Speed>14) Speed = 14;

	if( (Step < 61) || (Step > 66) ) //it means that different action was previously done
		Step = 60;


	if(Step == 60)
	{
		basePosition(14);
		Step = 61;
	}

	if(Step == 61)
		if( legLift(0b101010, 25, Speed) == DONE )
			Step = 62;
	if(Step == 62)
		if( legTurn(0b111111, 25, Speed, 1) == DONE )
			Step = 63;
	if(Step == 63)
		if( legLift(0b101010, 0, Speed) == DONE )
			Step = 64;

	if(Step == 64)
		if( legLift(0b010101, 25, Speed) == DONE )
			Step = 65;
	if(Step == 65)
		if( legTurn(0b111111, -25, Speed, 1) == DONE )
			Step = 66;
	if(Step == 66)
		if( legLift(0b010101, 0, Speed) == DONE )
			Step = 61;
}

void turn(int Speed, int Curve)
{
	if(Speed>14) Speed = 14;

	if(Curve<0)
		turnLeft(Speed);
	else if(Curve>0)
		turnRight(Speed);

}

#endif /* MOVEMENT_H_ */
