/*
 * Game.cpp
 *
 *  Created on: 26.09.2014 ã.
 *      Author: Miroslav Avramov
 */

#include "Game.h"

Game::Game() {
	// TODO Auto-generated constructor stub

}

Game::~Game() {
	// TODO Auto-generated destructor stub
}

void Game::GetCardFromDeck() {
	m_newDeck.Init();
	m_newDeck.Shuffle();
	for (int iter = 0; iter < 4; iter++)
	{

		m_temp = m_newDeck.getCard();
		m_cardSet.push_back(m_temp);
		m_cardSet.push_back(m_temp);

		srand(time(NULL));
		random_shuffle(m_cardSet.begin(), m_cardSet.end());
	}
}
