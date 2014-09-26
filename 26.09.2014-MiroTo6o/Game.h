/*
 * Game.h
 *
 *  Created on: 26.09.2014 ã.
 *      Author: Miroslav Avramov
 */

#ifndef GAME_H_
#define GAME_H_
#include <SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <string>
#include <iostream>
#include <ctime>
#include "DeckOfCards.h"
#include "Card.h"

class Game {
public:
	Game();
	virtual ~Game();
	void Init(SDL_Renderer*);
	void Draw(SDL_Renderer*);
	void UpDate(SDL_Event);
	void GetCardFromDeck();
private:
	vector<Card> m_cardSet;
	DeckOfCards m_newDeck;
	Card m_temp;

};

#endif /* GAME_H_ */
