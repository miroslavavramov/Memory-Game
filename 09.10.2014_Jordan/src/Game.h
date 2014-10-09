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
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include <string>
#include <iostream>
#include <ctime>
#include <set>
#include "DeckOfCards.h"
#include "Card.h"
#include "BackgroundTexture.h"
#include "GameStart.h"
#include "logicCards.h"
#include "Button.h"
#include "Timer.h"
#include "Text.h"
#include "Card.h"
#include "Statistics.h"
using namespace std;

class Game {
	friend class Buttons;
public:
	Game();
	virtual ~Game();
//	void Init(SDL_Renderer*);

	bool Init(const char*, int, int, int, int, int);
//	void InitMenu(gameStates);
	void drawMenu();
	void updateMenu();
	void Draw();
	void Update();
	void GetCardFromDeck();
	bool Running();
	void compareCard();

//private:
	SDL_Window* m_pWindow;
	SDL_Renderer* m_pRenderer;

	vector<Card> m_cardSet;
	set<int> m_TwoCard;
	set<int>::iterator m_Begin;
	set<int>::iterator m_End;
	DeckOfCards m_newDeck;
	Card m_temp;
	Button m_Play;
	Button m_Bet;
	Button m_WIN;
	Button m_Menu;
	Button m_Credits;

	BackgroundTexture texture;
	GameStart m_StartGameMenu;
	logicCards m_cardLogic;
//	gameStates m_currentGameStates;
	SDL_Event e;
	bool m_bRunning;
	Timer m_Timer;

	int m_GameLevel;
	int m_RightGuesses;
	Statistics m_stat;

	Text txt;
	Text level;
	Text txtGameOver;

	Text bet;
	Text credit;
	Text profit;

};

#endif /* GAME_H_ */
