#ifndef TEXT_H_
#define TEXT_H_

// C++ standard library includes
#include <cstdlib>
#include <cstring>
#include <string>
#include <sstream>

//SDL2 standard library includes
#include "SDL.h"
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

using namespace std;

class Text {
public:

	//Initializes variables
	Text();
	//Deallocates memory
	virtual ~Text();

	//Set coordinate
	void Set(int, int, int, int, string = "");

	//Set text color
	void setTextColor(int = 255, int = 255, int = 255, int = 255);

	//Draw text on screen
	void Draw(SDL_Renderer*);

	//Update timer,
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
	int m_LetterWidth;
	int m_TextCenter;
	};

#endif

