/*
 * Text.cpp
 *
 *  Created on: Sep 24, 2014
 *      Author: Todor
 */

#include "Text.h"

Text::Text() {
	// TODO Auto-generated constructor stub
	m_CounterSec = 9;
	m_CounterDecaSec = 2;
	m_currentTime = 0;
	m_lastTime = 0;
}

Text::~Text() {
	// TODO Auto-generated destructor stub
}

void Text::Init(SDL_Renderer* a) {
	m_textColor.a = 255;
	m_textColor.r = 255;
	m_textColor.g = 0;
	m_textColor.b = 0;

	m_textFont = TTF_OpenFont("font/12950.ttf", 60);
	if (!m_textFont) {
		cerr << "TTF_OpenFont: " << TTF_GetError() << endl;
		// handle error
	}

	destination.x = 200;
	destination.y = 100;
	destination.w = 10;
	destination.h = 60;
	itoa(m_CounterSec, m_Message, 10);

}

void Text::Draw(SDL_Renderer* a) {
	m_textSurface = TTF_RenderText_Solid(m_textFont, m_Message, m_textColor);

	m_t = SDL_CreateTextureFromSurface(a, m_textSurface);
	SDL_RenderCopy(a, m_t, 0, &destination);
}

void Text::UpDate(SDL_Event e) {


	m_currentTime = SDL_GetTicks();
	if (m_currentTime > m_lastTime + 1000) {
		if (m_CounterSec == 0) {
				m_CounterSec = 10;

			}
		m_CounterSec--;
		itoa(m_CounterSec, m_Message, 10);

//		std::cout << m_Counter << endl;
		m_lastTime = m_currentTime;
	}

}

