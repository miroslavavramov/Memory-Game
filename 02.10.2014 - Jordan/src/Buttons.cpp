#include "Buttons.h"

Buttons::Buttons() {
	// TODO Auto-generated constructor stub
state = 2;
}

Buttons::~Buttons() {
	// TODO Auto-generated destructor stub
}

void Buttons::Init(SDL_Renderer* a)
{
	SDL_Surface* buttons = IMG_Load("images/buttons.png");
	if (!buttons) {
		cerr << "images/cards.png: not found " << SDL_GetError() << endl;
	}

	m_t = SDL_CreateTextureFromSurface(a,buttons);
	SDL_FreeSurface(buttons);

	buttons = IMG_Load("images/bullet.png");
	m_textBullet = SDL_CreateTextureFromSurface(a,buttons);
	SDL_FreeSurface(buttons);
}

void Buttons::Draw(SDL_Renderer* a)
{
	SDL_RenderCopy(a, m_t, &m_source, &m_destination);
	SDL_RenderCopy(a,m_textBullet,&m_sourceBullet,&m_destinBullet);
}

//const SDL_Rect& Buttons::getDestination() const
//{
//}

//void Buttons::setDestination(int x_dest, int y_dest)
//{
//	m_destination.x = x_dest;
//	m_destination.y = y_dest;
//	m_destination.w = BUTTON_WIDTH;
//	m_destination.h = BUTTON_HEIGHT;
//}

void Buttons::ChangeCardState() {
	if (state == 1) {
		 m_source.y = 70;
		 m_sourceBullet.w = 50;
		 m_sourceBullet.h = 50;
	}
	if(state == 2){
	m_source.y = 0;
	m_sourceBullet.w = 0;
	m_sourceBullet.h = 0;
	}

}


void Buttons::Update(SDL_Event e)
{
	switch (e.type) {
			case SDL_MOUSEMOTION:
				int xCoordinate, yCoordinate;
					SDL_GetMouseState(&xCoordinate, &yCoordinate);

					if (xCoordinate > m_destination.x
							&& xCoordinate < m_destination.x + m_destination.w
							&& yCoordinate > m_destination.y
							&& yCoordinate < m_destination.y + m_destination.h)

					{
						if(state == 2)
						{
							state = 1;
						}

					}
					else{
						state = 2;
					}
				break;
			case SDL_MOUSEBUTTONDOWN:
	//			int xCoordinate, yCoordinate;
					SDL_GetMouseState(&xCoordinate, &yCoordinate);
				if (xCoordinate > m_destination.x
					&& xCoordinate < m_destination.x + m_destination.w
					&& yCoordinate > m_destination.y
					&& yCoordinate < m_destination.y + m_destination.h)

					{
							state = 3;
					}
				break;

			default:
				break;
		}
	ChangeCardState();
}

void Buttons::setDestination(int x_dest, int y_dest, int w_dest, int h_dest)
{
		m_destination.x = x_dest;
		m_destination.y = y_dest;
		m_destination.w = w_dest;
		m_destination.h = h_dest;

		m_destinBullet.x = x_dest - 40;
		m_destinBullet.y = y_dest + 12;
		m_destinBullet.w = 40;
		m_destinBullet.h = 40;
}

void Buttons::setSource(int x_sourc, int y_sourc, int w_sourc, int h_sourc)
{
	m_source.x = x_sourc;
	m_source.y = y_sourc;
	m_source.w = w_sourc;
	m_source.h = h_sourc;

	m_sourceBullet.x = 0;
	m_sourceBullet.y = 0;
	m_sourceBullet.w = 50;
	m_sourceBullet.h = 50;
}
int Buttons::getState() const {
	return state;
}
