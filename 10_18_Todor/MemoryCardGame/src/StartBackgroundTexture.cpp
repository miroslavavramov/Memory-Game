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
	SDL_Surface* background = IMG_Load("images/menu.png");
	m_textBackground[0] = SDL_CreateTextureFromSurface(a, background);

	SDL_FreeSurface(background);

}



void StartBackgroundTexture::InitRules(SDL_Renderer* a) {
	SDL_Surface* background = IMG_Load("images/rules.png");
	m_textTeam = SDL_CreateTextureFromSurface(a, background);

	SDL_FreeSurface(background);
}

void StartBackgroundTexture::Draw(SDL_Renderer* a) {


	SDL_RenderCopy(a, m_textBackground[0], 0, 0);
}



void StartBackgroundTexture::DrawRules(SDL_Renderer* a) {
	SDL_RenderCopy(a, m_textTeam, 0, 0);

}


void StartBackgroundTexture::InitSatistics(SDL_Renderer*) {

}


void StartBackgroundTexture::DrawSatistics(SDL_Renderer* a) {

vector <string> temp;

temp = m_statRecord.readFromFile();
	m_txtStatistics.setTextColor(0,0,0, 255);

int offset = 20;

	for (unsigned  i = 0; i < temp.size(); i ++)
	{
		offset += 40;
		m_txtStatistics.Set(512, 50 + offset, 12, 20, temp.at(i));
		m_txtStatistics.Draw(a);
	}

}
