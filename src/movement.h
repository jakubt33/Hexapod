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
		if( (legLift(Leg, 0, MAX_SPEED) != DONE) || (legTurn(Leg, 0, MAX_SPEED, NO_CURVE) != DONE) )
		{
			while( legLift(Leg, 35, Speed) != DONE );
			while( legTurn(Leg, 0, Speed, NO_CURVE) != DONE );
			while( legLift(Leg, 0, Speed) != DONE );
		}
	}
}


void goAhead(int Speed, int Curve)
{
	if(Speed>14) Speed = 14;

	if( (Step < 11) || (Step > 16) ) //it means that different action was previously done
		Step = 11;

	int Direction = 1;

	if(Step == 11) {
		if( legLift(0b101010, 25, Speed) == DONE )
			Step = 12;
	}
	else if(Step == 12) {
		if( legTurn(0b111111, -28, Speed, Curve) == DONE )
			Step = 13;
	}
	else if(Step == 13) {
		if( legLift(0b101010, 0, Speed) == DONE )
			Step = 14;
	}
	else if(Step == 14) {
		if(	legLift(0b010101, 25, Speed) == DONE )
			Step = 15;
	}
	else if(Step == 15) {
		if(	legTurn(0b111111, 28, Speed, Curve) == DONE )
			Step = 16;
	}
	else if(Step == 16) {
		if( legLift(0b010101, 0, Speed) == DONE )
			Step = 11;
	}
}

void goBack(int Speed, int Curve)
{
	if(Speed>14) Speed = 14;

	if( (Step < 21) || (Step > 26) ) //it means that different action was previously done
		Step = 21;

	int Direction = 2;

	if(Step == 21)
		if( legLift(0b101010, 25, Speed) == DONE )
			Step = 22;
	if(Step == 22)
		if( legTurn(0b111111, 28, Speed, Curve) == DONE )
			Step = 23;
	if(Step == 23)
		if( legLift(0b101010, 0, Speed) == DONE )
			Step = 24;

	if(Step == 24)
		if( legLift(0b010101, 25, Speed) == DONE )
			Step = 25;
	if(Step == 25)
		if( legTurn(0b111111, -28, Speed, Curve) == DONE )
			Step = 26;
	if(Step == 26)
		if( legLift(0b010101, 0, Speed) == DONE )
			Step = 21;
}


#endif /* MOVEMENT_H_ */
