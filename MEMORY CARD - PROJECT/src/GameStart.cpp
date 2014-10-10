/*
 * GameStart.cpp
 *
 *  Created on: Sep 30, 2014
 *      Author: User
 */

#include "GameStart.h"


GameStart::GameStart() {
	// TODO Auto-generated constructor stub
	m_bRunning = true;
	m_pRenderer = NULL;

}

GameStart::~GameStart() {
	// TODO Auto-generated destructor stub
}

void GameStart::Init(SDL_Renderer* a) {


	// attempt to initialize SDL
	backGroundMenu.Init(m_pRenderer);
	m_buttonsMenu.Init(m_pRenderer);
	for (int iter = 0; iter < 5; iter++){
		m_buttonsMenu.setSource(iter * 320,0,320,75);
		m_buttonsMenu.setDestination(100,(250 + 80 * iter),280,73);

		m_buttonSet.push_back(m_buttonsMenu);

	}

}

void GameStart::Draw()
{
	SDL_RenderClear(m_pRenderer);
	backGroundMenu.Draw(m_pRenderer);

	for (int iter = 0; iter < 5; iter++)
			m_buttonSet[iter].Draw(m_pRenderer);

	SDL_RenderPresent(m_pRenderer);
}

void GameStart::Update()
{
	SDL_Event event;
		//close windows
		if (SDL_PollEvent(&event))
		{
			switch (event.type)
			{
				case SDL_QUIT:
					m_bRunning = false;
					break;
				default:
					break;
			}

			//close with escape
			if (event.type == SDL_KEYDOWN) {
				if (event.key.keysym.sym == SDLK_ESCAPE) {
					m_bRunning = false;
				}
			}
		}
		for (int iter = 0; iter < 5; iter++)
				m_buttonSet[iter].Update(event);
}

bool GameStart::Running()
{
	return m_bRunning;
}
