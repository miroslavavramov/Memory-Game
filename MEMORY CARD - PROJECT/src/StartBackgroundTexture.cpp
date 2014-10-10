/*
 * StartBackgroundTexture.cpp
 *
 *  Created on: Sep 30, 2014
 *      Author: User
 */

#include "StartBackgroundTexture.h"

StartBackgroundTexture::StartBackgroundTexture() {
	m_r = NULL;
	m_t = NULL;

	m_textTeam = NULL;
	m_textStatistic = NULL;
}

StartBackgroundTexture::~StartBackgroundTexture() {
	// TODO Auto-generated destructor stub
}

void StartBackgroundTexture::Init(SDL_Renderer* a) {
	SDL_Surface* background = IMG_Load("images/background-One.png");
	m_textBackground[0] = SDL_CreateTextureFromSurface(a, background);

	SDL_FreeSurface(background);

	background = IMG_Load("images/background-Two.png");
	m_textBackground[1] = SDL_CreateTextureFromSurface(a, background);

	SDL_FreeSurface(background);

}

void StartBackgroundTexture::InitTeam(SDL_Renderer* a) {
	SDL_Surface* background = IMG_Load("images/Team.png");
	m_t = SDL_CreateTextureFromSurface(a, background);

	SDL_FreeSurface(background);

}

void StartBackgroundTexture::InitRules(SDL_Renderer* a) {
	SDL_Surface* background = IMG_Load("images/rules.png");
	m_textTeam = SDL_CreateTextureFromSurface(a, background);

	SDL_FreeSurface(background);
}

void StartBackgroundTexture::InitStatistic(SDL_Renderer* a) {
	SDL_Surface* background = IMG_Load("images/statistics.png");
	m_textStatistic = SDL_CreateTextureFromSurface(a, background);

	SDL_FreeSurface(background);

}

void StartBackgroundTexture::DrawStatistic(SDL_Renderer* a) {
	SDL_RenderCopy(a, m_textStatistic, 0, 0);
}

void StartBackgroundTexture::Draw(SDL_Renderer* a) {

	int frameBackground = 0;

	frameBackground = (SDL_GetTicks() / 500) % 2;

	SDL_RenderCopy(a, m_textBackground[frameBackground], 0, 0);
}

void StartBackgroundTexture::DrawTeam(SDL_Renderer* a) {
	SDL_RenderCopy(a, m_t, 0, 0);
}

void StartBackgroundTexture::DrawRules(SDL_Renderer* a) {
	SDL_RenderCopy(a, m_textTeam, 0, 0);
}

void StartBackgroundTexture::Update(SDL_Event e) {
	if (e.type == SDL_MOUSEBUTTONDOWN) {
		int xCoordinate, yCoordinate;
		SDL_GetMouseState(&xCoordinate, &yCoordinate);

		if (xCoordinate > 32 && xCoordinate < 230 && yCoordinate > 623
				&& yCoordinate < 695)

				{
					StateManager::stateMachine->setCurrentGameStates(MENU);

				}

	}

}
