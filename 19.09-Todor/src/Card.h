/*
 * Card.h
 *
 *  Created on: Sep 16, 2014
 *      Author: Todor
 */

#ifndef CARD_H_
#define CARD_H_
#include <SDL.h>
#include "Texture.h"

class Card {
public:
	Card();
	virtual ~Card();
	void Draw(int x, int y, SDL_Rect* clip, SDL_Renderer* temp, Texture a);

/*	void Init( SDL_Renderer* temp);*/
	int face;
	int suit;
	int state;
};

#endif /* CARD_H_ */
