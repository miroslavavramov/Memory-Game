/*
 * BackgroundTexture.cpp
 *
 *  Created on: Sep 27, 2014
 *      Author: Todor
 */

#include "BackgroundTexture.h"

BackgroundTexture::BackgroundTexture() {
	// TODO Auto-generated constructor stub

}

BackgroundTexture::~BackgroundTexture() {
	// TODO Auto-generated destructor stub
}


void BackgroundTexture::Init(SDL_Renderer* a) {

	SDL_Surface* Ship = IMG_Load("images/Project-DMT-Background-Gryb.png");

	//Create texture from surface pixels
	m_t = SDL_CreateTextureFromSurface(a, Ship);
//	SDL_SetTextureBlendMode(m_t, SDL_BLENDMODE_BLEND);
//		SDL_SetTextureAlphaMod(m_t, 100);
	SDL_FreeSurface(Ship);



}

void BackgroundTexture::Draw(SDL_Renderer* a) {

	SDL_RenderCopy(a, m_t, 0, 0);
}
