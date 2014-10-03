#include "Card.h"
#include "SoundsBank.h"

Card::Card() {
	// TODO Auto-generated constructor stub
	int face = 0;
	int suit = 0;
	int state = 0;

}

Card::~Card() {
	// TODO Auto-generated destructor stub
}

void Card::Init(SDL_Renderer* a) {

	SDL_Surface* cardSurface = IMG_Load("images/cards.png");
//	SDL_SetColorKey(cardSurface, 1,
//			SDL_MapRGB(cardSurface->format, 255, 255, 255));
	//Create texture from surface pixels
	if (!cardSurface) {
		cerr << "images/cards.png: not found " << SDL_GetError() << endl;
	}
	m_t = SDL_CreateTextureFromSurface(a, cardSurface);
	SDL_FreeSurface(cardSurface);

//
	sound = new SoundsBank();
	sound->initSoundEffect("sounds/button-24.wav");
	sound->initSoundEffect("sounds/poznati-iz4ezvat-karti.wav");
	sound->initMusic("sounds/cautious-path-01.mp3");
//	m_source.x = CARD_WIDTH * face;
//	m_source.y = CARD_HEIGHT * suit;
//	m_source.h = CARD_HEIGHT;
//	m_source.w = CARD_WIDTH;

}

void Card::Draw(SDL_Renderer* a) {

	SDL_RenderCopy(a, m_t, &m_source, &m_destination);
}

//const SDL_Rect& Card::getDestination() const {
//	return;
//}

void Card::setDestination(int x_dest, int y_dest) {
	m_destination.x = x_dest;
	m_destination.y = y_dest;
	m_destination.w = CARD_WIDTH;
	m_destination.h = CARD_HEIGHT;

}

void Card::ChangeCardState() {
	if (state == 0) {

		m_source.x = CARD_WIDTH * 2;
		m_source.y = CARD_HEIGHT * 4;
		m_source.h = CARD_HEIGHT;
		m_source.w = CARD_WIDTH;


	}
	else if (state == 1) {

		m_source.x = CARD_WIDTH * face;
		m_source.y = CARD_HEIGHT * suit;
		m_source.h = CARD_HEIGHT;
		m_source.w = CARD_WIDTH;


	}else if(state == 2){
		m_source.h = 0;
		m_source.w = 0;
	}

}
void Card::Update(SDL_Event e) {
	if (e.type == SDL_MOUSEBUTTONDOWN) {
		int xCoordinate, yCoordinate;
		SDL_GetMouseState(&xCoordinate, &yCoordinate);

		if (xCoordinate > m_destination.x
				&& xCoordinate < m_destination.x + m_destination.w
				&& yCoordinate > m_destination.y
				&& yCoordinate < m_destination.y + m_destination.h)

		{
			if (state == 0) {
				state = 1;
				sound->PlaySoundEffect(0);
			}
//			else if  (state == 1) {
//				state = 0;
//			}
		}

	}
	ChangeCardState();
}
