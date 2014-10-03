#include "Game.h"

SoundsBank* SoundsBank::sound;

Game::Game() {
}

Game::~Game() {
	// TODO Auto-generated destructor stub
}

bool Game::Init(const char* title, int xpos, int ypos, int width, int height,
		int flags) {
	// attempt to initialize SDL
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
		Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 4097 );
		std::cout << "SDL init success\n";
		// init the window
		m_pWindow = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
		if (m_pWindow != 0) // window init success
				{
			std::cout << "window creation success\n";
			m_pRenderer = SDL_CreateRenderer(m_pWindow, -1, 0);
			if (m_pRenderer != 0) // renderer init success
					{
				std::cout << "renderer creation success\n";
				SDL_SetRenderDrawColor(m_pRenderer, 0, 100, 0, 255);

			} else {
				std::cout << "renderer init fail\n";
				return false; // renderer init fail
			}
		} else {
			std::cout << "window init fail\n";
			return false; // window init fail
		}
	} else {
		std::cout << "SDL init fail\n";
		return false; // SDL init fail
	}

	std::cout << "init success\n";
	m_bRunning = true; // everything inited successfully,
//		start the main loop
	//initial game State

	SoundsBank::sound = new SoundsBank();
	SoundsBank::sound->initSoundEffect("sounds/hover.wav");
	SoundsBank::sound->initSoundEffect("sounds/connect.wav");
	SoundsBank::sound->initSoundEffect("sounds/button-24.wav");
	SoundsBank::sound->initSoundEffect("sounds/removeCards.wav");
	SoundsBank::sound->initMusic("sounds/removeCards.mp3")
;
	m_currentGameStates = MENU;

		m_StartGameMenu.backGroundMenu.Init(m_pRenderer);
		m_StartGameMenu.backGroundForTeam.InitTeam(m_pRenderer);
		m_StartGameMenu.backGroundForTeam.InitRules(m_pRenderer);
		m_StartGameMenu.m_buttonsMenu.Init(m_pRenderer);
		for (int iter = 0; iter < 5; iter++)
		{
				m_StartGameMenu.m_buttonsMenu.setSource(iter * 320,0,320,75);
				m_StartGameMenu.m_buttonsMenu.setDestination(100,(250 + 80 * iter),280,73);

				m_StartGameMenu.m_buttonSet.push_back(m_StartGameMenu.m_buttonsMenu);
		}
		texture.Init(m_pRenderer);
//		m_temp.Init(m_pRenderer);
		m_cardLogic.Init(m_pRenderer);

		m_cardLogic.GetCardFromDeck();

	return true;

}
void Game::Update() {
	SDL_Event event;
	//close windows
	if (SDL_PollEvent(&event)) {
		switch (event.type) {
		case SDL_QUIT:
			m_bRunning = false;
			break;
		default:
			break;
		}
	}
	//close with escape
	if (event.type == SDL_KEYDOWN) {
		if (event.key.keysym.sym == SDLK_ESCAPE) {
			m_bRunning = false;
		}
	}
	//
	switch (m_currentGameStates) {
		case MENU:

			for (int iter = 0; iter < 5; iter++)
			{
				m_StartGameMenu.m_buttonSet[iter].Update(event);
				if (m_StartGameMenu.m_buttonSet[0].getState() == CLICK_BUTTON)
				{
					m_currentGameStates = STARTGAME;
					SoundsBank::sound->PlaySoundEffect(1);
				}

				if(m_StartGameMenu.m_buttonSet[3].getState() == CLICK_BUTTON)
				{
					m_currentGameStates = RULES_OF_GAMES;
				}

				if(m_StartGameMenu.m_buttonSet[4].getState() == CLICK_BUTTON)
				{
					m_currentGameStates = TEAM_PROJECT;
				}
			}

			break;
		case STARTGAME:
			m_cardLogic.Update(event);
			m_cardLogic.compareCard();
			break;

		}
}

void Game::Draw() {
	SDL_RenderClear(m_pRenderer);

	switch (m_currentGameStates) {
		case MENU:
			m_StartGameMenu.backGroundMenu.Draw(m_pRenderer);
	//		buttonsMenu.Draw(m_pRenderer);
			for (int iter = 0; iter < 5; iter++)
							m_StartGameMenu.m_buttonSet[iter].Draw(m_pRenderer);
			break;
		case STARTGAME:
			texture.Draw(m_pRenderer);
//			for (int iter = 0; iter < 14; iter++)
//					m_cardSet[iter].Draw(m_pRenderer);
			m_cardLogic.Draw(m_pRenderer);
			break;
		case RULES_OF_GAMES:
			m_StartGameMenu.backGroundForTeam.DrawRules(m_pRenderer);
			break;
		case TEAM_PROJECT:
			m_StartGameMenu.backGroundForTeam.DrawTeam(m_pRenderer);
			break;

		}

	SDL_RenderPresent(m_pRenderer);
}

bool Game::Running() {
	return m_bRunning;
}