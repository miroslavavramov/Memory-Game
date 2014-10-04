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
#include <cstdlib>
//#include <string>
#include <iostream>
using namespace std;

class Text {
public:
	Text();
	virtual ~Text();

	void Init(SDL_Renderer*);
	void Draw(SDL_Renderer*);
	void UpDate(SDL_Event);
private:
	SDL_Renderer* m_r;
	SDL_Texture* m_t;
	SDL_Rect source;
	SDL_Rect destination;
	SDL_Color m_textColor;
	SDL_Surface* m_textSurface;
	TTF_Font* m_textFont;
	char m_Message[10];

	unsigned int m_lastTime;
	unsigned int m_currentTime;
	int m_CounterSec;
	int m_CounterDecaSec;
};
#endif /* TEXT_H_ */
