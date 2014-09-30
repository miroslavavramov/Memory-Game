#include "Game.h"
Game::Game() {

}

Game::~Game() {
	// TODO Auto-generated destructor stub
}

bool Game::Init(const char* title, int xpos, int ypos, int width, int height,
		int flags) {
	// attempt to initialize SDL
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
		Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 );
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

	texture.Init(m_pRenderer);
	m_temp.Init(m_pRenderer);

	m_temp.sound->PlayMusic(0);

	return true;

}

void Game::GetCardFromDeck() {
	m_cardSet.clear();
	m_newDeck.Init();
	m_newDeck.Shuffle();
	for (int iter = 0; iter < 7; iter++) {

		Card temp = m_newDeck.getCard();
		m_temp.face = temp.face;
		m_temp.suit = temp.suit;
		m_temp.m_source.x = CARD_WIDTH * m_temp.face;
		m_temp.m_source.y = CARD_HEIGHT * m_temp.suit;
		m_temp.m_source.h = CARD_HEIGHT;
		m_temp.m_source.w = CARD_WIDTH;

		m_cardSet.push_back(m_temp);
		m_cardSet.push_back(m_temp);

	}

	srand(time(NULL));
	random_shuffle(m_cardSet.begin(), m_cardSet.end());
	for (int iter = 0; iter < 14; iter++) {

		m_cardSet[iter].setDestination((iter % 7 * 100) + 100,
				(iter < 7 ? 100 : 250));
	}

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
	for (int iter = 0; iter < 14; iter++) {
		m_cardSet[iter].Update(event);

	}
	compareCard();
}

void Game::Draw() {
	SDL_RenderClear(m_pRenderer);

	texture.Draw(m_pRenderer);
	for (int iter = 0; iter < 14; iter++)
		m_cardSet[iter].Draw(m_pRenderer);

	SDL_RenderPresent(m_pRenderer);
}

bool Game::Running() {
	return m_bRunning;
}

void Game::compareCard() {

	for (int i = 0; i < 14; i++) {

		if (m_cardSet[i].state == 1) {

			m_TwoCard.insert(i);
			switch (m_TwoCard.size()) {

			case 2:

				m_Begin = m_TwoCard.begin();
				m_End = --m_TwoCard.end();

				if (m_cardSet[*m_Begin].face == m_cardSet[*m_End].face
						&& m_cardSet[*m_Begin].suit == m_cardSet[*m_End].suit) {

					m_cardSet[*m_Begin].state = 2;
					m_cardSet[*m_End].state = 2;

					m_temp.sound->PlaySoundEffect(1);

					m_TwoCard.clear();

				}else{	m_TwoCard.insert(i);}

				break;
			case 3:

				m_cardSet[*m_Begin].state = 0;
				m_cardSet[*m_End].state = 0;

				m_TwoCard.erase(*m_Begin);

				m_TwoCard.erase(*m_End);

				break;

			}

		}
	}
}
