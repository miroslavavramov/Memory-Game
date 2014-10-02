/*
 * Text.cpp
 *
 *  Created on: Sep 24, 2014
 *      Author: Todor
 */

#include "Text.h"

Text::Text() {
	// TODO Auto-generated constructor stub
startTime = 60;
}

Text::~Text() {
	// TODO Auto-generated destructor stub
}

void Text::Init(SDL_Renderer* a) {
	m_textColor.a = 255;
	m_textColor.r = 255;
	m_textColor.g = 0;
	m_textColor.b = 0;
    m_Message = "100";

	m_textFont = TTF_OpenFont("font/myriad-web-pro.ttf", 36);
	if (!m_textFont) {
		cerr << "TTF_OpenFont: " << TTF_GetError() << endl;
		// handle error
	}

	destination.x = 100;
	destination.y = 100;
	destination.w = 300;
	destination.h = 30;

}

void Text::Draw(SDL_Renderer* a) {

	 m_textSurface = TTF_RenderText_Solid(m_textFont, timeText.str().c_str() , m_textColor);


	m_t = SDL_CreateTextureFromSurface(a, m_textSurface);
	SDL_RenderCopy(a, m_t, 0, &destination);
}

void Text::UpDate(SDL_Event e) {
//	unsigned int lastTime = 0, currentTime;




	 if(e.type == SDL_KEYDOWN)
	 {
		 switch (e.key.keysym.sym) {
		 case SDLK_0:
			 running = true;
				 PrintTime();

		 		break;
		 		}

		 	}

}


void Text::PrintTime() {

	startTime -= m_speed;
	destination.h = 60;
	destination.w = 500;
	m_textColor.g = 255;
	m_textColor.r = 0;
	timeText.str("");
//		 		int currentTime = SDL_GetTicks()/100;
	if ((startTime - m_speed) < 60 && (startTime - m_speed) > 0) {
		startTime -= m_speed;
		timeText << "Milliseconds since start time " << startTime;
	} else {
		startTime = 0;
		timeText << "Milliseconds since start time " << startTime;
	}
//	startTime -= (int) SDL_GetTicks() / 100;
}
