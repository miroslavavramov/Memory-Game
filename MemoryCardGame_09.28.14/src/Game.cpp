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
	return true;

}

void Game::GetCardFromDeck() {
	m_cardSet.clear();
	m_newDeck.Init();
	m_newDeck.Shuffle();
	for (int iter = 0; iter < 4; iter++) {

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
	for (int iter = 0; iter < 8; iter++){

			m_cardSet[iter].setDestination((iter % 4 * 100) + 100, (iter<4?100:250));
	}

}
void Game::Update() {
	SDL_Event event;
	if (SDL_PollEvent(&event)) {
		switch (event.type) {
		case SDL_QUIT:
			m_bRunning = false;
			break;
		default:
			break;
		}
	}

}

void Game::Draw() {
	SDL_RenderClear(m_pRenderer);

	texture.Draw(m_pRenderer);
	for (int iter = 0; iter < 8; iter++)
	m_cardSet[iter].Draw(m_pRenderer);

	SDL_RenderPresent(m_pRenderer);
}

bool Game::Running() {
	return m_bRunning;
}
