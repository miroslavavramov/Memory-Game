
#ifndef TEXT_H_
#define TEXT_H_

#include "SDL.h"
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <cstdlib>
#include <cstring>
#include <string>
#include <sstream>
#include <iostream>

using namespace std;

class Text {
public:
	Text();
	virtual ~Text();
	void Draw(SDL_Renderer*);
	void Set(int, int, int, int, string = "");
	void setTextColor(int = 255, int = 255, int = 255, int = 255);
	void UpdateTextMessage(string);
	void IntToTextMessage(int);

private:
	SDL_Renderer* m_Renderer;
	SDL_Texture* m_Texture;
	SDL_Rect m_Destination;
	SDL_Color m_TextColor;
	SDL_Surface* m_TextSurface;
	TTF_Font* m_TextFont;
	string m_Message;
};

#endif

