/*
 * Game.h
 *
 *  Created on: Sep 27, 2014
 *      Author: Todor
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
#include "BackgroundTexture.h"
using namespace std;

class Game {
public:
	Game();
	virtual ~Game();
//	void Init(SDL_Renderer*);

	bool Init(const char*, int, int, int, int,
			int);
	void Draw();
	void Update();
	void GetCardFromDeck();
	bool Running();
	void compareCard();

private:
	SDL_Window* m_pWindow;
	SDL_Renderer* m_pRenderer;

	vector<Card> m_cardSet;
	vector<int> m_TwoCard;
	DeckOfCards m_newDeck;
	Card m_temp;

	BackgroundTexture texture;
	bool m_bRunning;

};

#endif /* GAME_H_ */
