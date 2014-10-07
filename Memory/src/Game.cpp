#include "Game.h"
#include "StateManager.h"
SoundsBank* SoundsBank::sound;
StateManager* StateManager::stateMachine;
Timer * Timer::g_Timer;

Game::Game() {
}

Game::~Game() {
	// TODO Auto-generated destructor stub
}

//here things will be initialized ******************************************************************************

bool Game::Init(const char* title, int xpos, int ypos, int width, int height,
		int flags) {

	// attempt to initialize SDL
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
		Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 4097);

		std::cout << "SDL init success\n";
//		 init the window

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
	SoundsBank::sound->initSoundEffect("sounds/no_time.wav");
	SoundsBank::sound->initMusic("sounds/removeCards.mp3");

	StateManager::stateMachine = new StateManager();
	StateManager::stateMachine->setCurrentGameStates(GAMEOVER);

	Timer::g_Timer = new Timer();

	m_StartGameMenu.backGroundMenu.Init(m_pRenderer);
	m_StartGameMenu.backGroundForTeam.InitTeam(m_pRenderer);
	m_StartGameMenu.backGroundForTeam.InitRules(m_pRenderer);
	m_StartGameMenu.m_buttonsMenu.Init(m_pRenderer);
	for (int iter = 0; iter < 5; iter++) {
		m_StartGameMenu.m_buttonsMenu.setSource(iter * 320, 0, 320, 75);
		m_StartGameMenu.m_buttonsMenu.setDestination(100, (250 + 80 * iter),
				280, 73);

		m_StartGameMenu.m_buttonSet.push_back(m_StartGameMenu.m_buttonsMenu);
	}
	texture.Init(m_pRenderer);
//		m_temp.Init(m_pRenderer);
	m_cardLogic.Init(m_pRenderer);

	//init and draw Play button
	m_Play.Init(m_pRenderer);

	m_Play.setSource(546, 0, 204, 72);
	m_Play.setDestination(523, 692, 204, 72);

	//init and draw BET
	m_Bet.Init(m_pRenderer);

	m_Bet.setSource(0, 0, 147, 78);
	m_Bet.setDestination(0, 684, 147, 78);

	//init and draw WIN
	m_WIN.Init(m_pRenderer);
	m_WIN.setSource(150, 0, 189, 107);
	m_WIN.setDestination(837, 656, 189, 107);

	//init and draw MENU
	m_Menu.Init(m_pRenderer);
	m_Menu.setSource(336, 0, 210, 78);
	m_Menu.setDestination(197, 691, 210, 78);

	//init CREDITS
	m_Credits.Init(m_pRenderer);
	m_Credits.setSource(752, 0, 291, 42);
	m_Credits.setDestination(332, 600, 291, 42);

	txt.Set(470, 90, 55, 50);
	txt.setTextColor(255, 255, 255, 255);

	level.Set(520, 30, 17, 35);
	level.setTextColor(254, 255, 88, 255);

//	**************
//	bet.Set();
//	bet.setTextColor(255, 255, 255, 255);
	credit.Set(380, 617, 100, 17);
	credit.setTextColor(255, 255, 255, 255);

	profit.Set(900, 700, 100, 17);
	profit.setTextColor(255, 255, 255, 255);

	return true;

}/*end of Init*/

