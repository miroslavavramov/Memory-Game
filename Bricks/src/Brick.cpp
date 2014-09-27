/*
 * Brick.cpp
 *
 *  Created on: Sep 23, 2014
 *      Author: Todor
 */

#include "Brick.h"

Brick::Brick() {
	// TODO Auto-generated constructor stub

}

Brick::~Brick() {
	// TODO Auto-generated destructor stub
}

void Brick::Init(SDL_Renderer* a, int x, int y) {

		SDL_Surface* Ship = IMG_Load("images/brick.bmp");
		SDL_SetColorKey(Ship, 1, SDL_MapRGB(Ship->format, 255, 255, 255));
			//Create texture from surface pixels
			m_t = SDL_CreateTextureFromSurface(a, Ship);
			SDL_FreeSurface(Ship);
			source = {0, 0, 167, 47};
            destination.x = x;
            destination.y = y;
			destination.w = 50;
			destination.h = 30;

}

void Brick::Draw(SDL_Renderer* a) {

	SDL_RenderCopy(a, m_t, &source, &destination);
}

