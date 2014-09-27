/*
 * Ball.cpp
 *
 *  Created on: Sep 22, 2014
 *      Author: Todor
 */

#include "Ball.h"


Ball::Ball()
{

}


Ball::~Ball()
{

}

void Ball::Init(SDL_Renderer* a) {

		SDL_Surface* Ship = IMG_Load("images/ball.bmp");
		SDL_SetColorKey(Ship, 1, SDL_MapRGB(Ship->format, 254, 254, 254));
			//Create texture from surface pixels
			m_t = SDL_CreateTextureFromSurface(a, Ship);
			SDL_FreeSurface(Ship);
			source = {0, 0, 30, 30};

			destination = {400, 300, 30, 30};

}


void Ball::Draw(SDL_Renderer* a) {

	SDL_RenderCopy(a, m_t, &source, &destination);
}
