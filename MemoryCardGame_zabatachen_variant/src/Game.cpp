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

//		cout << m_cardSet[iter].state << endl;
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
//static int i = 0;
for(int i = 0; i < 14; i++){

	if (m_cardSet[i].state == 1) {

//		cout << m_TwoCard.size()<< "size" << endl;

		switch (m_TwoCard.size()) {
		case 0:
			m_TwoCard.push_back(i);

			cout<<"0 case: "<<i<<endl;
			break;
		case 1:
			m_TwoCard.push_back(i);
			cout<<"1 case: "<<i<<endl;
			break;

		case 2:
			if (m_cardSet[m_TwoCard[0]].face == m_cardSet[m_TwoCard[1]].face
					&& m_cardSet[m_TwoCard[0]].suit
							== m_cardSet[m_TwoCard[1]].suit) {

				m_cardSet[m_TwoCard[0]].state = 2;
				m_cardSet[m_TwoCard[1]].state = 2;
				m_TwoCard.clear();
				//playvame zvuka
				//				Mix_PlayChannel(-1, gScratchRemoveCard, 0);
			} else {
				m_TwoCard.push_back(i);
			}
			break;
		case 3:

			cout << i << endl;
			m_cardSet[m_TwoCard[0]].state = 0;
			m_cardSet[m_TwoCard[1]].state = 0;
			m_TwoCard[0] = m_TwoCard[2];
			m_TwoCard.pop_back();
			m_TwoCard.pop_back();
			break;

		}

//		if (m_TwoCard.size() == 0) {
//			m_TwoCard.push_back(i);
//			cout<<" "<<i<<endl;
//		}
//		else {
//			m_TwoCard.push_back(i);
//
//			if (m_cardSet[m_TwoCard[0]].face
//					== m_cardSet[m_TwoCard[1]].face
//					&& m_cardSet[m_TwoCard[0]].suit
//							== m_cardSet[m_TwoCard[1]].suit) {
//
//				m_cardSet[m_TwoCard[0]].state = 2;
//				m_cardSet[m_TwoCard[1]].state = 2;
//				m_TwoCard.clear();
//				//playvame zvuka
////				Mix_PlayChannel(-1, gScratchRemoveCard, 0);
//			}
//
//		}

	}
}
//i++;
//end else if
//	else if(m_TwoCard.size() == 2)
//	{
//		m_TwoCard.push_back(i);
//
//		m_cardSet[m_TwoCard[0]].state = 0;
//		m_cardSet[m_TwoCard[1]].state = 0;
//		m_TwoCard[0] = m_TwoCard[2];
//		m_TwoCard.pop_back();
//		m_TwoCard.pop_back();
//	}


}
