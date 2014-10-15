/*
 * Card.h
 *
 *  Created on: Sep 16, 2014
 *      Author: Todor
 */

#ifndef CARD_H_
#define CARD_H_

class Card {
public:
	Card();
	virtual ~Card();
	int face;
	int suit;
	int state;
};

#endif /* CARD_H_ */
