#include "Game.h"
#include "StateManager.h"
//static objects
SoundsBank* SoundsBank::sound;
StateManager* StateManager::stateMachine;
Timer * Timer::g_Timer;

Game::Game() {
	m_GameLevel = 0;
	iterButt = 3;
	m_bRunning = true;
	m_pRenderer = NULL;
	m_pWindow = NULL;
	m_BackGroundTexture = 0;
	m_RightGuesses = 0;
}

Game::~Game() {
	// TODO Auto-generated destructor stub
}

//here things will be initialized ******************************************************************************

bool Game::Init(const char* title, int xpos, int ypos, int width, int height,
		int flags) {

	// attempt to initialize SDL
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
		Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 1, 10000);

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
	SDL_Surface* temp = IMG_Load("images/GameBackground.png");

//Create texture from surface pixels
	m_BackGroundTexture = SDL_CreateTextureFromSurface(m_pRenderer, temp);
	SDL_FreeSurface(temp);

	SoundsBank::sound = new SoundsBank();
	SoundsBank::sound->initSoundEffect("sounds/hover.wav");
	SoundsBank::sound->initSoundEffect("sounds/connect.wav");
	SoundsBank::sound->initSoundEffect("sounds/button-24.wav");
	SoundsBank::sound->initSoundEffect("sounds/removeCards.wav");

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

	m_buttonsMenuRecover = m_buttonSet.at(3);
	m_buttonsMenuRecover.setSource(696, 100, 232, 52);
	m_buttonsMenuRecover.setDestination(100, 428, 260, 50);

	m_buttonSet.at(4).setDestination(25, 699, 150, 45);

	m_cardLogic.Init(m_pRenderer);

	txtTimer.Set(513, 50, 30, 40, " ");
	txtTimer.setTextColor(255, 255, 0, 255);

	gameOver.Set(512, 150, 30, 40, " ");
	gameOver.setTextColor(255, 255, 0, 255);

	level.Set(790, 50, 30, 40, " ");
	level.setTextColor(255, 255, 0, 255);

//	**************
	bet.Set(950, 704, 30, 40, " ");
	bet.setTextColor(255, 255, 0, 255);
	bet.IntToTextMessage(5);

	credit.Set(295, 704, 25, 35, " ");
	credit.setTextColor(255, 255, 0, 255);

	profit.Set(790, 704, 30, 40, " ");
	profit.setTextColor(255, 255, 0, 255);

//	***********************************

	m_statTxtClicks.Set(155, 60, 18, 22, " ");
	m_statTxtClicks.setTextColor(255, 255, 0, 255);

	m_statTxtLevelStatus.Set(240, 35, 18, 22, " ");
	m_statTxtLevelStatus.setTextColor(255, 255, 0, 255);

	m_statTxtSeconds.Set(155, 90, 18, 22, " ");
	m_statTxtSeconds.setTextColor(255, 255, 0, 255);

	m_statTxtLevelNumber.Set(155, 35, 18, 22, " ");
	m_statTxtLevelNumber.setTextColor(255, 255, 0, 255);

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

	switch (StateManager::stateMachine->getCurrentGameStates()) {
	case MENU:

		if ((m_Recovery.getRecoverLevel() > 1)
				&& (m_Recovery.getRecoverCredit() >= 5)) {
			iterButt = 4;
		} else {
			iterButt = 3;
		}

		for (int iter = 0; iter < iterButt; iter++) {
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
				m_Recovery.saveRecoverFile(m_cardLogic.getTempLevel(),
						m_stat.getCredit(),
						StateManager::stateMachine->getCurrentGameStates());
				m_statTxtSeconds.IntToTextMessage(
						m_stat.getGameLevel() + 9 - m_stat.getSecondToEnd());
				StateManager::stateMachine->setCurrentGameStates(GAMEOVER);
			}
			m_stat.setGameLevel(m_cardLogic.getTempLevel());
			level.IntToTextMessage(m_cardLogic.getTempLevel());

		}
		txtTimer.UpdateTextMessage(Timer::g_Timer->getString());

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

		PlayButton.Update(event);
		m_buttonSet.at(4).Update(event);

		if(PlayButton.getState() == CLICK_BUTTON)
				{
					if(m_stat.getCredit() <= 0 || m_stat.getCredit() < 5)
					{
						m_stat.setCredit(50);
						m_cardLogic.setTempLevel(1);
					}

					m_stat.setCredit(m_stat.getCredit() - 5);

				}

				if(m_stat.getCredit() < 5)
				{
					gameOver.UpdateTextMessage("GAME OVER");
				}
				else
				{
					gameOver.UpdateTextMessage(" ");
				}

