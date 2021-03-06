/*
 * logicCards.cpp
 *
 *  Created on: Oct 2, 2014
 *      Author: User
 */

#include "logicCards.h"
#include <iostream>

using namespace std;

logicCards::logicCards() {
	// TODO Auto-generated constructor stub

}

logicCards::~logicCards() {
	// TODO Auto-generated destructor stub
}

void logicCards::Init(SDL_Renderer* cardRender) {

	m_Cards.Init(cardRender);
	m_newDeck.Init();
	m_newDeck.Shuffle();

}

void logicCards::Draw(SDL_Renderer* cardRender)
{
//	SDL_RenderClear(m_pRenderer);
	for (int iter = 0; iter < 8; iter++)
	{
		m_cardSet[iter].Draw(cardRender);
	}

//	SDL_RenderPresent(m_pRenderer);
}

void logicCards::Update(SDL_Event event)
{
	for (int iter = 0; iter < 8; iter++) {
		m_cardSet[iter].Update(event);
	}
}

void logicCards::GetCardFromDeck() {
	m_cardSet.clear();

	for (int iter = 0; iter < 4; iter++) {

		Card temp = m_newDeck.getCard();
		m_Cards.face = temp.face;
		m_Cards.suit = temp.suit;

		m_Cards.m_source.x = CARD_WIDTH * m_Cards.face;
		m_Cards.m_source.y = CARD_HEIGHT * m_Cards.suit;
		m_Cards.m_source.h = CARD_HEIGHT;
		m_Cards.m_source.w = CARD_WIDTH;

		m_cardSet.push_back(m_Cards);
		m_cardSet.push_back(m_Cards);
	}

	srand(time(NULL));
	random_shuffle(m_cardSet.begin(), m_cardSet.end());
	for (int iter = 0; iter < 8; iter++) {

		m_cardSet[iter].setDestination((iter % 4 * 100) + 100,
				(iter < 4 ? 100 : 250));
	}

}

void logicCards::compareCard() {

	for (int i = 0; i < 8; i++) {

		if (m_cardSet[i].m_currentStateOfCard == FACE_OF_CARD) {

			m_TwoCard.insert(i);
			switch (m_TwoCard.size()) {

			case 2:

				m_Begin = m_TwoCard.begin();
				m_End = --m_TwoCard.end();

				if (m_cardSet[*m_Begin].face == m_cardSet[*m_End].face
						&& m_cardSet[*m_Begin].suit == m_cardSet[*m_End].suit) {


					m_cardSet[*m_Begin].m_currentStateOfCard = INVISIBLE_OF_CARD;
					m_cardSet[*m_End].m_currentStateOfCard = INVISIBLE_OF_CARD;

					SoundsBank::sound->PlayMusic(0);
					cout << "Music" << endl;

					m_TwoCard.clear();

				}else{	m_TwoCard.insert(i);}

				break;
			case 3:

				m_cardSet[*m_Begin].m_currentStateOfCard = BACK_OF_CARD;
				m_cardSet[*m_End].m_currentStateOfCard = BACK_OF_CARD;

				m_TwoCard.erase(*m_Begin);

				m_TwoCard.erase(*m_End);

				break;

			}

		}
	}
}
