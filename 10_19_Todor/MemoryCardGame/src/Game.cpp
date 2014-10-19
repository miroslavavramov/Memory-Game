#include "Game.h"
#include "StateManager.h"
//static objects
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

//		 init the window

		m_pWindow = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
		if (m_pWindow != 0) // window init success
				{
			m_pRenderer = SDL_CreateRenderer(m_pWindow, -1, 0);
			if (m_pRenderer != 0) // renderer init success
					{
				SDL_SetRenderDrawColor(m_pRenderer, 255, 255, 255, 255);

			} else {
				return false; // renderer init fail
			}
		} else {
			return false; // window init fail
		}
	} else {
		return false; // SDL init fail
	}

	m_bRunning = true; // everything inited successfully,
//		start the main loop
			//initial game State
	SDL_Surface* temp = IMG_Load("images/GameBackground_1.png");

//Create texture from surface pixels
	m_BackGroundTexture = SDL_CreateTextureFromSurface(m_pRenderer, temp);
	SDL_FreeSurface(temp);

	SoundsBank::sound = new SoundsBank();
	SoundsBank::sound->initSoundEffect("sounds/hover.wav");
	SoundsBank::sound->initSoundEffect("sounds/connect.wav");
	SoundsBank::sound->initSoundEffect("sounds/button-24.wav");
	SoundsBank::sound->initSoundEffect("sounds/no_time.wav");
	SoundsBank::sound->initMusic("sounds/removeCards.mp3");

	StateManager::stateMachine = new StateManager();
	StateManager::stateMachine->setCurrentGameStates(MENU);

	Timer::g_Timer = new Timer();

	StartMenu.InitSatistics(m_pRenderer);
	StartMenu.Init(m_pRenderer);
	StartMenu.InitRules(m_pRenderer);

	m_buttonsMenu.Init(m_pRenderer);
	for (int iter = 0; iter < 5; iter++) {
		m_buttonsMenu.setSource(iter * 232, 0, 232, 52);
		m_buttonsMenu.setDestination(100, (250 + 60 * iter), 260, 50);

		m_buttonSet.push_back(m_buttonsMenu);
	}
	PlayButton = m_buttonSet.at(0);
	PlayButton.setSource(0, 0, 232, 52);
	PlayButton.setDestination(410, 684, 240, 60);

	m_buttonSet.at(4).setDestination(25, 699, 150, 45);

	m_cardLogic.Init(m_pRenderer);

	txt.Set(513, 50, 30, 40, " ");
	txt.setTextColor(255, 255, 0, 255);

	level.Set(790, 50, 30, 40, " ");
	level.setTextColor(255, 255, 0, 255);

//	**************
	bet.Set(950, 702, 30, 40, " ");
	bet.setTextColor(255, 255, 0, 255);
	bet.IntToTextMessage(5);

	credit.Set(295, 704, 25, 35, " ");
	credit.setTextColor(255, 255, 0, 255);

	profit.Set(790, 702, 30, 40, " ");
	profit.setTextColor(255, 255, 0, 255);

	m_stat.createFile();
	m_Recovery.createRecoverFile();
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

		for (int iter = 0; iter < 4; iter++) {
			m_buttonSet[iter].Update(event);
			if (m_buttonSet[0].getState() == CLICK_BUTTON) {
				StateManager::stateMachine->setCurrentGameStates(GAMEOVER);
				m_buttonSet[0].setState(NORMAL_BUTTON);
				SoundsBank::sound->PlaySoundEffect(1);
			}
			if (m_buttonSet[1].getState() == CLICK_BUTTON) {
				StateManager::stateMachine->setCurrentGameStates(STATISTIC);
				m_buttonSet[1].setState(NORMAL_BUTTON);
				SoundsBank::sound->PlaySoundEffect(1);
			}
			if (m_buttonSet[2].getState() == CLICK_BUTTON) {
				StateManager::stateMachine->setCurrentGameStates(
						RULES_OF_GAMES);
				m_buttonSet[2].setState(NORMAL_BUTTON);
				SoundsBank::sound->PlaySoundEffect(1);
			}

			if (m_buttonSet[3].getState() == CLICK_BUTTON) {
				StateManager::stateMachine->setCurrentGameStates(RECOVERY);
				m_buttonSet[3].setState(NORMAL_BUTTON);
			}

		}			//end of for
		break;

	case STARTGAME:
