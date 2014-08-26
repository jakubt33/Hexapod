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
	legLift(0b000001, 35, Speed);
	legTurn(0b000001, 0, Speed, 0);
	legLift(0b000001, 0, Speed);

	legLift(0b000010, 35, Speed);
	legTurn(0b000010, 0, Speed, 0);
	legLift(0b000010, 0, Speed);

	legLift(0b000100, 35, Speed);
	legTurn(0b000100, 0, Speed, 0);
	legLift(0b000100, 0, Speed);

	legLift(0b001000, 35, Speed);
	legTurn(0b001000, 0, Speed, 0);
	legLift(0b001000, 0, Speed);

	legLift(0b010000, 35, Speed);
	legTurn(0b010000, 0, Speed, 0);
	legLift(0b010000, 0, Speed);

	legLift(0b100000, 35, Speed);
	legTurn(0b100000, 0, Speed, 0);
	legLift(0b100000, 0, Speed);

}


void goAhead(int Speed)
{
	if(Speed>14) Speed = 14;

	if( (Step < 11) || (Step > 16) ) //it means that different action was previously done
		Step = 10;


	if(Step == 10)
	{
		basePosition(8);
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

	legLift(0b101010, 25, Speed);  //135
	legTurn(0b111111, 25, Speed, 1); //246
	legLift(0b101010, 0, Speed);

	legLift(0b010101, 25, Speed);
	legTurn(0b111111, -25, Speed, 1);
	legLift(0b010101, 0, Speed);
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
