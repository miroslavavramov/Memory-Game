/*
 * Card.h
 *
 *  Created on: Sep 16, 2014
 *      Author: Todor
 */

#ifndef CARD_H_
#define CARD_H_
#include "SDL.h"
#include <SDL2/SDL_image.h>
#include <iostream>
using namespace std;

const int CARD_WIDTH = 79;
const int CARD_HEIGHT = 123;
class Card {
public:
	Card();
	virtual ~Card();
	int face;
	int suit;
	int state;
 void Init(SDL_Renderer*);
 void Draw(SDL_Renderer*);
 const SDL_Rect& getDestination() const;
 void setDestination(int x_dest, int y_dest);
 void UpDate(SDL_Event);
private:
 SDL_Renderer* m_r;
 SDL_Texture* m_t;
 SDL_Rect m_source;
 SDL_Rect m_destination;

};

#endif /* CARD_H_ */