//		if (m_stat.getCredit() < 0) {
//			gameOver.UpdateTextMessage("GAME OVER");
//			if (PlayButton.getState() == CLICK_BUTTON) {
//				m_stat.setCredit(50);
//				m_cardLogic.setTempLevel(1);
//			}
//
//		} else {
//			gameOver.UpdateTextMessage("");
//		}

		if (PlayButton.getState() == CLICK_BUTTON) {
			m_cardLogic.GetCardFromDeck();
			m_cardLogic.m_TwoCard.clear();

			Timer::g_Timer->StartTimer(2 + m_cardLogic.getTempLevel());
			StateManager::stateMachine->setCurrentGameStates(VIEW_CARDS);
			PlayButton.setState(NORMAL_BUTTON);

		}
		if (m_buttonSet.at(4).getState() == CLICK_BUTTON) {
			StateManager::stateMachine->setCurrentGameStates(MENU);
			m_buttonSet.at(4).setState(NORMAL_BUTTON);
//				SoundsBank::sound->PlaySoundEffect(1);
		}
		credit.IntToTextMessage(m_stat.getCredit());
		level.IntToTextMessage(m_cardLogic.getTempLevel());
		profit.IntToTextMessage(m_stat.getProfit());
		m_statTxtClicks.IntToTextMessage(m_stat.getClickForLevel());

		if (m_stat.getProfit() == 0) {
			m_gameStatus = "Failed";

			m_statTxtLevelNumber.IntToTextMessage(m_cardLogic.getTempLevel());
		} else {
			m_gameStatus = "Succeed";
			m_statTxtLevelNumber.IntToTextMessage(
					m_cardLogic.getTempLevel() - 1);
		}
		m_statTxtLevelStatus.UpdateTextMessage(m_gameStatus);

		break;

	case VIEW_CARDS:

		if (Timer::g_Timer->GetIsStarted()) {

			txtTimer.UpdateTextMessage(Timer::g_Timer->getString());
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

		break;
	case STATISTIC:
		m_buttonSet.at(4).Update(event);
		if (m_buttonSet.at(4).getState() == CLICK_BUTTON) {
			StateManager::stateMachine->setCurrentGameStates(MENU);
			m_buttonSet.at(4).setState(NORMAL_BUTTON);
			SoundsBank::sound->PlaySoundEffect(1);
		}
		break;

	case RECOVERY:

		m_Recovery.LoadRecoverFile();
		credit.IntToTextMessage(m_Recovery.getRecoverCredit());
		level.IntToTextMessage(m_Recovery.getRecoverLevel());
		m_cardLogic.setTempLevel(m_Recovery.getRecoverLevel());
		m_cardLogic.GetCardFromDeck();
		m_stat.setCredit(m_Recovery.getRecoverCredit());
		Timer::g_Timer->StartTimer(m_Recovery.getRecoverLevel() + 2);
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
//		m_buttonsMenuRecover.Draw(m_pRenderer);

		for (int iter = 0; iter < 3; iter++)
			m_buttonSet[iter].Draw(m_pRenderer);

		m_Recovery.LoadRecoverFile();
		if ((m_Recovery.getRecoverLevel() < 2)
				|| (m_Recovery.getRecoverCredit() < 5)) {
			m_buttonsMenuRecover.Draw(m_pRenderer);
		}

		else {
			m_buttonSet[3].Draw(m_pRenderer);
		}

		break;

	case STARTGAME:

		SDL_RenderCopy(m_pRenderer, m_BackGroundTexture, 0, 0);
		m_cardLogic.Draw(m_pRenderer);
		PlayButton.Draw(m_pRenderer);
		m_buttonSet.at(4).Draw(m_pRenderer);
		level.Draw(m_pRenderer);
		txtTimer.Draw(m_pRenderer);
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
		txtTimer.Draw(m_pRenderer);
		gameOver.Draw(m_pRenderer);
		bet.Draw(m_pRenderer);
		credit.Draw(m_pRenderer);
		profit.Draw(m_pRenderer);
		if (m_stat.getGameLevel() > 0) {
			m_statTxtClicks.Draw(m_pRenderer);
			m_statTxtLevelNumber.Draw(m_pRenderer);
			m_statTxtLevelStatus.Draw(m_pRenderer);
			m_statTxtSeconds.Draw(m_pRenderer);
		}
		break;

	case VIEW_CARDS:

		SDL_RenderCopy(m_pRenderer, m_BackGroundTexture, 0, 0);
		PlayButton.Draw(m_pRenderer);
		m_cardLogic.Draw(m_pRenderer);
		m_buttonSet.at(4).Draw(m_pRenderer);
		level.Draw(m_pRenderer);
		txtTimer.Draw(m_pRenderer);
		bet.Draw(m_pRenderer);
		profit.Draw(m_pRenderer);
		credit.Draw(m_pRenderer);
		break;
	case STATISTIC:

		StartMenu.DrawSatistics(m_pRenderer);
		m_buttonSet.at(4).Draw(m_pRenderer);
		break;
	case RECOVERY:
		break;

	}

	SDL_RenderPresent(m_pRenderer);
}/*end of Draw*/

bool Game::Running() {
	return m_bRunning;
}
