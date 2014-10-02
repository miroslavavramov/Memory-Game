/*
 * StartBackgroundTexture.cpp
 *
 *  Created on: Sep 30, 2014
 *      Author: User
 */

#include "StartBackgroundTexture.h"

StartBackgroundTexture::StartBackgroundTexture() {
	// TODO Auto-generated constructor stub

}

StartBackgroundTexture::~StartBackgroundTexture() {
	// TODO Auto-generated destructor stub
}

void StartBackgroundTexture::Init(SDL_Renderer* a)
{
	SDL_Surface* background = IMG_Load("images/background.png");
	m_t = SDL_CreateTextureFromSurface(a,background);

	SDL_FreeSurface(background);
}

void StartBackgroundTexture::Draw(SDL_Renderer* a)
{
	SDL_RenderCopy(a,m_t,0,0);
}
