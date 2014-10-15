/*
 * Game.h
 *
 *  Created on: Sep 27, 2014
 *      Author: Todor
 */

#ifndef GAME_H_
#define GAME_H_

#include <string>
#include <iostream>
#include <ctime>
#include <set>
#include "DeckOfCards.h"
#include "StartBackgroundTexture.h"
#include "logicCards.h"
#include "Buttons.h"
#include "Timer.h"
#include "Text.h"
#include "Card.h"
#include "Statistics.h"
#include "Recovery.h"

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

private:
	SDL_Window* m_pWindow;
	SDL_Renderer* m_pRenderer;
	SDL_Texture* m_BackGroundTexture;

	DeckOfCards m_newDeck;
	Card m_temp;

	Buttons m_buttonsMenu;
	vector<Buttons> m_buttonSet;
	Buttons PlayButton;

	logicCards m_cardLogic;
	StartBackgroundTexture StartMenu;

	SDL_Event e;
	bool m_bRunning;
	Timer m_Timer;

	int m_GameLevel;
	int m_RightGuesses;
	Statistics m_stat;

	Text txt;
	Text level;

	Text bet;
	Text credit;
	Text profit;

	Recovery m_Recovery;

};

#endif /* GAME_H_ */
