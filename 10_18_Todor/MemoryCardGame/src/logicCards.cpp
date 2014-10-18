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
	CardSetX = 312;
	CardSetY = 250;
	CardSetOffsetX = 100;
	CardSetOffsetY = 400;
	m_lastTime = SDL_GetTicks();

}

logicCards::~logicCards() {
	// TODO Auto-generated destructor stub
}

void logicCards::Init(SDL_Renderer* cardRender) {

	m_Cards.Init(cardRender);
	m_newDeck.Init();
	m_newDeck.Shuffle();
	TempLevel = 1;

}

void logicCards::Draw(SDL_Renderer* cardRender) {

	for (int iter = 0; iter < (TempLevel + 3) * 2; iter++) {
		m_cardSet[iter].Draw(cardRender);
	}

}

void logicCards::Update(SDL_Event event) {
	for (int iter = 0; iter < (TempLevel + 3) * 2; iter++) {
		m_cardSet[iter].Update(event);

	}
	std::cout << " ----- curr" << m_cardSet[0].m_currentStateOfCard
			<< std::endl;
	std::cout << " ----- new" << m_cardSet[0].m_NewStateOfCard << std::endl;
}

void logicCards::GetCardFromDeck() {
	m_cardSet.clear();

	if (m_CountInvCards == (TempLevel + 3)) {

		TempLevel++;
	}

	m_CountInvCards = 0;
	for (int iter = 0; iter < (TempLevel + 3); iter++) {

		Card temp = m_newDeck.getCard();
		m_Cards.face = temp.face;
		m_Cards.suit = temp.suit;
		m_Cards.m_NewStateOfCard = BACK_OF_CARD;
		m_Cards.m_currentStateOfCard = FACE_OF_CARD;

		m_Cards.m_source.x = CARD_WIDTH * m_Cards.face;
		m_Cards.m_source.y = CARD_HEIGHT * m_Cards.suit;
		m_Cards.m_source.h = CARD_HEIGHT;
		m_Cards.m_source.w = CARD_WIDTH;

		m_cardSet.push_back(m_Cards);
		m_cardSet.push_back(m_Cards);
	}

	srand(time(NULL));
	random_shuffle(m_cardSet.begin(), m_cardSet.end());

	CardSetX = 362 - TempLevel * 50;
	for (int iter = 0; iter < (TempLevel + 3) * 2; iter++) {

		m_cardSet[iter].setDestination(
				(iter % (TempLevel + 3) * CardSetOffsetX) + CardSetX,
				(iter < (TempLevel + 3) ? CardSetY : CardSetOffsetY));
		//cout << m_cardSet[iter].m_currentStateOfCard << endl;
	}

}

void logicCards::compareCard() {
	for (int i = 0; i < (TempLevel + 3) * 2; i++) {

		if (m_cardSet[i].m_currentStateOfCard == FACE_OF_CARD && m_cardSet[i].m_NewStateOfCard == FACE_OF_CARD) {

			m_TwoCard.insert(i);
			switch (m_TwoCard.size()) {

			case 2:

				m_Begin = m_TwoCard.begin();
				m_End = --m_TwoCard.end();
				cout << "In set   Begin" << *m_Begin << endl;
				cout << "In set   End" << *m_End << endl;

				if (m_cardSet[*m_Begin].face == m_cardSet[*m_End].face
						&& m_cardSet[*m_Begin].suit == m_cardSet[*m_End].suit) {
//
						m_cardSet[*m_End].m_NewStateOfCard = INVISIBLE_OF_CARD;
						m_cardSet[*m_Begin].m_NewStateOfCard = INVISIBLE_OF_CARD;
						if((m_cardSet[*m_End].m_currentStateOfCard == INVISIBLE_OF_CARD) && (m_cardSet[*m_Begin].m_currentStateOfCard == INVISIBLE_OF_CARD))
						m_CountInvCards++;
//					std::cout << m_CountInvCards << std::endl;
					/*					if(m_CountInvCards == (TempLevel + 3)){

					 TempLevel++;
					 }*/
					SoundsBank::sound->PlayMusic(0);

					m_TwoCard.clear();

				} else {
					m_TwoCard.insert(i);
				}

				break;
			case 3:
//
					m_cardSet[*m_Begin].m_NewStateOfCard = BACK_OF_CARD;
					m_cardSet[*m_End].m_NewStateOfCard = BACK_OF_CARD;

				m_TwoCard.erase(*m_Begin);

				m_TwoCard.erase(*m_End);

				break;

			}
		}
	}
}

//void logicCards::animateCard() {
//
//	m_lastTime = m_currentTime = SDL_GetTicks();
//
//	while (!(m_currentTime > m_lastTime + 3000)) {
//		for (int iter = 0; iter < (TempLevel + 3) * 2; iter++) {
//			m_cardSet[iter].m_NewStateOfCard = BACK_OF_CARD;
//
//		}
//		for (int iter = 0; iter < (TempLevel + 3) * 2; iter++) {
//				m_cardSet[iter].ChangeCardState();
//
//			}
//		m_currentTime = SDL_GetTicks();
//	}
//}
