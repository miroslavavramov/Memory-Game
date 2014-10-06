
#include "Text.h"

Text::Text() {
	TTF_Init();
	m_TextFont = NULL;
	m_TextFont = TTF_OpenFont("font/12950.ttf", 48);
	m_Message = "";

}

Text::~Text() {
	// TODO Auto-generated destructor stub
}

void Text::Set(int x, int y, int w, int h, string message) {
	m_Destination.x = x;
	m_Destination.y = y;
	m_Destination.w = w;
	m_Destination.h = h;
	m_Message = message;

}

void Text::setTextColor(int r, int g, int b, int a) {
	m_TextColor.r = r;
	m_TextColor.g = g;
	m_TextColor.b = g;
	m_TextColor.a = a;


}
void Text::Draw(SDL_Renderer* a) {
	m_TextSurface= TTF_RenderText_Solid(m_TextFont, m_Message.c_str(), m_TextColor);
	m_Texture = SDL_CreateTextureFromSurface(a, m_TextSurface);
	SDL_RenderCopy(a, m_Texture, 0, &m_Destination);

}

void Text::UpdateTextMessage(string message) {
	m_Message = message;
}
