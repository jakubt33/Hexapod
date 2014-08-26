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
	if(Speed<1) Speed = 8;
	if(Speed>13) Speed = 13;


	char Leg=0;

	for(Leg=0b00000001; Leg<=0b00100000; Leg*=2)
	{
		if( (legLift(Leg, 0, MAX_SPEED) != DONE) || (legTurn(Leg, 0, MAX_SPEED, 0) != DONE) )
		{
			while( legLift(Leg, 35, Speed) != DONE );
			while( legTurn(Leg, 0, Speed, 0) != DONE );
			while( legLift(Leg, 0, Speed) != DONE );
		}
	}
}


void goAhead(int Speed)
{
	if(Speed>14) Speed = 14;

	if( (Step < 11) || (Step > 16) ) //it means that different action was previously done
		Step = 10;


	if(Step == 10)
	{
		//basePosition(8);
		Step = 11;
	}

	if(Step == 11)
		if( legLift(0b101010, 25, Speed) == DONE )
			Step = 12;
	if(Step == 12)
		if( legTurn(0b111111, -25, Speed, 1) == DONE )
			Step = 13;
	if(Step == 13)
		if( legLift(0b101010, 0, Speed) == DONE )
			Step = 14;

	if(Step == 14)
		if(	legLift(0b010101, 25, Speed) == DONE )
			Step = 15;
	if(Step == 15)
		if(	legTurn(0b111111, 25, Speed, 1) == DONE )
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
		//basePosition(8);
		Step = 21;
	}

	if(Step == 21)
		if( legLift(0b101010, 25, Speed) == DONE )
			Step = 22;
	if(Step == 22)
		if( legTurn(0b111111, 25, Speed, 1) == DONE )
			Step = 23;
	if(Step == 23)
		if( legLift(0b101010, 0, Speed) == DONE )
			Step = 24;

	if(Step == 24)
		if( legLift(0b010101, 25, Speed) == DONE )
			Step = 25;
	if(Step == 25)
		if( legTurn(0b111111, -25, Speed, 1) == DONE )
			Step = 26;
	if(Step == 26)
		if( legLift(0b010101, 0, Speed) == DONE )
			Step = 21;
}

void turnLeft(int Speed)
{
	if(Speed>14) Speed = 14;
	legLift(0b010101, 25, Speed);
	legTurn(0b111111, 25, Speed, 0);
	legLift(0b010101, 0, Speed);

	legLift(0b101010, 25, Speed);  //135
	legTurn(0b111111, -25, Speed, 0); //246
	legLift(0b101010, 0, Speed);
}

void turnRight(int Speed)
{
	if(Speed>14) Speed = 14;
	legLift(0b101010, 25, Speed);  //135
	legTurn(0b111111, 25, Speed, 0); //246
	legLift(0b101010, 0, Speed);

	legLift(0b010101, 25, Speed);
	legTurn(0b111111, -25, Speed, 0);
	legLift(0b010101, 0, Speed);
}

void goLeft(int Speed)
{

}

void goRight(int Speed)
{

}

#endif /* MOVEMENT_H_ */
