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
			while( legLift(Leg, 35, 13) != DONE );
			while( legTurn(Leg, 0, 13, 0, 1) != DONE );
			while( legLift(Leg, 0, 13) != DONE );
		}
	}

	Step = 0;
}

void curveAdjust(int *Curve) // 0 to 28
{
	*Curve -= 14;

	switch(*Curve)
	{
	case -14: {
		*Curve = -56;
		break;
	}
	case -13: {
		*Curve = -28;
		break;
	}
	case -12: {
		*Curve = -28;
		break;
	}
	case -11: {
		*Curve = -24;
		break;
	}
	case -10: {
		*Curve = -20;
		break;
	}
	case -9: {
		*Curve = -18;
		break;
	}
	case -8: {
		*Curve = -16;
		break;
	}
	case -7: {
		*Curve = -14;
		break;
	}
	case -6: {
		*Curve = -12;
		break;
	}
	case -5: {
		*Curve = -10;
		break;
	}
	case -4: {
		*Curve = -8;
		break;
	}
	case -3: {
		*Curve = -6;
		break;
	}
	case -2: {
		*Curve = -4;
		break;
	}
	case -1: {
		*Curve = -2;
		break;
	}
	case 0: {
		*Curve = 0;
		break;
	}
	case 1: {
		*Curve = 2;
		break;
	}
	case 2: {
		*Curve = 4;
		break;
	}
	case 3: {
		*Curve = 6;
		break;
	}
	case 4: {
		*Curve = 8;
		break;
	}
	case 5: {
		*Curve = 10;
		break;
	}
	case 6: {
		*Curve = 12;
		break;
	}
	case 7: {
		*Curve = 14;
		break;
	}
	case 8: {
		*Curve = 16;
		break;
	}
	case 9: {
		*Curve = 18;
		break;
	}
	case 10: {
		*Curve = 20;
		break;
	}
	case 11: {
		*Curve = 24;
		break;
	}
	case 12: {
		*Curve = 28;
		break;
	}
	case 13: {
		*Curve = 28;
		break;
	}
	case 14: {
		*Curve = 56;
		break;
	}
	default: {
		*Curve = 0;
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
		if( legLift(0b101010, 25, Speed) == DONE )
			Step = 12;
	}

	else if((Step == 12) && (Direction == 1) ) {
		if( legTurn(0b111111, -28, Speed, Curve, Direction) == DONE )
			Step = 13;
	}
	else if((Step == 12) && (Direction == 2) ) {
		if( legTurn(0b111111, 28, Speed, Curve, Direction) == DONE )
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

	else if( (Step == 15) && (Direction == 1) ) {
		if(	legTurn(0b111111, 28, Speed, Curve, Direction) == DONE )
			Step = 16;
	}
	else if( (Step == 15) && (Direction == 2) ) {
		if(	legTurn(0b111111, -28, Speed, Curve, Direction) == DONE )
			Step = 16;
	}

	else if(Step == 16) {
		if( legLift(0b010101, 0, Speed) == DONE )
			Step = 11;
	}
}

#endif /* MOVEMENT_H_ */
