/*
 * movement.h
 *
 *  Created on: Aug 18, 2014
 *      Author: Jakub Trzyna
 */

#ifndef MOVEMENT_H_
#define MOVEMENT_H_


void basePosition()
{
	char Leg=0;

	for(Leg=0b00000001; Leg<=0b00100000; Leg*=2)
	{
		if( (legLift(Leg, 0, MAX_SPEED) != DONE) || (legTurn(Leg, 0, MAX_SPEED, 0, 1) != DONE) )
		{
			while( legLift(Leg, 13, 11) != DONE ); //(Leg, 38, 11)
			while( legTurn(Leg, 0, 11, 0, 1) != DONE );
			while( legLift(Leg, 0, 11) != DONE );
		}
	}

	Step = 0;
}

void layDown() //protocol must be changed to handle this function
{
	while( legTurn(0b111111, 0, 13, 0, 0) != DONE );
	while( legLift(0b111111, 20, 13) != DONE );

}

void curveAdjust(int *Curve) // 0 to 28
{
	*Curve -= 14;

	switch(*Curve)
	{
	case -14: {
		*Curve = -19;//-56;
		break;
	}
	case -13: {
		*Curve = -19;//-28;
		break;
	}
	case -12: {
		*Curve = -10;//-28;
		break;
	}
	case -11: {
		*Curve = -10; //-24;
		break;
	}
	case -10: {
		*Curve = -9; //-24;
		break;
	}
	case 10: {
		*Curve = 9; //-24;
		break;
	}
	case 11: {
		*Curve = 10;//24;
		break;
	}
	case 12: {
		*Curve = 10;//28;
		break;
	}
	case 13: {
		*Curve = 19;//28;
		break;
	}
	case 14: {
		*Curve = 19;//56;
		break;
	}
	default: {
		break;
	}
	}
}

void go(int Speed, int Curve, int Direction)
{
	if(Speed>14) Speed = 14;

	if( (Step < 11) || (Step > 16) ) //it means that different action was previously done
	{
		basePosition();
		Step = 11;
	}


	if(Step == 11) {
		if( legLift(0b101010, 12, Speed) == DONE ) //45
			Step = 12;
	}

	else if((Step == 12) && (Direction == 1) ) {
		if( legTurn(0b111111, -9, Speed, Curve, Direction) == DONE ) //-28
			Step = 13;
	}
	else if((Step == 12) && (Direction == 2) ) {
		if( legTurn(0b111111, 9, Speed, Curve, Direction) == DONE ) //28
			Step = 13;
	}

	else if(Step == 13) {
		if( legLift(0b101010, 3, Speed) == DONE ) //15
			Step = 14;
	}


	else if(Step == 14) {
		if(	legLift(0b010101, 12, Speed) == DONE ) //45
			Step = 15;
	}

	else if( (Step == 15) && (Direction == 1) ) { //45
		if(	legTurn(0b111111, 9, Speed, Curve, Direction) == DONE ) //28
			Step = 16;
	}
	else if( (Step == 15) && (Direction == 2) ) { //45
		if(	legTurn(0b111111, -9, Speed, Curve, Direction) == DONE ) //28
			Step = 16;
	}

	else if(Step == 16) {
		if( legLift(0b010101, 3, Speed) == DONE ) //15
			Step = 11;
	}
}

#endif /* MOVEMENT_H_ */