//here things will be updated ******************************************************************************

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
	switch (StateManager::stateMachine->getCurrentGameStates()) {
	case MENU:

		for (int iter = 0; iter < 5; iter++) {
			m_StartGameMenu.m_buttonSet[iter].Update(event);
			if (m_StartGameMenu.m_buttonSet[0].getState() == CLICK_BUTTON) {
//					m_currentGameStates = STARTGAME;
				StateManager::stateMachine->setCurrentGameStates(GAMEOVER);
				m_StartGameMenu.m_buttonSet[0].setState(NORMAL_BUTTON);
				SoundsBank::sound->PlaySoundEffect(1);
			}

			if (m_StartGameMenu.m_buttonSet[3].getState() == CLICK_BUTTON) {
//					m_currentGameStates = RULES_OF_GAMES;
				StateManager::stateMachine->setCurrentGameStates(
						RULES_OF_GAMES);
				m_StartGameMenu.m_buttonSet[3].setState(NORMAL_BUTTON);
			}

			if (m_StartGameMenu.m_buttonSet[4].getState() == CLICK_BUTTON) {
//					m_currentGameStates = TEAM_PROJECT;
				StateManager::stateMachine->setCurrentGameStates(TEAM_PROJECT);
				m_StartGameMenu.m_buttonSet[4].setState(NORMAL_BUTTON);
			}
		}

		break;

	case STARTGAME:
//*********************

		m_cardLogic.Update(event);
		m_cardLogic.compareCard();

		if (Timer::g_Timer->GetIsStarted()) {

			if (Timer::g_Timer->GetSeconds() < 4
					&& Timer::g_Timer->GetSeconds() > 0) {
//				SoundsBank::sound->PlaySoundEffect(3);
			}

			if (Timer::g_Timer->GetSeconds() == 0
					|| m_cardLogic.getCountInvCards() == m_RightGuesses) {

				//here statistics gathers information for Timer end Clicks
				m_stat.setSecondToEnd(Timer::g_Timer->GetSeconds());
				m_stat.setClickForLevel(Card::clickCount);

				StateManager::stateMachine->setCurrentGameStates(GAMEOVER);

				Timer::g_Timer->StopTimer();

			}
			m_stat.setGameLevel(m_cardLogic.getTempLevel());
			level.IntToTextMessage(m_cardLogic.getTempLevel());

		}
		txt.UpdateTextMessage(Timer::g_Timer->getString());


		break;

	case RULES_OF_GAMES:

		m_StartGameMenu.backGroundForTeam.Update(event);

		break;
	case TEAM_PROJECT:

		m_StartGameMenu.backGroundForTeam.Update(event);

		break;

	case GAMEOVER:
		m_Play.Update(event);
		m_Menu.Update(event);

		if (m_Menu.isIsClicked()) {

			StateManager::stateMachine->setCurrentGameStates(MENU);
			m_Menu.setIsClicked(false);
		}
		credit.IntToTextMessage(m_stat.getCredit());
		level.IntToTextMessage(m_cardLogic.getTempLevel());
		break;

	case VIEW_CARDS:

		if (Timer::g_Timer->GetIsStarted()) {

//			Timer::g_Timer -> getString();
			txt.UpdateTextMessage(Timer::g_Timer->getString());
			if (Timer::g_Timer->GetSeconds() == 0) {
				StateManager::stateMachine->setCurrentGameStates(STARTGAME);
				Timer::g_Timer->StopTimer();
				Timer::g_Timer->StartTimer(9);
			}
		}

		level.IntToTextMessage(m_cardLogic.getTempLevel());
		m_RightGuesses = (m_cardLogic.getTempLevel() + 3);

		break;
	}

}/*end of Update*/

//here things will be drawn ******************************************************************************

void Game::Draw() {
	SDL_RenderClear(m_pRenderer);

	switch (StateManager::stateMachine->getCurrentGameStates()) {
	case MENU:

		m_StartGameMenu.backGroundMenu.Draw(m_pRenderer);

		for (int iter = 0; iter < 5; iter++)
			m_StartGameMenu.m_buttonSet[iter].Draw(m_pRenderer);

		break;

	case STARTGAME:

		texture.Draw(m_pRenderer);
		m_cardLogic.Draw(m_pRenderer);
		m_Play.Draw(m_pRenderer);
		m_Bet.Draw(m_pRenderer);
		m_WIN.Draw(m_pRenderer);
		m_Credits.Draw(m_pRenderer);
		m_Menu.Draw(m_pRenderer);  //BUTTON MENU
		level.Draw(m_pRenderer);
		txt.Draw(m_pRenderer);
		credit.Draw(m_pRenderer);
		profit.Draw(m_pRenderer);
		break;

	case RULES_OF_GAMES:
		m_StartGameMenu.backGroundForTeam.DrawRules(m_pRenderer);
		break;

	case TEAM_PROJECT:
		m_StartGameMenu.backGroundForTeam.DrawTeam(m_pRenderer);
		break;

	case GAMEOVER:

		texture.Draw(m_pRenderer);
		m_Play.Draw(m_pRenderer);
		m_Bet.Draw(m_pRenderer);
		m_WIN.Draw(m_pRenderer);
		m_Credits.Draw(m_pRenderer);
		m_Menu.Draw(m_pRenderer);
		level.Draw(m_pRenderer);
		txt.Draw(m_pRenderer);
		credit.Draw(m_pRenderer);
		profit.Draw(m_pRenderer);
		break;

	case VIEW_CARDS:

		if (m_Play.isIsClicked()) {
			m_cardLogic.GetCardFromDeck();
			m_cardLogic.m_TwoCard.clear();
			m_Play.setIsClicked(false);
		}

		texture.Draw(m_pRenderer);
		m_Play.Draw(m_pRenderer);
		m_Bet.Draw(m_pRenderer);
		m_WIN.Draw(m_pRenderer);
		m_Credits.Draw(m_pRenderer);
		m_Menu.Draw(m_pRenderer);  //BUTTON MENU
		m_cardLogic.Draw(m_pRenderer);
		level.Draw(m_pRenderer);


		credit.Draw(m_pRenderer);
		break;

	}

	SDL_RenderPresent(m_pRenderer);
}/*end of Draw*/

bool Game::Running() {
	return m_bRunning;
}
