/*
 * Card.cpp
 *
 *  Created on: Sep 16, 2014
 *      Author: Todor
 */
#include <SDL.h>
#include "Card.h"

Card::Card() {
	// TODO Auto-generated constructor stub

}

Card::~Card() {
	// TODO Auto-generated destructor stub
}

void Card::Draw(int x, int y, SDL_Rect* clip, SDL_Renderer* temp, Texture a) {
	SDL_Rect renderQuad = { x, y, 79, 123 };

	//Set clip rendering dimensions
	if (clip != NULL) {
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}
	//Render to screen
	SDL_RenderCopy(temp, a, clip, &renderQuad);
}

/*void Card::Init(SDL_Renderer* temp)
{
	CardTex.loadFromFile("images/cards.png", temp);
}*/
