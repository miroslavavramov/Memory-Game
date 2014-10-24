/*
 * StartBackgroundTexture.cpp
 *
 *  Created on: Sep 30, 2014
 *      Author: User
 */

#include "StartBackgroundTexture.h"

StartBackgroundTexture::StartBackgroundTexture() {
	// TODO Auto-generated constructor stub
	m_r = 0;
	m_textRules = 0;
	m_textStat = 0;
	m_t = 0;
	m_textBackground = 0;

}

StartBackgroundTexture::~StartBackgroundTexture() {
	// TODO Auto-generated destructor stub
}

void StartBackgroundTexture::Init(SDL_Renderer* a) {
	SDL_Surface* background = IMG_Load("images/menu.png");
	m_textBackground = SDL_CreateTextureFromSurface(a, background);

	SDL_FreeSurface(background);

}

void StartBackgroundTexture::Draw(SDL_Renderer* a) {

	SDL_RenderCopy(a, m_textBackground, 0, 0);
}

void StartBackgroundTexture::InitRules(SDL_Renderer* a) {
	SDL_Surface* background = IMG_Load("images/rules.png");
	m_textRules = SDL_CreateTextureFromSurface(a, background);

	SDL_FreeSurface(background);
}

void StartBackgroundTexture::DrawRules(SDL_Renderer* a) {
	SDL_RenderCopy(a, m_textRules, 0, 0);

}

void StartBackgroundTexture::InitSatistics(SDL_Renderer* a) {
	SDL_Surface* background = IMG_Load("images/stat.png");
	m_textStat = SDL_CreateTextureFromSurface(a, background);
	SDL_FreeSurface(background);
}

void StartBackgroundTexture::DrawSatistics(SDL_Renderer* a) {
	SDL_RenderCopy(a, m_textStat, 0, 0);
	vector<string> temp;

	temp = m_statRecord.readFromFile();
	m_txtStatistics.setTextColor(230, 0, 0, 255);

	int offset = 40;
	for (int i = temp.size() - 1; i > -1; i--) {
		offset += 40;
		m_txtStatistics.Set(512, 100 + offset, 11, 25, temp.at(i));
		m_txtStatistics.Draw(a);
	}
}