//*********************

		m_cardLogic.Update(event);
		m_cardLogic.compareCard();

		if (Timer::g_Timer->GetIsStarted()) {

			if (Timer::g_Timer->GetSeconds() == 0
					|| m_cardLogic.getCountInvCards() == m_RightGuesses) {

				//here statistics gathers information for Timer end Clicks
				m_stat.setSecondToEnd(Timer::g_Timer->GetSeconds());
				m_stat.setClickForLevel(Card::clickCount);

				Timer::g_Timer->StopTimer();
				m_stat.calculateProfit();
				m_stat.saveToFile();
				StateManager::stateMachine->setCurrentGameStates(GAMEOVER);
			}
			m_stat.setGameLevel(m_cardLogic.getTempLevel());
			level.IntToTextMessage(m_cardLogic.getTempLevel());

		}
		txt.UpdateTextMessage(Timer::g_Timer->getString());
		/*		if (!m_recover) {
		 m_Recovery.saveRecoverFile(m_cardLogic.getTempLevel(),
		 m_stat.getProfit(), m_stat.getCredit(),
		 Timer::g_Timer->GetSeconds(),
		 StateManager::stateMachine->getCurrentGameStates(),
		 m_cardLogic.getCardSet(), Card::clickCount);
		 }*/
		break;

	case RULES_OF_GAMES:

		m_buttonSet.at(4).Update(event);
		if (m_buttonSet.at(4).getState() == CLICK_BUTTON) {
			StateManager::stateMachine->setCurrentGameStates(MENU);
			m_buttonSet.at(4).setState(NORMAL_BUTTON);
			//				SoundsBank::sound->PlaySoundEffect(1);
		}
		break;

	case GAMEOVER:
		/*		if (!m_recover) {
		 m_Recovery.saveRecoverFile(m_cardLogic.getTempLevel(),
		 m_stat.getProfit(), m_stat.getCredit(),
		 Timer::g_Timer->GetSeconds(),
		 StateManager::stateMachine->getCurrentGameStates(),
		 m_cardLogic.getCardSet(), Card::clickCount);
		 }*/

		PlayButton.Update(event);
		m_buttonSet.at(4).Update(event);

		if (PlayButton.getState() == CLICK_BUTTON) {
			m_cardLogic.GetCardFromDeck();
			m_cardLogic.m_TwoCard.clear();

			Timer::g_Timer->StartTimer(2 + m_cardLogic.getTempLevel());
			StateManager::stateMachine->setCurrentGameStates(VIEW_CARDS);
			PlayButton.setState(NORMAL_BUTTON);
//			m_recover = false;
			m_Recovery.saveRecoverFile(m_cardLogic.getTempLevel(),
					m_stat.getProfit(), m_stat.getCredit(),
					StateManager::stateMachine->getCurrentGameStates(),
					Card::clickCount);

		}
		if (m_buttonSet.at(4).getState() == CLICK_BUTTON) {
			StateManager::stateMachine->setCurrentGameStates(MENU);
			m_buttonSet.at(4).setState(NORMAL_BUTTON);
//				SoundsBank::sound->PlaySoundEffect(1);
		}
		credit.IntToTextMessage(m_stat.getCredit());
		level.IntToTextMessage(m_cardLogic.getTempLevel());
		profit.IntToTextMessage(m_stat.getProfit());

		break;

	case VIEW_CARDS:

		if (Timer::g_Timer->GetIsStarted()) {

			txt.UpdateTextMessage(Timer::g_Timer->getString());
			if (Timer::g_Timer->GetSeconds() == 0) {

				Timer::g_Timer->StopTimer();
				Timer::g_Timer->StartTimer(9 + m_cardLogic.getTempLevel());
				StateManager::stateMachine->setCurrentGameStates(STARTGAME);
			}
		}
		Card::clickCount = 0;
		profit.IntToTextMessage(0);
		level.IntToTextMessage(m_cardLogic.getTempLevel());
		m_RightGuesses = (m_cardLogic.getTempLevel() + 3);
