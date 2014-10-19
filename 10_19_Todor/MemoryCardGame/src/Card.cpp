#include "Card.h"
int Card::clickCount = 0;
Card::Card() {
	// TODO Auto-generated constructor stub
	int face = 0;
	int suit = 0;
	cardState m_currentStateOfCard = BACK_OF_CARD;
	m_speed = 2;
	m_lastTime = SDL_GetTicks();

}

Card::~Card() {
	// TODO Auto-generated destructor stub
}

void Card::Init(SDL_Renderer* a) {

	SDL_Surface* cardSurface = IMG_Load("images/cards.png");
	//Create texture from surface pixels

	m_t = SDL_CreateTextureFromSurface(a, cardSurface);
	SDL_FreeSurface(cardSurface);

}

void Card::Draw(SDL_Renderer* a) {
	SDL_RenderCopy(a, m_t, &m_source, &m_destination);
}

void Card::setDestination(int x_dest, int y_dest) {
	m_destination.x = x_dest;
	m_destination.y = y_dest;
	m_destination.w = CARD_WIDTH_DEST;
	m_destination.h = CARD_HEIGHT_DEST;

}

void Card::ChangeCardState() {
	if (m_NewStateOfCard != m_currentStateOfCard) {
		m_currentTime = SDL_GetTicks();

		if (m_currentStateOfCard == FACE_OF_CARD
				&& m_NewStateOfCard == BACK_OF_CARD) {
			if (m_currentTime > m_lastTime + 1) {
				m_destination.x += m_speed;
				m_destination.w -= m_speed * 2;
				m_lastTime = m_currentTime;
			}

			if (m_destination.w < 9) {
				m_source.x = CARD_WIDTH * 2;
				m_source.y = CARD_HEIGHT * 4;
				m_speed = -1 * m_speed;

			}
			if (m_destination.w > 89) {
				m_destination.w = 90;
				m_speed = -1 * m_speed;
				m_currentStateOfCard = m_NewStateOfCard;
			}
		} else if (m_currentStateOfCard == BACK_OF_CARD
				&& m_NewStateOfCard == FACE_OF_CARD) {

			if (m_currentTime > m_lastTime + 1) {
				m_destination.x += m_speed;
				m_destination.w -= m_speed * 2;
				m_lastTime = m_currentTime;
			}
			if (m_destination.w < 9) {
				m_source.x = CARD_WIDTH * face;
				m_source.y = CARD_HEIGHT * suit;
				m_speed = -1 * m_speed;

			}
			if (m_destination.w > 89) {
				m_destination.w = 90;
				m_speed = -1 * m_speed;
				m_currentStateOfCard = m_NewStateOfCard;
			}

		} else if (m_currentStateOfCard == FACE_OF_CARD
				&& m_NewStateOfCard == INVISIBLE_OF_CARD) {

			if (m_destination.w > 1) {

				m_currentTime = SDL_GetTicks();
				if (m_currentTime > m_lastTime + 5) {
					m_destination.x += 1;
					m_destination.y += 1;
					m_destination.h -= 3;
					m_destination.w -= 2;
					m_lastTime = m_currentTime;

				}
				if (m_destination.w < 1) {
					m_destination.w = 0;
					m_destination.h = 0;
					m_currentStateOfCard = m_NewStateOfCard;
				}
			}

		}
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
			if (m_currentStateOfCard == BACK_OF_CARD) {
				clickCount++;
				m_NewStateOfCard = FACE_OF_CARD;
				SoundsBank::sound->PlaySoundEffect(2);

			}
		}

	}

	ChangeCardState();

}

int Card::getClickCount() const {
	return clickCount;
}

void Card::setClickCount(int clickCount) {
	this->clickCount = clickCount;
}
