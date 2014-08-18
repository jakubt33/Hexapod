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
	legTurn(123456, 0, Speed);
	legLift(123456, 0, Speed);
}

void goAhead(int Speed)
{
	legLift(135, 25, Speed);
	delay_ms(100);
	legTurn(246, -25, Speed);
	legTurn(135, 25, Speed);
	delay_ms(100);
	legLift(135, 0, Speed);
	delay_ms(100);

	legLift(246, 25, Speed);
	delay_ms(100);
	legTurn(135, -25, Speed);
	legTurn(246, 25, Speed);
	delay_ms(100);
	legLift(246, 0, Speed);
	delay_ms(100);
}

#endif /* MOVEMENT_H_ */