//		if (!m_recover) {
//			m_Recovery.saveRecoverFile(m_cardLogic.getTempLevel(),
//					m_stat.getProfit(), m_stat.getCredit(),
//					Timer::g_Timer->GetSeconds(),
//					StateManager::stateMachine->getCurrentGameStates(),
//					m_cardLogic.getCardSet(), Card::clickCount);
//		}
		break;
	case STATISTIC:
		m_buttonSet.at(4).Update(event);
		if (m_buttonSet.at(4).getState() == CLICK_BUTTON) {
			StateManager::stateMachine->setCurrentGameStates(MENU);
			m_buttonSet.at(4).setState(NORMAL_BUTTON);
			//				SoundsBank::sound->PlaySoundEffect(1);
		}
		break;
	case RECOVERY:

		m_Recovery.LoadRecoverFile();
		credit.IntToTextMessage(m_Recovery.getRecoverCredit());
		level.IntToTextMessage(m_Recovery.getRecoverLevel());
		m_cardLogic.setTempLevel(m_Recovery.getRecoverLevel());
		m_cardLogic.GetCardFromDeck();
		Timer::g_Timer->StartTimer(m_Recovery.getRecoverLevel() + 3);
		StateManager::stateMachine->setCurrentGameStates(VIEW_CARDS);

		break;
	}

}/*end of Update*/

//here things will be drawn ******************************************************************************

void Game::Draw() {
	SDL_RenderClear(m_pRenderer);

	switch (StateManager::stateMachine->getCurrentGameStates()) {
	case MENU:

		StartMenu.Draw(m_pRenderer);

		for (int iter = 0; iter < 4; iter++)
			m_buttonSet[iter].Draw(m_pRenderer);

		break;

	case STARTGAME:

		SDL_RenderCopy(m_pRenderer, m_BackGroundTexture, 0, 0);
		m_cardLogic.Draw(m_pRenderer);
		PlayButton.Draw(m_pRenderer);
		m_buttonSet.at(4).Draw(m_pRenderer);
		level.Draw(m_pRenderer);
		txt.Draw(m_pRenderer);
		bet.Draw(m_pRenderer);
		credit.Draw(m_pRenderer);
		profit.Draw(m_pRenderer);
		break;

	case RULES_OF_GAMES:
		StartMenu.DrawRules(m_pRenderer);
		m_buttonSet.at(4).Draw(m_pRenderer);
		break;

	case GAMEOVER:

		SDL_RenderCopy(m_pRenderer, m_BackGroundTexture, 0, 0);
		PlayButton.Draw(m_pRenderer);
		m_buttonSet.at(4).Draw(m_pRenderer);
		level.Draw(m_pRenderer);
		txt.Draw(m_pRenderer);
		bet.Draw(m_pRenderer);
		credit.Draw(m_pRenderer);
		profit.Draw(m_pRenderer);
		break;

	case VIEW_CARDS:

		SDL_RenderCopy(m_pRenderer, m_BackGroundTexture, 0, 0);
		PlayButton.Draw(m_pRenderer);
		m_cardLogic.Draw(m_pRenderer);
		m_buttonSet.at(4).Draw(m_pRenderer);
		level.Draw(m_pRenderer);
		txt.Draw(m_pRenderer);
		bet.Draw(m_pRenderer);
		profit.Draw(m_pRenderer);
		credit.Draw(m_pRenderer);
		break;
	case STATISTIC:

		StartMenu.DrawSatistics(m_pRenderer);
		m_buttonSet.at(4).Draw(m_pRenderer);
		break;

	}

	SDL_RenderPresent(m_pRenderer);
}/*end of Draw*/

bool Game::Running() {
	return m_bRunning;
}
