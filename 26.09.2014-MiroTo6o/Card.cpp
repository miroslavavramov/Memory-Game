/*
 * Card.cpp
 *
 *  Created on: Sep 16, 2014
 *      Author: Todor
 */

#include "Card.h"

Card::Card() {
	// TODO Auto-generated constructor stub
	int face = 0;
	int suit = 0;
	int state = 0;

}

Card::~Card() {
	// TODO Auto-generated destructor stub
}

void Card::Init(SDL_Renderer* a) {
	SDL_Surface* cardSurface = IMG_Load("images/cards.png");
	SDL_SetColorKey(cardSurface, 1,
			SDL_MapRGB(cardSurface->format, 255, 255, 255));
	//Create texture from surface pixels
	if (!cardSurface) {
		cerr << "images/cards.png: not found " << SDL_GetError() << endl;
	}
	m_t = SDL_CreateTextureFromSurface(a, cardSurface);
	SDL_FreeSurface(cardSurface);

	m_source.x = CARD_WIDTH * face;
	m_source.y = CARD_HEIGHT * suit;
	m_source.h = CARD_HEIGHT;
	m_source.w = CARD_WIDTH;

//   m_destination = {0 - 35, 600- 25, 70, 25};
}

void Card::Draw(SDL_Renderer* a) {

	SDL_RenderCopy(a, m_t, &m_source, &m_destination);
}

//const SDL_Rect& Card::getDestination() const {
//	return;
//}

void Card::setDestination(int x_dest, int y_dest) {
	m_destination.x = x_dest;
	m_destination.y = y_dest;
	m_destination.w = CARD_WIDTH;
	m_destination.h = CARD_HEIGHT;
}

void Card::UpDate(SDL_Event e) {
	if (e.type == SDL_MOUSEBUTTONDOWN) {
		int xCoordinate, yCoordinate;
		SDL_GetMouseState(&xCoordinate, &yCoordinate);
		if (xCoordinate > m_destination.x
				&& xCoordinate < m_destination.x + m_destination.w
				&& yCoordinate > m_destination.y
				&& yCoordinate < m_destination.y + m_destination.h) {
			if (state == 0) {
				state = 1;

			}
		}

	}
}
