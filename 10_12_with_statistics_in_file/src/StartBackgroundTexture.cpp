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
void StartBackgroundTexture::InitSatistics(SDL_Renderer*) {

}


void StartBackgroundTexture::DrawSatistics(SDL_Renderer* a) {

vector <string> temp;

temp = m_statRecord.readFromFile();
	m_txtStatistics.setTextColor();

/*	for (int i = 0; i < temp.size(); i ++)
	{
		cout << temp.at(i) << endl;
	}*/
int offset = 50;

	for (int i = 0; i < temp.size(); i ++)
	{
		offset +=50;
		m_txtStatistics.Set(50,50 + offset, 18, 20, temp.at(i));
		m_txtStatistics.UpdateTextMessage(temp.at(i));
		m_txtStatistics.Draw(a);
	}
}
