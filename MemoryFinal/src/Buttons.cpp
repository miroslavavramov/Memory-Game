#include "Buttons.h"

Buttons::Buttons() {
	// TODO Auto-generated constructor stub
	m_currentStateButt = NORMAL_BUTTON;
	m_r = 0;
	m_t = 0;
}

Buttons::~Buttons() {
	// TODO Auto-generated destructor stub
}

void Buttons::Init(SDL_Renderer* a)
{
	SDL_Surface* buttons = IMG_Load("images/buttonsMemory.png");

	m_t = SDL_CreateTextureFromSurface(a,buttons);
	SDL_FreeSurface(buttons);



}

void Buttons::Draw(SDL_Renderer* a)
{
	SDL_RenderCopy(a, m_t, &m_source, &m_destination);
}

void Buttons::ChangeButtonState() {
	if (m_currentStateButt == HOVER_BUTTON) {
		 m_source.y = 52;


	}
	if(m_currentStateButt == NORMAL_BUTTON){
	m_source.y = 0;

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
						if(m_currentStateButt == NORMAL_BUTTON)
						{
							m_currentStateButt = HOVER_BUTTON;
							SoundsBank::sound->PlaySoundEffect(0);
						}

					}
					else{
						m_currentStateButt = NORMAL_BUTTON;
					}
				break;
			case SDL_MOUSEBUTTONDOWN:
					SDL_GetMouseState(&xCoordinate, &yCoordinate);
				if (xCoordinate > m_destination.x
					&& xCoordinate < m_destination.x + m_destination.w
					&& yCoordinate > m_destination.y
					&& yCoordinate < m_destination.y + m_destination.h)

					{
					m_currentStateButt = CLICK_BUTTON;
					}
				break;

			default:
				break;
		}
	ChangeButtonState();
}

void Buttons::setDestination(int x_dest, int y_dest, int w_dest, int h_dest)
{
		m_destination.x = x_dest;
		m_destination.y = y_dest;
		m_destination.w = w_dest;
		m_destination.h = h_dest;

}

void Buttons::setSource(int x_sourc, int y_sourc, int w_sourc, int h_sourc)
{
	m_source.x = x_sourc;
	m_source.y = y_sourc;
	m_source.w = w_sourc;
	m_source.h = h_sourc;
}

void Buttons::setState(stateButtons currentGameStates)
{
	m_currentStateButt = currentGameStates;
}

int Buttons::getState() const {
	return m_currentStateButt;
}
