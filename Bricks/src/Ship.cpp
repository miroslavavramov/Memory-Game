/*
 * Ship.cpp
 *
 *  Created on: Sep 22, 2014
 *      Author: Todor
 */

#include "Ship.h"

Ship::Ship() {
	// TODO Auto-generated constructor stub

}

Ship::~Ship() {
	// TODO Auto-generated destructor stub
}

void Ship::Init(SDL_Renderer* a) {

		SDL_Surface* Ship = IMG_Load("images/board.bmp");
		SDL_SetColorKey(Ship, 1, SDL_MapRGB(Ship->format, 255, 255, 255));
			//Create texture from surface pixels
			m_t = SDL_CreateTextureFromSurface(a, Ship);
			SDL_FreeSurface(Ship);

			source = {0, 0, 90, 90};

			destination = {600 - 35, 600- 25, 70, 25};
			acceleration = 0;
}

void Ship::Draw(SDL_Renderer* a) {

	SDL_RenderCopy(a, m_t, &source, &destination);
}

const SDL_Rect& Ship::getDestination() const {
	return destination;
}

void Ship::setDestination(const SDL_Rect& destination) {
	this->destination = destination;
}



void Ship::UpDate(SDL_Event e) {
	if (e.type == SDL_KEYDOWN) {

					switch (e.key.keysym.sym) {
					case SDLK_LEFT:
						acceleration = -8;

						break;
					case SDLK_RIGHT:
						acceleration = 8;
						break;
				}
	}
	if (e.type == SDL_KEYUP) {

			switch (e.key.keysym.sym) {
			case SDLK_LEFT:
				acceleration = 0;

				break;
			case SDLK_RIGHT:
				acceleration = 0;

				break;
			}

		}
	this -> destination.x  = (destination.x + acceleration) % 800;
	if(destination.x < 0)
		this -> destination.x  = 800 - 1;


}
