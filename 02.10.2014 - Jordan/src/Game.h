/*
 * Game.h
 *
 *  Created on: Sep 27, 2014
 *      Author: Todor
 */


#ifndef GAME_H_
#define GAME_H_
#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>
#include <iostream>
#include <ctime>
#include <set>
//#include <iterator>
#include "DeckOfCards.h"
#include "Card.h"
#include "BackgroundTexture.h"
#include "GameStart.h"
using namespace std;

enum gameStates{

	MENU = 0,
	STARTGAME = 1,
	GAMEOVER = 2,
	RECOVERY = 3

};

class Game {
public:
	Game();
	virtual ~Game();
//	void Init(SDL_Renderer*);

	bool Init(const char*, int, int, int, int,
			int);
	void InitMenu(gameStates);
	void drawMenu();
	void updateMenu();
	void Draw();
	void Update();
	void GetCardFromDeck();
	bool Running();
	void compareCard();

private:
	SDL_Window* m_pWindow;
	SDL_Renderer* m_pRenderer;

	vector<Card> m_cardSet;
	set<int> m_TwoCard;
	set<int>::iterator m_Begin;
	set<int>::iterator m_End;
	DeckOfCards m_newDeck;
	Card m_temp;

	BackgroundTexture texture;
	GameStart m_StartGameMenu;
	gameStates m_currentGameStates;
	SDL_Event e;
	bool m_bRunning;

};

#endif /* GAME_H_ */
