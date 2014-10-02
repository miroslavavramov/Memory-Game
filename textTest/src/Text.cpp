/*
 * Text.cpp
 *
 *  Created on: Sep 24, 2014
 *      Author: Todor
 */

#include "Text.h"

Text::Text() {
	// TODO Auto-generated constructor stub

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
	 m_textSurface = TTF_RenderText_Solid(m_textFont,timeText.str().c_str() , m_textColor);


	m_t = SDL_CreateTextureFromSurface(a, m_textSurface);
	SDL_RenderCopy(a, m_t, 0, &destination);
}

void Text::UpDate(SDL_Event e) {
//	unsigned int lastTime = 0, currentTime;



	if (e.type == SDL_MOUSEBUTTONDOWN) {
		int xCoordinate, yCoordinate;
		SDL_GetMouseState(&xCoordinate, &yCoordinate);
		if (xCoordinate > destination.x
				&& xCoordinate < destination.x + destination.w
				&& yCoordinate > destination.y
				&& yCoordinate < destination.y + destination.h){
		destination.h = 60;
		destination.w = 500;
		m_textColor.g = 255;
		m_textColor.r = 0;
		timeText.str( "" );
		int currentTime = SDL_GetTicks()/100;
		timeText << "Milliseconds since start time " << startTime - currentTime;

//		currentTime = SDL_GetTicks();
//			  if (currentTime > lastTime + 1000) {
//			    //printf("Report: %d\n", variable);
//			    lastTime = currentTime;
//			  }
//		m_Message = timeText;
//		m_Message = "00";
		}
	}

}

//void Text::PrintTime(SDL_Event e) {
//
//	unsigned int lastTime = 0, currentTime;
//	while (e.type == SDLK_q) {
//	  // do stuff
//	  // ...
//
//	  // Print a report once per second
//	  currentTime = SDL_GetTicks();
//	  if (currentTime > lastTime + 1000) {
//	    printf("Report: %d\n", variable);
//	    lastTime = currentTime;
//	  }
//	}
//}