/*
 * Text.h
 *
 *  Created on: Sep 24, 2014
 *      Author: Todor
 */

#ifndef TEXT_H_
#define TEXT_H_
#include "SDL.h"
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <string>
#include <iostream>
#include <sstream>
using namespace std;

class Text {
public:
	Text();
	virtual ~Text();
	std::stringstream timeText;

	void Init(SDL_Renderer*);
	void Draw(SDL_Renderer*);
	void UpDate(SDL_Event);
	void PrintTime();
	bool running;
private:
	SDL_Renderer* m_r;
	SDL_Texture* m_t;
	SDL_Rect source;
	SDL_Rect destination;
	SDL_Color m_textColor;
	SDL_Surface* m_textSurface;
	TTF_Font* m_textFont;
	string m_Message;
	int m_speed = (SDL_GetTicks() / 100);
	Uint32 startTime;
//	= SDL_GetTicks() / 100;
};
#endif /* TEXT_H_ */
